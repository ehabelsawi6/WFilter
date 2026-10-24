using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
        public static PacketResult PartyDataUpdateResponse(Packet packet, PlayerSession session)
        {
            var type = packet.ReadByte();

            if (type == 1)
                session.State.InsideParty = false;
            else if (type == 3)
                if (packet.ReadUInt() == session.State.UserJid)
                    session.State.InsideParty = false;
            return new PacketResult(PacketResultType.Nothing);
        }

        public static PacketResult PartyInfoResponse(Packet packet, PlayerSession session)
        {
            session.State.InsideParty = true;

            return new PacketResult(PacketResultType.Nothing);
        }
    }
}
