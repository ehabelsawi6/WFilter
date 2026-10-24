using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult TimeJobUsageRequest(Packet packet, PlayerSession session)
    {

        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);


        packet.ReadUInt();
        var itemId = packet.ReadUInt();
        var type = 0;

        if (itemId == 3795)
        {
            type = packet.ReadByte();
        }

        if (itemId is 3783 or 3782 or 36785 or 3769 or 3795)
        {
            if (session.State.InSurvival)
                return new PacketResult(PacketResultType.Block);

            if (itemId == 3795)
            {
                if (session.State.LastDiedRegionId == Config.GetSurvivalEvent.RegionId && type == 3 ||
                    session.State.LastReturnRegionId == Config.GetSurvivalEvent.RegionId && type == 2)
                {
                    return new PacketResult(PacketResultType.Block);
                }
            }
            
        }

        if (itemId is 3783 or 3782 or 36785)
        {
            if (Config.GetJob.DisableResScroll && session.State.IsJob)
            {
                 session.SendNotice("You can't use this function in job mode!");
                return new PacketResult(PacketResultType.Block);
            }

            if (Config.GetFortress.DisableResScroll &&
                session.State.Location == PlayerLocation.Fortress)
            {
                 session.SendNotice("You can't use this function during Fortress way !");
                return new PacketResult(PacketResultType.Block);
            }
        }

        if (Config.GetJob.DisablePremiumReturn && itemId == 3769 && session.State.IsJob)
        {
             session.SendNotice("You can't use this function in job mode!");
            return new PacketResult(PacketResultType.Block);
        }

        if (Config.GetJob.DisablePremiumReverse && itemId == 3795 && session.State.IsJob)
        {
             session.SendNotice("You can't use this function in job mode!");
            return new PacketResult(PacketResultType.Block);
        }

        if (Config.GetBlockByRegion.ReverseRegions.Count > 0 && itemId == 3795)
        {

            var s = session.State;
            if ((Config.GetBlockByRegion.ReverseRegions.Contains(s.LastDiedRegionId) &&
                 type == 3) ||
                (Config.GetBlockByRegion.ReverseRegions.Contains(s.LastReturnRegionId) &&
                 type == 2))
            {
                 session.SendNotice("You are not allowed to use Reverse Scrolls to this place !");
                return new PacketResult(PacketResultType.Block);
            }
        }

        return new PacketResult(PacketResultType.Nothing);

    }
}