using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult AlchemyReinforceRequest2(Packet packet, PlayerSession session)
    {
        if (Config.GetExtra.DisableAlchemySystem)
        {
             session.SendNotice("Alchemy system has been disabled !");
            return new PacketResult(PacketResultType.Block);
        }


        return new PacketResult(PacketResultType.Nothing);

    }


    public static PacketResult AlchemyReinforceRequest(Packet packet, PlayerSession session)
    {

        var isExcluded = Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName);

        if (!isExcluded && Config.GetExtra.DisableAlchemySystem)
        {
            session.SendNotice("Alchemy system has been disabled !");
            return new PacketResult(PacketResultType.Block);
        }

        if (packet.ReadByte() == 2 && packet.ReadByte() == 3)
        {
            packet.ReadByte();
            var slot = packet.ReadByte();
            var info = session.GetSql.GetAlchemyTypeInfo(session.State.CharId, slot);
            if (info == null)
                return new PacketResult(PacketResultType.Disconnect, "GetAlchemyTypeInfo() Returned null !");

            session.State.PendingAlchemySlot = slot;
            session.State.PendingAlchemyPlus = info.Plus;

            if (!isExcluded)
            {
                if (info.TypeID3 == 14)
                {
                    if (Config.GetInGameLimits.MaxDevilPlus > 0 && info.Plus >= Config.GetInGameLimits.MaxDevilPlus)
                    {
                        session.SendNotice("You have already reached the current devil max plus.");
                        return new PacketResult(PacketResultType.Block);
                    }
                }
                else if (Config.GetInGameLimits.MaxPlus > 0 && info.Plus >= Config.GetInGameLimits.MaxPlus)
                {
                    session.SendNotice("You have already reached the current item max plus.");
                    return new PacketResult(PacketResultType.Block);
                }
            }
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}