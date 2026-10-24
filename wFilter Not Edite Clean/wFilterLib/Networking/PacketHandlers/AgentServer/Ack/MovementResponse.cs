using wFilterLib;
using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;
using wFilterLib.Database.Models;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
        public static PacketResult MovementResponse(Packet packet, PlayerSession session)
        {
            var entity = new MovementResponseEntity();
            entity.ReadFromPacket(packet);

            if (entity.HasDestination && entity.TargetID == session.State.UniqueId)
            {
                session.State.Position = entity.DestPos;
                // CheckRegions(session, session.State.Position.RegionID);
                session.State.InTown = Globals.TownsRegions.Contains(session.State.Position.RegionID);
            }

            return new PacketResult(PacketResultType.Nothing);
        }


        public static PacketResult CancelMovementResponse(Packet packet, PlayerSession session)
        {
            /*if (packet.ReadUInt() == session.State.UniqueId)
                CheckRegions(session, packet.ReadInt32());*/

            return new PacketResult(PacketResultType.Nothing);
        }

        public static void CheckRegions(PlayerSession session, int currentRegionId)
        {
            // session.State.Position.RegionID = currentRegionId;

            /*if (Program.TownsRegions.Contains(currentRegionId))
                session.State.Location = PlayerLocation.Town;*/
            /*else*/
            if (Globals.FgwRegions.Contains(currentRegionId))
                session.State.Location = PlayerLocation.Fgw;
            else if (Globals.ArenaRegions.Contains(currentRegionId))
                session.State.Location = PlayerLocation.Arena;
            else if (Globals.FortressRegions.Contains(currentRegionId))
                session.State.Location = PlayerLocation.Fortress;
            else if (currentRegionId == -32759 &&
                     session.GetSql.Read<int>($"use {Config.GetSql.ShardDatabase} SELECT WorldID FROM dbo._Char where CharID = {session.State.CharId}") ==
                     29) // CTF Region
                session.State.Location = PlayerLocation.Ctf;
            else if (currentRegionId == 24758)
                session.State.Location = PlayerLocation.ThiefVillage;
            else
                session.State.Location = PlayerLocation.None;

            //if (session.State.Location != PlayerLocation.None)
            //    Console.WriteLine($"CharName: {session.State.CharName} | Current Location: {session.State.Location}");

        }
    }
}