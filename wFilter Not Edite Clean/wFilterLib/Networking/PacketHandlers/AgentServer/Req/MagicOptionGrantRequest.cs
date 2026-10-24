using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult MagicOptionGrantRequest(Packet packet, PlayerSession session)
    {
        var blue = packet.ReadAscii();

        var blues = new string[14];

        blues[0] = "MATTR_STR_AVATAR";
        blues[1] = "MATTR_INT_AVATAR";
        blues[2] = "MATTR_AVATAR_STR";
        blues[3] = "MATTR_AVATAR_INT";
        blues[4] = "MATTR_AVATAR_HR";
        blues[5] = "MATTR_AVATAR_ER";
        blues[6] = "MATTR_AVATAR_HP";
        blues[7] = "MATTR_AVATAR_MP";
        blues[8] = "MATTR_AVATAR_DRUA";
        blues[9] = "MATTR_AVATAR_DARA";
        blues[10] = "MATTR_AVATAR_MDIA";
        blues[11] = "MATTR_AVATAR_HPRG";
        blues[12] = "MATTR_AVATAR_MPRG";
        blues[13] = "MATTR_AVATAR_LUCK";
        if (!blues.Any(blue.Contains))
            return new PacketResult(PacketResultType.Block);


        return new PacketResult(PacketResultType.Nothing);
    }
}