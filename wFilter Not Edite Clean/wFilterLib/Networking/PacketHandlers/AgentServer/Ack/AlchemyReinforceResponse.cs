using wFilterLib;
using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult AlchemyReinforceResponse(Packet packet, PlayerSession session)
    {
        try
        {
            if (!Config.GetExtra.EnablePlusNotice)
                return new PacketResult(PacketResultType.Nothing);

            if (session?.State == null || string.IsNullOrEmpty(session.State.CharName))
                return new PacketResult(PacketResultType.Nothing);

            if (session.State.PendingAlchemySlot == 255 || session.State.PendingAlchemyPlus < 0)
                return new PacketResult(PacketResultType.Nothing);

            var result = packet.ReadByte();
            if (result != 1)
            {
                session.State.PendingAlchemySlot = 255;
                session.State.PendingAlchemyPlus = -1;
                return new PacketResult(PacketResultType.Nothing);
            }

            var slot = session.State.PendingAlchemySlot;
            var oldPlus = session.State.PendingAlchemyPlus;
            session.State.PendingAlchemySlot = 255;
            session.State.PendingAlchemyPlus = -1;

            var info = session.GetSql.GetAlchemyTypeInfo(session.State.CharId, slot);
            if (info == null || info.Plus <= oldPlus)
                return new PacketResult(PacketResultType.Nothing);

            if (info.Plus < Config.GetExtra.PlusNoticeMinPlus)
                return new PacketResult(PacketResultType.Nothing);

            var message = Config.GetExtra.PlusNoticeMessage
                .Replace("{player}", session.State.CharName)
                .Replace("{plus}", info.Plus.ToString());

            SessionManager.SendNoticeToAll(message, Config.GetExtra.PlusNoticeColor);
        }
        catch (Exception ex)
        {
            Globals.Logger.Error(ex, "AlchemyReinforceResponse failed");
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}
