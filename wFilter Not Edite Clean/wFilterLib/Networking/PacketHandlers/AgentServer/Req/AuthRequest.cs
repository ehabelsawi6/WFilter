using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult LoginRequest(Packet packet, PlayerSession session)
    {
        var tokenId = packet.ReadUInt();
        var userName = packet.ReadAscii();

        //if (!Globals.PlayerStatus.ContainsKey(tokenId))
        //    return new PacketResult(PacketResultType.Disconnect);

        session.State.UserName = wFilterLib.Helper.Utility.CleanString(userName).ToLower();
        session.State.TokenId = tokenId;
        
        
       

        //if (Configs.Config.GetLogin.AllowClientLess)
        //    session.State.IsClientLess = Globals.PlayerStatus[tokenId].IsClientLess;

        //Globals.PlayerStatus[tokenId].UserName = session.State.UserName;
        //Globals.PlayerStatus[tokenId].CurIp = session.State.Ip;

        return new PacketResult(PacketResultType.Nothing);
    }
}