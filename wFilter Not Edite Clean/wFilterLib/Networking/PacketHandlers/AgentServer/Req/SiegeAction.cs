using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult SiegeActionRequest(Packet packet, PlayerSession session)
    {
        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);

        var message = packet.ReadAscii();

        if (message.Contains("'"))
            return new PacketResult(PacketResultType.Block);

        if (message.Contains("\""))
            return new PacketResult(PacketResultType.Block);

        if (message.Contains("-"))
            return new PacketResult(PacketResultType.Block);


        return new PacketResult(PacketResultType.Nothing);
    }
}