using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
        public static PacketResult StallCreateResponse(Packet packet, PlayerSession session)
        {
            if (!session.State.InTown && Config.GetExtra.DisableStallOutSideTown)
            {
                var pCancelStall = new Packet((ushort)wFilterLib.Opcodes.Agent.Request.STALL_DESTROY);
                 session.SendPacketToServer(pCancelStall);


                 session.SendNotice("You aren't allowed to open stall outside towns !");
            }

            return new PacketResult(PacketResultType.Nothing);
        }
    }
}
