using wFilterLib;
using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult TeleportUseRequest(Packet packet, PlayerSession session)
    {
        if (packet.GetBytes().Length < 9) return new PacketResult(PacketResultType.Nothing);

        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);


        packet.ReadUInt(); //NPC ID

        if (packet.ReadByte() == 2)
        {
            if (session.State.InSurvival)
                return new PacketResult(PacketResultType.Block);

            var targetTeleport = packet.ReadUInt();
            var teleportControl = Config.GetTeleport;

            //Hwid fw Limit
            if (Config.GetPcLimit.Account > 0)
            {
                if (Config.GetPcLimit.Fw > 0 && Globals.FwTeleports.Contains((int) targetTeleport))
                {
                    if (SessionManager.GetFwSessionCountForHwid(session.State.Hwid) + 1
                        > Config.GetPcLimit.Fw)
                    {
                         session.SendNotice("You have reached the maxmimum allowed PC(s) to enter the fortress.");

                    }
                }
            }



            //Teleport By Time Control
            if (teleportControl.TeleportByTime.Count > 0 &&
                teleportControl.TeleportByTime.ContainsKey(targetTeleport))
            {
                var isTime = false;

                foreach (var teleTime in teleportControl.TeleportByTime[targetTeleport])
                {
                    if (DateTime.Parse(teleTime.Start) <= DateTime.Now &&
                        DateTime.Parse(teleTime.End) >= DateTime.Now)
                    {
                        isTime = true;
                        break;
                    }
                }

                if (!isTime)
                {
                     session.SendNotice("You aren't allowed to use this teleport now!");
                    return new PacketResult(PacketResultType.Block);
                }
            }

            //Teleport by jobType


            var thiefTeleport = teleportControl.ThiefOnlyTeleports.Contains(targetTeleport);
            var hunterTeleport = teleportControl.HunterOnlyTeleports.Contains(targetTeleport);
            var traderTeleport = teleportControl.TraderOnlyTeleports.Contains(targetTeleport);
            var jobType = session.State.JobType;
            if (thiefTeleport || hunterTeleport || traderTeleport)
            {
                if (!session.State.IsJob)
                {
                     session.SendNotice("You aren't allowed to use this teleport (Requires Job)");
                    // session.SendNotice("Only job mode can enter this area");
                    return new PacketResult(PacketResultType.Block);
                }

                if ((thiefTeleport && jobType == JobType.Robber)
                    || (hunterTeleport && jobType == JobType.Hunter)
                    || (traderTeleport && jobType == JobType.Trader))
                {
                    return new PacketResult(PacketResultType.Nothing);
                }

                 session.SendNotice("You aren't allowed to use this teleport");
                return new PacketResult(PacketResultType.Block);
            }

            //if (teleportControl.ThiefOnlyTeleports.Count > 0 &&
            //    teleportControl.ThiefOnlyTeleports.Contains(targetTeleport))
            //{
            //    if (!session.State.IsJob || session.State.JobType != JobType.Robber)
            //    {
            //        session.SendNotice("You aren't allowed to use this teleport");
            //        return new PacketResult(PacketResultType.Block);
            //    }
            //}

            //if (teleportControl.HunterOnlyTeleports.Count > 0 &&
            //    teleportControl.HunterOnlyTeleports.Contains(targetTeleport))
            //{
            //    if (!session.State.IsJob || session.State.JobType != JobType.Hunter)
            //    {
            //        session.SendNotice("You aren't allowed to use this teleport");
            //        return new PacketResult(PacketResultType.Block);
            //    }
            //}

            //if (teleportControl.TraderOnlyTeleports.Count > 0 &&
            //    teleportControl.TraderOnlyTeleports.Contains(targetTeleport))
            //{
            //    if (!session.State.IsJob || session.State.JobType != JobType.Trader)
            //    {
            //        session.SendNotice("You aren't allowed to use this teleport");
            //        return new PacketResult(PacketResultType.Block);
            //    }
            //}
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}