using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
       public static PacketResult BArenaOperationResponse(Packet packet, PlayerSession session)
        {
            var operation =  packet.ReadByte();
            switch (operation)
            { 
                case 0xFF:
                    var errCode = packet.ReadByte();
                    if (errCode == 0)
                    {
                        var state = packet.ReadByte();
                        packet.ReadByte();

                        switch (state)
                        {
                            case 1: // Registered
                                session.State.ArenaRegistered = true;
                                break;
                            case 2: // Canceled
                                session.State.ArenaRegistered = false;
                                break;
                        }
                    }
                    break;
                case 3:
                case 5:
                case 4:
                    if(session.State.ArenaRegistered)
                        session.State.ArenaRegistered = false;
                    break;
                
            }

            return new PacketResult(PacketResultType.Nothing);
        }


        //0x34D2 - SERVER_AGENT_BARENA_OPERATION

        //1    byte operation

        //if (operation == BArenaOperation.RegisterState)
        //{
        //    1    byte errCode
        //    if (errCode == 0)
        //    {
        //        1    byte state // 1 = Registered, 2 = Canceled
        //        1    byte UnkByte02
        //    }
        //}
    }
}
