using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wFilterLib.Networking.PacketHandlers
{
	public interface IPacketHandler
    {
        PacketResult HandleReq(Packet packet, PlayerSession session);
        PacketResult HandleAck(Packet packet, PlayerSession session);

    }
}
