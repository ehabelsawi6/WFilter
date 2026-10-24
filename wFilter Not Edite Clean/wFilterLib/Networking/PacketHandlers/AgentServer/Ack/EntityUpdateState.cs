using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
       public static PacketResult EntityUpdateStateResponse(Packet packet, PlayerSession session)
        {
         
                var gameId = packet.ReadUInt();
                var type =  packet.ReadByte();
                var state = packet.ReadByte();

                if (type == 4)
                {
                    if (gameId == session.State.UniqueId)
                    {
                        if (state == 0x00)
                        {
                            session.State.IsZerking = false;
                        }
                        else if (state == 0x01)
                        {
                            packet.ReadByte();

                            session.State.IsZerking = true;
                        }
                    }
                }
                
                return new PacketResult(PacketResultType.Nothing);
        }
    }
}
