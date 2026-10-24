using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{

    public static PacketResult LinkedItemInfo(Packet packet, PlayerSession session)
    {
        var itemSlot = packet.ReadByte();
        var type = packet.ReadUShort();
        if (type == 0x29ED || type == 0x29EC)
        {
            session.State.m_GlobalLinkedItemBegin = packet.ReadByte();
            session.State.m_GlobalLinkedItemEnd = packet.ReadByte();
            session.State.m_CustomLinkedItemName = packet.ReadUnicode();
            session.State.m_GlobalLinkedItemSlot = itemSlot;
        }


        return new PacketResult(PacketResultType.Block);
    }

    public static PacketResult ItemUseRequest(Packet packet, PlayerSession session)
    {
        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);

        var itemSlot = packet.ReadByte();
        var itemId = packet.ReadUShort();

        //  Program.DatabaseConnection.ChangeDatabase(Configs.Config.GetSql.ShardDatabase);
        var refItemId = (int) session.GetSql.Read<int>
            ($"use {Config.GetSql.ShardDatabase} SELECT items.RefItemID FROM _Items as items inner join _Inventory as inv on items.ID64 = inv.ItemID where inv.Slot = {itemSlot} and inv.CharID = {session.State.CharId}");

        if (Config.GetJob.DisableScrolls.Count > 0 && session.State.IsJob)
        {
            if (Config.GetJob.DisableScrolls.Contains(refItemId))
            {
                 session.SendNotice("You are not allowed to use this Scroll under job mode !");
                return new PacketResult(PacketResultType.Block);
            }
        }

        if (Config.GetFortress.DisableScrolls.Count > 0 &&
            session.State.Location == PlayerLocation.Fortress)
        {
            if (Config.GetFortress.DisableScrolls.Contains(refItemId))
            {
                 session.SendNotice("You are not allowed to use this Scroll during Fortress War !");
                return new PacketResult(PacketResultType.Block);
            }
        }

        if (Config.GetBlockByRegion.Scrolls.Count > 0 &&
            Config.GetBlockByRegion.Scrolls.ContainsKey(session.State.TempPosition.RegionID))
        {
            var scrolls = Config.GetBlockByRegion.Scrolls[session.State.TempPosition.RegionID];

            if (scrolls.Contains(refItemId))
            {
                 session.SendNotice("You are not allowed to use this Scroll here !");
                return new PacketResult(PacketResultType.Block);
            }
        }

        if (Config.GetExtra.DisableScrollsOutSideTown.Count > 0 && !session.State.InTown)
        {
            if (Config.GetExtra.DisableScrollsOutSideTown.Contains(refItemId))
            {
                 session.SendNotice("You are not allowed to use this Scroll outside Towns !");
                return new PacketResult(PacketResultType.Block);
            }
        }

        switch (itemId)
        {
            //Global Chatting
            case 0x29ED:
            case 0x29EC:

                #region Global Require Level

                if (Config.GetInGameLimits.GlobalRequireLevel > 0 && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                    if (Config.GetInGameLimits.GlobalRequireLevel > session.State.CurLevel)
                    {
                        const string globalScroll =
                            "You are low level, you need at least level ({level}) to use Global Scroll.";

                         session.SendNotice(globalScroll.Replace("{level}",
                            Config.GetInGameLimits.GlobalRequireLevel.ToString()));
                        return new PacketResult(PacketResultType.Block);
                    }
                }

                #endregion

                #region Global Delay

                if (Config.GetDelays.GlobalDelay > 0 && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                    //if (session.State.GlobalDelay >= DateTime.Now)
                    //{
                    //    const string globalMsg = "Global delay: You must wait {time} sec between each Global usage.";

                    //    session.SendNotice(globalMsg.Replace("{time}", Configs.Config.GetDelays.GlobalDelay.ToString()));
                    //    return new PacketResult(PacketResultType.Block);
                    //}
                    //session.State.GlobalDelay = DateTime.Now.AddSeconds(Configs.Config.GetDelays.GlobalDelay);

                    var lastGlobalSec =
                        Convert.ToInt32(DateTime.Now.Subtract(session.State.GlobalDelay).TotalSeconds);
                    if (lastGlobalSec < Config.GetDelays.GlobalDelay)
                    {
                        var globalMsg =
                            $"Global delay: You must wait [{Config.GetDelays.GlobalDelay - lastGlobalSec}] sec to use Global again";

                         session.SendNotice(globalMsg);
                        return new PacketResult(PacketResultType.Block);
                    }

                    session.State.GlobalDelay = DateTime.Now;
                }

                #endregion

                var message = packet.ReadAscii();

                #region Global item linking

                if (session.State.m_GlobalLinkedItemEnd != 0 && message.Length > session.State.m_CustomLinkedItemName.Length)
                {
                    message = message.Remove(session.State.m_GlobalLinkedItemBegin, session.State.m_CustomLinkedItemName.Length);

                    var pBuffer = new Packet((ushort)wFilterLib.Opcodes.Agent.Request.INVENTORY_ITEM_USE, true);
                    pBuffer.WriteByte(itemSlot);
                    pBuffer.WriteUShort(itemId);
                    pBuffer.WriteAscii(message);
                     session.SendPacketToServer(pBuffer);

                    return new PacketResult(PacketResultType.Block);
                }

                #endregion

                break;

            //Reverse Scroll
            case 0x19ED:
            case 0x19EC:
                var type = packet.ReadByte();

                if (Config.GetSurvivalEvent.Enable)
                    if (session.State.InSurvival)
                        return new PacketResult(PacketResultType.Block);

                if (session.State.LastDiedRegionId == Config.GetSurvivalEvent.RegionId && type == 3 ||
                    session.State.LastReturnRegionId == Config.GetSurvivalEvent.RegionId && type == 2)
                {
                    return new PacketResult(PacketResultType.Block);
                }

                #region Reverse Require Level

                if (Config.GetInGameLimits.ReverseRequireLevel > 0 && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                    if (Config.GetInGameLimits.ReverseRequireLevel > session.State.CurLevel)
                    {
                        const string reverseScroll =
                            "You are low level, you need at least level ({level}) to use Reverse Scroll.";

                         session.SendNotice(reverseScroll.Replace("{level}",
                            Config.GetInGameLimits.ReverseRequireLevel.ToString()));
                        return new PacketResult(PacketResultType.Block);
                    }
                }

                #endregion

                #region Reverse Delay

                if (Config.GetDelays.ReverseDelay > 0 && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                    //if (session.State.ReverseDelay >= DateTime.Now)
                    //{
                    //    const string reverseMsg = "Reverse delay: You must wait {time} sec between each Reverse Scroll usage.";

                    //    session.SendNotice(reverseMsg.Replace("{time}", Configs.Config.GetDelays.ReverseDelay.ToString()));
                    //    return new PacketResult(PacketResultType.Block);
                    //}
                    //session.State.ReverseDelay = DateTime.Now.AddSeconds(Configs.Config.GetDelays.ReverseDelay);


                    var lastReverseSec =
                        Convert.ToInt32(DateTime.Now.Subtract(session.State.ReverseDelay).TotalSeconds);
                    if (lastReverseSec < Config.GetDelays.ReverseDelay)
                    {
                        var reverseMsg =
                            $"Reverse delay: You must wait [{Config.GetDelays.ReverseDelay - lastReverseSec}] sec to use Reverse again";

                         session.SendNotice(reverseMsg);
                        return new PacketResult(PacketResultType.Block);
                    }

                    session.State.ReverseDelay = DateTime.Now;
                }

                #endregion

                if (Config.GetJob.DisableReverse && session.State.IsJob && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                     session.SendNotice("You are not allowed to use Reverse Scrolls under job mode !");
                    return new PacketResult(PacketResultType.Block);
                }



                if (Config.GetBlockByRegion.ReverseRegions.Count > 0 && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {

                    var s = session.State;
                    if ((Config.GetBlockByRegion.ReverseRegions.Contains(s.LastDiedRegionId) &&
                         type == 3) ||
                        (Config.GetBlockByRegion.ReverseRegions.Contains(s.LastReturnRegionId) &&
                         type == 2))
                    {
                         session.SendNotice("You are not allowed to use Reverse Scrolls to this place !");
                        return new PacketResult(PacketResultType.Block);
                    }
                }

                break;

            case 0x36ED:
            case 0x36EC:
                if (Config.GetSurvivalEvent.Enable)
                    if (session.State.InSurvival)
                        return new PacketResult(PacketResultType.Block);

                #region Resurrection Require Level

                if (Config.GetInGameLimits.ResurrectionRequireLevel > 0 && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                    if (Config.GetInGameLimits.ResurrectionRequireLevel > session.State.CurLevel)
                    {
                        const string resurrectionLevel =
                            "You are low level, you need at least level ({level}) to use Resurrection Scroll.";

                         session.SendNotice(resurrectionLevel.Replace("{level}",
                            Config.GetInGameLimits.ResurrectionRequireLevel.ToString()));
                        return new PacketResult(PacketResultType.Block);
                    }
                }

                #endregion

                #region Resurrection Delay

                if (Config.GetDelays.ResurrectionDelay > 0 && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                    //if (session.State.ResurrectionDelay >= DateTime.Now)
                    //{
                    //    const string resurrectionMsg = "Resurrection delay: You must wait {time} sec between each Resurrection Scroll usage.";

                    //    session.SendNotice(resurrectionMsg.Replace("{time}", Configs.Config.GetDelays.ResurrectionDelay.ToString()));
                    //    return new PacketResult(PacketResultType.Block);
                    //}
                    //session.State.ResurrectionDelay = DateTime.Now.AddSeconds(Configs.Config.GetDelays.ResurrectionDelay);

                    var lastResSec = Convert.ToInt32(DateTime.Now.Subtract(session.State.ResurrectionDelay)
                        .TotalSeconds);
                    if (lastResSec < Config.GetDelays.ResurrectionDelay)
                    {
                        var resMsg =
                            $"Resurrection delay: You must wait [{Config.GetDelays.ResurrectionDelay - lastResSec}] sec to use Resurrection again";

                         session.SendNotice(resMsg);
                        return new PacketResult(PacketResultType.Block);
                    }

                    session.State.ResurrectionDelay = DateTime.Now;
                }

                #endregion

                if (Config.GetJob.DisableResScroll && session.State.IsJob && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                     session.SendNotice("You are not allowed to use Res Scrolls under job mode !");
                    return new PacketResult(PacketResultType.Block);
                }

                if (Config.GetFortress.DisableResScroll &&
                    session.State.Location == PlayerLocation.Fortress && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                     session.SendNotice("You are not allowed to use Res Scrolls during Fortress War !");
                    return new PacketResult(PacketResultType.Block);
                }

                break;
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}