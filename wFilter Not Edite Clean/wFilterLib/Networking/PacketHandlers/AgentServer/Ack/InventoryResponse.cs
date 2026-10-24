using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
        public static PacketResult InventoryResponse(Packet packet, PlayerSession session)
        {
            if (packet.ReadByte() == 1)
            {
                var itemSlot = packet.ReadByte();
                packet.ReadUShort();
                var typeId = packet.ReadUShort();

                if (typeId == 0x29ED || typeId == 0x29EC)
                {
                    var refItemId = session.GetSql.Read<int>(
                        @$"use {Config.GetSql.ShardDatabase} SELECT TOP(1) itm.RefItemID FROM _Inventory inv
                        INNER JOIN _Items itm ON inv.ItemID = itm.ID64 where inv.CharID = {session.State.CharId} AND inv.Slot = {itemSlot}");

                    session.State.CurrentGlobalColor = 0xFFFF00;

                    var colors = Config.GetGUISettings.GlobalColors;

                    //if (refItemId == colors.Crimson && colors.Crimson > 0)
                    //    session.State.CurrentGlobalColor = 0xDC143C;
                    //else if (refItemId == colors.Blue && colors.Blue > 0)
                    //    session.State.CurrentGlobalColor = 0x0096FF;
                    //else if (refItemId == colors.DarkCyan && colors.DarkCyan > 0)
                    //    session.State.CurrentGlobalColor = 0x008b8b;
                    //else if (refItemId == colors.Green && colors.Green > 0)
                    //    session.State.CurrentGlobalColor = 0x50C878;
                    //else if (refItemId == colors.Orange && colors.Orange > 0)
                    //    session.State.CurrentGlobalColor = 0xFFA500;
                    //else if (refItemId == colors.Red && colors.Red > 0)
                    //    session.State.CurrentGlobalColor = 0xFF0000;
                    //else if (refItemId == colors.Purple && colors.Purple > 0)
                    //    session.State.CurrentGlobalColor = 0xBF40BF;


                    if (refItemId == colors.Crimson && colors.Crimson > 0)
                        session.State.CurrentGlobalColor = 0x9D2235;
                    else if (refItemId == colors.Blue && colors.Blue > 0)
                        session.State.CurrentGlobalColor = 0x0080ff;
                    else if (refItemId == colors.DarkCyan && colors.DarkCyan > 0)
                        session.State.CurrentGlobalColor = 0x008b8b;
                    else if (refItemId == colors.Green && colors.Green > 0)
                        session.State.CurrentGlobalColor = 0x2ef600;
                    else if (refItemId == colors.Orange && colors.Orange > 0)
                        session.State.CurrentGlobalColor = 0xFF4500;
                    else if (refItemId == colors.Red && colors.Red > 0)
                        session.State.CurrentGlobalColor = 0xFF0000;
                    else if (refItemId == colors.Purple && colors.Purple > 0)
                        session.State.CurrentGlobalColor = 0x8b1a89;

                }
            }


            return new PacketResult(PacketResultType.Nothing);
        }
    }
}
