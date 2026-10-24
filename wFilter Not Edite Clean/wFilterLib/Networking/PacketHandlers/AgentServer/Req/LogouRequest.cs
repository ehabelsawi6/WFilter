using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult LogoutRequest(Packet packet, PlayerSession session)
    {
        if(packet.Length > 1)
            return new PacketResult(PacketResultType.Disconnect);

        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);

        var logoutRequest = packet.ReadByte();

        if (Config.GetExtra.DisableExcStallRestartExitByRegion.Contains(session.State
                .TempPosition.RegionID))
        {
             session.SendNotice("You may not use this function here!");
            return new PacketResult(PacketResultType.Block);
        }

        switch (logoutRequest)
        {
            case 1://exit
            case 2://restart

                if (Config.GetDelays.LogoutDelay > 0)
                {
                    var lastLogoutSec = Convert.ToInt32(DateTime.Now.Subtract(session.State.LogoutDelay).TotalSeconds);
                    if (lastLogoutSec < Config.GetDelays.LogoutDelay)
                    {
                        var logoutMsg = $"Logout delay: You must wait [{Config.GetDelays.LogoutDelay - lastLogoutSec}] sec to Logout again";

                         session.SendNotice(logoutMsg);
                        return new PacketResult(PacketResultType.Block);
                    }
                    session.State.LogoutDelay = DateTime.Now;
                }

                break;
            default:
                return new PacketResult(PacketResultType.Disconnect);
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}