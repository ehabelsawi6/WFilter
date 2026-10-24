using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult StallCreateRequest(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);

        if (Config.GetSurvivalEvent.Enable)
            if (session.State.InSurvival)
                return new PacketResult(PacketResultType.Block);

        if (!session.State.InTown && Config.GetExtra.DisableStallOutSideTown)
        {
             session.SendNotice("You aren't allowed to open stall outside towns !");
            return new PacketResult(PacketResultType.Block);
        }

        #region Stall Require Level

        if (Config.GetInGameLimits.StallRequireLevel > 0)
        {
            if (Config.GetInGameLimits.StallRequireLevel > session.State.CurLevel)
            {
                var stallLevel = "You are low level, you need at least level ({level}) to open a stall.";

                 session.SendNotice(stallLevel.Replace("{level}",
                    Config.GetInGameLimits.StallRequireLevel.ToString()));
                return new PacketResult(PacketResultType.Block);
            }
        }

        #endregion

        #region Stall Delay

        if (Config.GetDelays.StallDelay > 0)
        {
            //if (session.State.StallDelay >= DateTime.Now)
            //{
            //    var stalleMsg = "Stall delay: You must wait {time} sec between each Stall Open.";

            //    session.SendNotice(stalleMsg.Replace("{time}", Configs.Config.GetDelays.StallDelay.ToString()));
            //    return new PacketResult(PacketResultType.Block);
            //}
            //session.State.StallDelay = DateTime.Now.AddSeconds(Configs.Config.GetDelays.StallDelay);

            var lastStallSec = Convert.ToInt32(DateTime.Now.Subtract(session.State.StallDelay).TotalSeconds);
            if (lastStallSec < Config.GetDelays.StallDelay)
            {
                var stallMsg =
                    $"Stall delay: You must wait [{Config.GetDelays.StallDelay - lastStallSec}] sec to Stall again";

                 session.SendNotice(stallMsg);
                return new PacketResult(PacketResultType.Block);
            }

            session.State.StallDelay = DateTime.Now;
        }

        #endregion

        if (Config.GetExtra.DisableExcStallRestartExitByRegion.Contains(session.State
                .TempPosition.RegionID))
        {
             session.SendNotice("You may not use this function here!");
            return new PacketResult(PacketResultType.Block);
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}