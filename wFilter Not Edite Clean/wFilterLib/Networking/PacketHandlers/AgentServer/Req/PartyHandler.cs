using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult PartyRequests(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);
        
        if (Config.GetBlockByRegion.PartyRegions.Count <= 0)
            return new PacketResult(PacketResultType.Nothing);

        if (Config.GetSurvivalEvent.Enable)
            if (session.State.InSurvival)
                return new PacketResult(PacketResultType.Block);

        if (Config.GetBlockByRegion.PartyRegions.Contains(session.State.TempPosition.RegionID))
        {
             session.SendNotice("You aren't allowed to send/join or create parties in this arena");
            return new PacketResult(PacketResultType.Block);
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}