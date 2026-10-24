using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult FrPvpUpdateRequest(Packet packet, PlayerSession session)
    {
        //var pvpMode = (FrPvpMode)packet.ReadByte();
        if (Config.GetSurvivalEvent.Enable)
            if (session.State.InSurvival)
                return new PacketResult(PacketResultType.Block);

        if (Config.GetExtra.AutoCapeRegions.Count > 0
            && Config.GetExtra.AutoCapeRegions.Contains(session.State.TempPosition.RegionID))
            return new PacketResult(PacketResultType.Block);


        return new PacketResult(PacketResultType.Nothing);
    }
}