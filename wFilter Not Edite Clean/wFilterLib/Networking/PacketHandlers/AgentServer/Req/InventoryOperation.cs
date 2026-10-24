using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
	public partial class AgentHandler
    {
        public static PacketResult InventoryOperationRequest(Packet packet, PlayerSession session)
        {
            if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                return new PacketResult(PacketResultType.Nothing);
            
                //var check = packet.ReadByte();
                //if (check == 1)
                //{
                var inventoryOperationType =  packet.ReadByte();
                byte fromSlotNo;
                byte toSlotNo;
                // ushort quantity;

                switch (inventoryOperationType)
                {
                case 0x13:
                case 0x14:
                    if (Config.GetExtra.BlockPHBot && packet.Opcode == 0x7034)
                        return new PacketResult(PacketResultType.Block);
                    break;
                    case 0:

                        fromSlotNo = packet.ReadByte();
                        toSlotNo = packet.ReadByte();

                        if (toSlotNo == 8)
                        {
                            if (Config.GetSurvivalEvent.Enable)
                                if (session.State.InSurvival)
                                    return new PacketResult(PacketResultType.Block);

                            

                            if (Config.GetPcLimit.Account > 0 && Config.GetPcLimit.Job > 0)
                            {
                                if (SessionManager.GetJobSessionCountForHwid(session.State.Hwid) + 1 >
                                    Config.GetPcLimit.Job)
                                {
                                    session.SendNotice("You have exceeded the maximum Job Limit on this PC");
                                    return new PacketResult(PacketResultType.Block);
                                }
                            }
                        }

                        break;

                    case 10:
                    case 7:
                        if (Config.GetExtra.DisableDropItemInTown &&
                            session.State.InTown)
                        {
                             session.SendNotice("Dropping item/gold inside towns are forbidden.");
                            return new PacketResult(PacketResultType.Block);
                        }

                        break;

                }
                return new PacketResult(PacketResultType.Nothing);
        }
    }
}
