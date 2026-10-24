using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult GuildInviteRequest(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);
        if (Config.GetSurvivalEvent.Enable)
            if (session.State.InSurvival)
                return new PacketResult(PacketResultType.Block);

        if (Config.GetInGameLimits.MaxGuildUsers > 0)
        {
            //Program.DatabaseConnection.ChangeDatabase(Configs.Config.GetSql.ShardDatabase);

            var guildMembers = (int) session.GetSql.Read<int>(
                    $"use {Config.GetSql.ShardDatabase} SELECT COUNT(*) FROM _GuildMember inner join _Guild ON _Guild.ID = _GuildMember.GuildID inner join _Char ON _Char.GuildID = _Guild.ID where _Char.CharName16 = '{session.State.CharName}'")
                ;

            if (guildMembers >= Config.GetInGameLimits.MaxGuildUsers)
            {
                 session.SendNotice("Guild Limit: You have reached the max concurrent members!");
                return new PacketResult(PacketResultType.Block);
            }
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}