using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult BArenaRequest(Packet packet, PlayerSession session)
    {
        if (session.State.CharName.Length < 1)
            return new PacketResult(PacketResultType.Disconnect);
        
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        #region Arena Require Level

        if (Config.GetInGameLimits.ArenaRegisterLevel > 0)
        {
            if (Config.GetInGameLimits.ArenaRegisterLevel > session.State.CurLevel)
            {
                const string battleArena =
                    "You are low level, you need at least level ({level}) to register in Battle Arena.";

                 session.SendNotice(battleArena.Replace("{level}",
                    Config.GetInGameLimits.ArenaRegisterLevel.ToString()));
                return new PacketResult(PacketResultType.Block);
            }
        }

        #endregion

        var register = packet.ReadByte();


        switch (register)
        {
            case 1: //register
                packet.ReadByte();
                packet.ReadByte();

                if (Config.GetPcLimit.Account > 0 && Config.GetPcLimit.Arena > 0 && !Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
                {
                    var count = SessionManager.GetArenaSessionCountForHwid(session.State.Hwid);

                    if (count + 1 > Config.GetPcLimit.Arena)
                    {
                         session.SendNotice("You have exceeded the maximum Arena Limit on this PC");
                        return new PacketResult(PacketResultType.Block);
                    }
                }

                break;
            case 2: //Cancel
                break;

        }


        return new PacketResult(PacketResultType.Nothing);
    }
}

//0x74D2 - CLIENT_AGENT_BARENA_REQUEST

//1    byte register // 1 = Register, 2 = Cancel
//if (register == 1)
//{
//    1    byte barenaGameType
//    1    byte barenaMatchType
//}