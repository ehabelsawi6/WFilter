using wFilterLib;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult DPSMeter(Packet packet, PlayerSession session)
    {
        try
        {
            var refObjId = packet.ReadUInt();
            var size = packet.ReadUInt();

            var records = new List<(string Name, uint Damage, PlayerSession Player)>();
            for (int i = 0; i < size; i++)
            {
                var dwPlayerGID = packet.ReadUInt();
                var dwDamage = packet.ReadUInt();
                var player = SessionManager.GetStateByUniqueID(dwPlayerGID);
                if (player?.State == null || string.IsNullOrEmpty(player.State.CharName))
                    continue;

                records.Add((player.State.CharName, dwDamage, player));
            }

            if (records.Count == 0)
                return new PacketResult(PacketResultType.Block);

            records.Sort((a, b) => b.Damage.CompareTo(a.Damage));

            var pDPSMeter = new Packet(0x1338);
            pDPSMeter.WriteByte(0x42);
            pDPSMeter.WriteUInt(refObjId);
            pDPSMeter.WriteUInt((uint)records.Count);

            foreach (var record in records)
            {
                pDPSMeter.WriteAscii(record.Name);
                pDPSMeter.WriteUInt(record.Damage);
            }

            foreach (var record in records)
                record.Player.SendPacketToClient(pDPSMeter);

            return new PacketResult(PacketResultType.Block);
        }
        catch (Exception ex)
        {
            Globals.Logger.Error(ex, "DPSMeter handler failed");
            return new PacketResult(PacketResultType.Block);
        }
    }
}
