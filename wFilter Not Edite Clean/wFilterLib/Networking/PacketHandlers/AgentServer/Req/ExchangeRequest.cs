using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult ExchangeStartRequest(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);

        if (session.State.InSurvival)
            return new PacketResult(PacketResultType.Block);


        #region Exchange Delay

        if (Config.GetDelays.ExchangeDelay > 0)
        {
            var lastExchangeSec =
                Convert.ToInt32(DateTime.Now.Subtract(session.State.ExchangeDelay).TotalSeconds);
            if (lastExchangeSec < Config.GetDelays.ExchangeDelay)
            {
                var exchangeMsg =
                    $"Exchange delay: You must wait [{Config.GetDelays.ExchangeDelay - lastExchangeSec}] sec to Exchange again";

                 session.SendNotice(exchangeMsg);
                return new PacketResult(PacketResultType.Block);
            }

            //session.State.ExchangeDelay = DateTime.Now.AddSeconds(Configs.Config.GetDelays.ExchangeDelay);
            session.State.ExchangeDelay = DateTime.Now;
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