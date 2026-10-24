using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
       public static PacketResult LoginResponse(Packet packet, PlayerSession session)
        {
            var result = packet.ReadByte();

            if (result != 1) return new PacketResult(PacketResultType.Nothing);
            
            session.State.IsOnline = true;
            //Globals.PlayerStatus[session.State.TokenId].IsOnline = true;

            session.State.CharScreen = true;


            return new PacketResult(PacketResultType.Nothing);
        }
    }
}
