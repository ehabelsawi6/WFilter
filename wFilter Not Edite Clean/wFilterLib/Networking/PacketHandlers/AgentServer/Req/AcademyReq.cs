using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult AcademyCreateRequest(Packet pck, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (!Config.GetAcademy.DisableAcademyCreate)
            return new PacketResult(PacketResultType.Nothing);
        session.SendNotice("[Academy Create] Sorry the service isn't available");
        return new PacketResult(PacketResultType.Block);
    }

    public static PacketResult AcademyInviteRequest(Packet pck, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (!Config.GetAcademy.DisableAcademyInvite)
            return new PacketResult(PacketResultType.Nothing);
        session.SendNotice("[Academy Invite] Sorry the service isn't available");
        return new PacketResult(PacketResultType.Block);
    }

    public static PacketResult AcademyJoinRequest(Packet pck, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (!Config.GetAcademy.DisableAcademyJoin)
            return new PacketResult(PacketResultType.Nothing);
        session.SendNotice("[Academy Join] Sorry the service isn't available");
        return new PacketResult(PacketResultType.Block);
    }

    public static PacketResult AcademyKickRequest(Packet pck, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (!Config.GetAcademy.DisableAcademyBan)
            return new PacketResult(PacketResultType.Nothing);
        session.SendNotice("[Academy Ban] Sorry the service isn't available");
        return new PacketResult(PacketResultType.Block);
    }

    public static PacketResult AcademyLeaveRequest(Packet pck, PlayerSession session)
    {
        if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            return new PacketResult(PacketResultType.Nothing);

        if (!Config.GetAcademy.DisableAcademyLeave)
            return new PacketResult(PacketResultType.Nothing);
        session.SendNotice("[Academy Leave] Sorry the service isn't available");
        return new PacketResult(PacketResultType.Block);
    }
}
