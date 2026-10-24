using wFilterLib;
using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.Opcodes;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult GameReadyRequest(Packet packet, PlayerSession session)
    {

        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);

        session.SendPacketToServer(packet);

        if (Globals.BlockData.ContainsKey(session.State.Hwid))
        {
            if (Globals.BlockData[session.State.Hwid].EndDate > DateTime.Now)
            {
                session.SendPinkNotice(
                    $"You have been blocked till {Globals.BlockData[session.State.Hwid].EndDate}");
                //return new PacketResult(PacketResultType.Block);
                return new PacketResult(PacketResultType.Disconnect);

            }

            session.GetSql.ExecuteNonQuery(
                    $"use wFilter delete from _Blocked where Id = {Globals.BlockData[session.State.Hwid].Id}")
                ;
            // PrintToConsole.Notify($"IP: {Globals.BlockData[session.State.Ip]} has been unblocked !");
            Globals.BlockData.TryRemove(session.State.Hwid, out _);

        }


        //if (!session.State.IsLocked || session.State.SavedPC == session.State.Hwid)
        //    session.SendPacketToServer(packet);
        //else
        //{
        //    session.State.GameReadyPacket = packet;

        //    var pLocked = new Packet((ushort)Custom.Response.Customs);
        //    pLocked.WriteUInt8(MsgOpcodeTypes.UnLockResponse);
        //    pLocked.WriteUInt8(1);

        //    session.SendPacketToClient(pLocked);
        //}

        if (string.IsNullOrEmpty(session.State.Hwid) && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
        {

            if (Config.GetLogin.AllowClientLess)
            {
                var ip = session.GetSql.Read<string>(
                    $"use wFilter exec _wReturnUserIp '{session.State.UserName}'");

                if(!string.IsNullOrEmpty(ip) && ip == session.State.Ip)
                {
                    var hwid = session.GetSql.Read<string>(
                   $"use wFilter exec _wReturnUserHwid '{session.State.UserName}'");
                    if (!string.IsNullOrEmpty(hwid) && hwid != "none" /* && hwid.Length == 32*/)
                    {
                        session.State.Hwid = hwid;
                        session.IsClientLess = true;
                    }
                    else
                    {
                        session.SendNotice(
                           "New hardware detected or hwid didn't sent please restart the client !");
                        return new PacketResult(PacketResultType.Disconnect);
                    }
                }
                else
                {
                    session.SendNotice(
                       "New hardware detected or hwid didn't sent please restart the client !");
                    return new PacketResult(PacketResultType.Disconnect);
                }
            }
            else
            {
                session.SendNotice(
                   "(1)Our hwid dll is not found or corrupted,Please re-download it or try to restart the client !"
                  );
                return new PacketResult(PacketResultType.Disconnect);
            }

        }

        var u = session.State;


        var result = session.GetSql.ExecuteNonQuery(
            $"use wFilter exec _UpdatePlayerStatus '{u.UserName}','{u.CharName}','{u.Ip}','{u.Hwid}'");

        CheckRegions(session, session.State.TempPosition.RegionID);
        session.State.InTown = Globals.TownsRegions.Contains(session.State.TempPosition.RegionID);
        if (Config.GetSurvivalEvent.Enable)
            session.State.InSurvival = session.State.TempPosition.RegionID == Config.GetSurvivalEvent.RegionId;

        session.GetSql.GetCharacterRegions(session);

        if (Config.GetLogin.AllowClientLess && session.State.IsClientLess)
        {
            session.State.Position.RegionID = session.GetSql.Read<int>
                    ($"use {Config.GetSql.ShardDatabase} Select top 1 LatestRegion from _Char where CharID = {session.State.CharId}");

            session.State.CurLevel = session.GetSql.Read<int>
                    ($"use {Config.GetSql.ShardDatabase} Select CurLevel from _Char where CharID = {session.State.CharId}");

            session.State.IsJob = session.GetSql.Read<int>
                    ($"use {Config.GetSql.ShardDatabase} select top 1 ItemID from _Inventory where Slot = 8 and CharID = {session.State.CharId}") != 0;
            session.State.JobType = (JobType)session.GetSql.Read<byte>
                        ($"use {Config.GetSql.ShardDatabase} select top 1 JobType from _CharTrijob where CharID = {session.State.CharId}");

        }

        if (Config.GetExtra.AutoCapeRegions.Count > 0 && !session.State.IsJob
                                                                     && Config.GetExtra.AutoCapeRegions
                                                                         .Contains(session.State.TempPosition
                                                                             .RegionID))
        {
            var pUpdatePvp = new Packet((ushort)Custom.Framework.MAIN);
            pUpdatePvp.WriteUInt(session.State.UniqueId);
            pUpdatePvp.WriteByte(3); // type | _InstantPvpStateDelivery
            pUpdatePvp.WriteByte(5); // Cape id
             session.SendPacketToServer(pUpdatePvp);
            //Task.Run(async () => await Program.DatabaseConnection.Execute(
            //    $"use wFilter INSERT INTO _InstantPvpStateDelivery (CharID,[State]) VALUES ({session.State.CharId},5)"));
        }

        if (!Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
        {
            if (Config.GetPcLimit.Account > 0 && Config.GetPcLimit.Job > 0 &&
                session.State.IsJob)
            {
                if (SessionManager.GetJobSessionCountForHwid(session.State.Hwid)
                    > Config.GetPcLimit.Job)
                {
                     session.SendNotice("You have exceeded the maximum Job Limit on this PC");
                    return new PacketResult(PacketResultType.Disconnect);
                }
            }
        }

        if (!session.State.FirstTime)
        {
            if (!Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            {
                //     _= Program.DatabaseConnection.UpdateHwanList(session);
                if (Config.GetPcLimit.Ip > 0)
                {
                    var ipCount = SessionManager.GetSessionCountForIp(session.State.Ip);
                    if (ipCount > Config.GetPcLimit.Ip)
                    {
                         session.SendNotice("You have reach the maximum accounts on this IP !");
                        return new PacketResult(PacketResultType.Disconnect);
                    }
                }

                if (Config.GetPcLimit.Account > 0)
                {
                    if (string.IsNullOrEmpty(session.State.Hwid))
                    {
                         session.SendNotice(
                            "Our hwid dll is not found or corrupted,Please re-download it or contact our support !");
                        return new PacketResult(PacketResultType.Disconnect);
                    }


                    if (SessionManager.GetSessionCountForHwid(session.State.Hwid)
                        > Config.GetPcLimit.Account)
                    {
                         session.SendNotice("You have exceeded the maximum PC Limit on this PC");
                        return new PacketResult(PacketResultType.Disconnect);
                    }
                }
            }

            var welcomeMsg = Config.GetExtra.WelcomeMessage;
            if (welcomeMsg.Length > 0)
            {
                welcomeMsg = welcomeMsg.Replace("{playername}", session.State.CharName);
                welcomeMsg = welcomeMsg.Replace("{servername}", Config.GetLogin.ServerName);

                 session.SendNotice(welcomeMsg);
            }

           

            #region SilkPerHour System

            if (Config.GetSilkPerHour.RewardEvery > 0 && Config.GetSilkPerHour.Enable)
            {
                if (Config.GetSilkPerHour.PCLimit == 0 || Config.GetSilkPerHour.PCLimit >
                    SessionManager.GetSilkPerHourCountForHwid(session.State.Hwid))
                {
                    session.InitializeSilkTimerObject(
                        (Config.GetSilkPerHour.RewardEvery > 0 ? Config.GetSilkPerHour.RewardEvery : 1) *
                        60000);
                    if (Config.GetSilkPerHour.PCLimit > 0)
                        session.SendNotice(
                            $"silk per hour system activated for this character! | Limit is {Config.GetSilkPerHour.PCLimit} Per PC");
                }
                   
            }
               

            #endregion

            session.State.FirstTime = true;
        }

        if (!Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
        {
            if (Config.GetPcLimit.Account > 0)
            {
                if (Config.GetPcLimit.Fw > 0 && session.State.Location == PlayerLocation.Fortress)
                {
                    var countIn = SessionManager.GetFwSessionCountForHwid(session.State.Hwid);
                    if (countIn > Config.GetPcLimit.Fw)
                    {
                         session.SendNotice("You have exceeded the maximum Fortress Limit on this PC");
                        session.TeleportToDonwhang();
                    }
                }

                if (Config.GetPcLimit.Arena > 0 && session.State.Location == PlayerLocation.Arena)
                {
                    var countIn =
                        SessionManager.GetArenaRegionSessionCountForHwid(session.State.Hwid);
                    if (countIn > Config.GetPcLimit.Arena)
                    {
                         session.SendNotice("You have exceeded the maximum Arena Limit on this PC");
                        session.TeleportToDonwhang();
                    }
                }

                if (Config.GetPcLimit.Ctf > 0 && session.State.Location == PlayerLocation.Ctf)
                {
                    var countIn =
                        SessionManager.GetCtfRegionSessionCountForHwid(session.State.Hwid);
                    if (countIn > Config.GetPcLimit.Ctf)
                    {
                         session.SendNotice("You have exceeded the maximum CTF Limit on this PC");
                        session.TeleportToDonwhang();
                    }
                }

                if (Config.GetPcLimit.RegionPcLimit.Count > 0 &&
                    Config.GetPcLimit.RegionPcLimit.ContainsKey(session.State.TempPosition.RegionID))
                {
                    var countIn =
                        SessionManager.GetCustomRegionSessionCountForHwid(session.State.Hwid,
                            session.State.TempPosition.RegionID);
                    if (countIn > Config.GetPcLimit.RegionPcLimit[session.State.TempPosition.RegionID])
                    {
                         session.SendNotice("You have exceeded the maximum PC Limit in that Area");
                        session.TeleportToDonwhang();

                    }
                }

            }

            if (Config.GetBlockByRegion.PartyRegions.Count > 0 && session.State.InsideParty &&
                Config.GetBlockByRegion.PartyRegions.Contains(session.State.TempPosition.RegionID))
            {

                //  session.SendNotice("You cannot enter to this area inside a party or a party matching.");
                //session.TeleportToDonwhang();

                var partyLeave = new Packet((ushort)wFilterLib.Opcodes.Agent.Request.PARTY_LEAVE);
                 session.SendPacketToServer(partyLeave);
            }

            if (Config.GetSurvivalEvent.Enable)
            {

                if (session.State.InSurvival)
                {
                    if (Globals.SurvivalEvent)
                    {
                        if (!Globals.SurvivalEventRegisteredCharacters.Contains(session.State.CharName))
                        {
                            Globals.SurvivalEventRegisteredCharacters.Add(session.State.CharName);

                            var remainTime = (uint)(DateTime.Now - Globals.SurvivalStartTime).TotalSeconds * 1000;

                            var playingTimer = new Packet(0x34B1);
                            playingTimer.WriteByte(255);
                            playingTimer.WriteByte(14);
                            playingTimer.WriteInt32(20 * 60 * 1000 -
                                (Config.GetSurvivalEvent.PlayingDuration * 60 * 1000) + remainTime);
                            session?.SendPacketToClient(playingTimer);
                        }

                        var partyLeave = new Packet((ushort)wFilterLib.Opcodes.Agent.Request.PARTY_LEAVE);
                        session?.SendPacketToServer(partyLeave);

                        session?.LiveTitleUpdate(5);
                    }
                    else
                    {
                        session.TeleportToDonwhang();
                        session.State.SurvivalBlock = false;
                    }

                }
                else
                    session.State.SurvivalBlock = false;
            }
        }


        //gui

        var pGUISettings = new Packet((ushort)Custom.Response.Customs);
        pGUISettings.WriteUInt8(0x99);
        pGUISettings.WriteBool(Config.GetGUISettings.TitleManager);
        pGUISettings.WriteBool(Config.GetGUISettings.UniqueStatus);
        pGUISettings.WriteBool(Config.GetGUISettings.EventTimes);
        pGUISettings.WriteBool(Config.GetGUISettings.GrantName);
        pGUISettings.WriteBool(Config.GetGUISettings.CustomTitle);
        pGUISettings.WriteBool(Config.GetGUISettings.DynamicShop);
        pGUISettings.WriteBool(Config.GetGUISettings.Facebook);
        pGUISettings.WriteBool(Config.GetGUISettings.Discord);
        pGUISettings.WriteBool(Config.GetGUISettings.Website);
        pGUISettings.WriteAscii(Config.GetGUISettings.FacebookLink);
        pGUISettings.WriteAscii(Config.GetGUISettings.DiscordLink);
        pGUISettings.WriteAscii(Config.GetGUISettings.WebsiteLink);

        session.SendPacketToClient(pGUISettings);


        session.GetSql.UpdateHwanList(session);

        if (session.State.CharTitles.Count > 0)
        {
            var titlesPacket = new Packet((ushort)Custom.Response.Customs);
            titlesPacket.WriteUInt8(0x21);
            titlesPacket.WriteUInt16(session.State.CharTitles.Count);
            foreach (var titleId in session.State.CharTitles)
                titlesPacket.WriteByte(titleId);

            session.SendPacketToClient(titlesPacket);
        }

        session.GetSql.ReadQuery(session);

        if (!string.IsNullOrEmpty(session.State.CustomTitleName) ||
            session.State.NameColor != 0 ||
            session.State.TitleColor != 0 || session.State.CustomIconId != 0 ||
            session.State.DSPoints != 0)
        {
            var customPacket = new Packet((ushort)Custom.Response.Customs);
            customPacket.WriteByte(0x41);

            customPacket.WriteUInt(session.State.UniqueId);
            customPacket.WriteInt32(session.State.NameColor);
            customPacket.WriteInt32(session.State.TitleColor);

            customPacket.WriteBool(!string.IsNullOrEmpty(session.State.CustomTitleName));
            if (!string.IsNullOrEmpty(session.State.CustomTitleName))
                customPacket.WriteAscii(session.State.CustomTitleName);

            customPacket.WriteInt32(session.State.CustomIconId);
            //customPacket.WriteByte(session.State.CustomTitleCredits);
            customPacket.WriteInt32(session.State.DSPoints);

            session.SendPacketToClient(customPacket);
            //  await SessionManager.SendPacketToAll(customPacket);
        }


        var pDShop = new Packet((ushort)Custom.Response.Customs);
        pDShop.WriteUInt8(MsgOpcodeTypes.DShopResponse);
        pDShop.WriteUInt8(1); // 1 = title shop
        pDShop.WriteUInt8(Globals.DShopTitlesList.Count);
        if (!Globals.DShopTitlesList.IsEmpty)
        {
            foreach (var title in Globals.DShopTitlesList.Values)
            {
                pDShop.WriteInt32(title.TitleId);
                pDShop.WriteInt32(title.Price);
            }
        }

        pDShop.WriteInt32(Globals.DShopNameColorPrice);
        pDShop.WriteInt32(Globals.DShopTitleColorPrice);
        pDShop.WriteInt32(Globals.DShopCustomTitlePrice);

        session.SendPacketToClient(pDShop);


        if (session.State.SurvivalBlock && Config.GetSurvivalEvent.RegionId != session.State.TempPosition.RegionID)
            session.State.SurvivalBlock = false;
       
        
        return new PacketResult(PacketResultType.Block);
    }
}