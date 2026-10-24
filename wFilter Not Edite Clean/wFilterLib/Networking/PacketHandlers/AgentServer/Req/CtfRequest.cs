using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult CtfRegisterRequest(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);


        #region CtfRegister Require Level

        if (Config.GetInGameLimits.CtfRegisterLevel > 0)
        {
            if (Config.GetInGameLimits.CtfRegisterLevel > session.State.CurLevel)
            {
                const string captureTheFlag =
                    "You are low level, you need at least level ({level}) to register in Capture The Flag.";

                 session.SendNotice(captureTheFlag.Replace("{level}",
                    Config.GetInGameLimits.CtfRegisterLevel.ToString()));
                return new PacketResult(PacketResultType.Block);
            }
        }

        #endregion

        session.State.CtfRegistered = true;

        return new PacketResult(PacketResultType.Nothing);
    }
}