using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult UnionInviteRequest(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);


        if (session.State.InSurvival)
            return new PacketResult(PacketResultType.Block);

        //if (Configs.Config.GetInGameLimits.MaxUnionGuilds > 0)
        //{
        //Program.DatabaseConnection.ChangeDatabase(Configs.Config.GetSql.ShardDatabase);

        var unionGuilds = (int)session.GetSql
                    .Read<int>(
                        $"use {Config.GetSql.ShardDatabase} SELECT Ally{Config.GetInGameLimits.MaxUnionGuilds} FROM _AlliedClans inner join _Guild ON _Guild.Alliance = _AlliedClans.ID inner join _Char ON _Char.GuildID = _Guild.ID where _Char.CharName16 = '{session.State.CharName}'")
                ;

            if (unionGuilds >= Config.GetInGameLimits.MaxUnionGuilds)
            {
                session.SendNotice("Union limit: You have reached the max concurrent Guilds!");
                return new PacketResult(PacketResultType.Block);
            }
       // }

        return new PacketResult(PacketResultType.Nothing);
    }
}