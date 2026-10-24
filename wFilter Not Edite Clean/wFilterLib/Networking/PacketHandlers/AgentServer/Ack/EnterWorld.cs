using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Opcodes;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
        public static PacketResult EnterWorld(Packet packet, PlayerSession session)
        {

            if (Config.GetExtra.BlockPHBot)
            {
                //Fucks PhBot 
                var random = new Random();

                var multiplier = random.Next(1, 6);
                var addition = random.Next(1, 23);
                var newOpcode = (uint)random.Next(50000, 65535);
                session.State.phbotOpcode = newOpcode;

                var tradePacket = new Packet((ushort)Custom.Response.Customs);
                tradePacket.WriteUInt8(55);
                tradePacket.WriteUInt8(multiplier);
                tradePacket.WriteUInt8(addition);
                tradePacket.WriteUInt64(((newOpcode * multiplier) + addition));

                 session.SendPacketToClient(tradePacket);
            }

            //SessionManager.SendCharacterInfo(session);


            return new PacketResult(PacketResultType.Nothing);
        }
    }
}
