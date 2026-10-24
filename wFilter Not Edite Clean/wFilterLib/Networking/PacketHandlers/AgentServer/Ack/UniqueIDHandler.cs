using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
       public static PacketResult CelestialPositionResponse(Packet packet, PlayerSession session)
        {
            session.State.UniqueId = packet.ReadUInt();

            return new PacketResult(PacketResultType.Nothing);
        }
    }
}
