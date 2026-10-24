using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult PingRequest(Packet packet, PlayerSession session)
    {
        
        if (session.State is { IsAfk: false })
        {
            session.State.PingCounter++;
            if (session.State.PingCounter >= 300 / 5)
                session.SetAfkStatus(true);
        }
        

        return new PacketResult(PacketResultType.Nothing);
    }
}