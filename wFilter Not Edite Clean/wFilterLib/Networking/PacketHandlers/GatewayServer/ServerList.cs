using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;
using wFilterLib.Networking.PacketHandlers.GatewayServer.PacketStructure;

namespace wFilterLib.Networking.PacketHandlers.GatewayServer;

public class ServerList
{
    public static PacketResult HandleAck(Packet packet, PlayerSession session)
    {
        var serverListResponse = new ServerListResponse();
        serverListResponse.ReadPacket(packet);

        var settings = Config.GetLogin;

        foreach (var shard in serverListResponse.Shards)
        {
            if (settings.ServerName.Length > 0)
                shard.Name = settings.ServerName;

            if (settings.FakePlayers > 0)
                shard.OnlineCount += settings.FakePlayers;

            if (settings.MaxPlayers > 0)
                shard.Capacity = settings.MaxPlayers;
        }
        return new PacketResult(serverListResponse.WritePacket(), PacketResultType.Override);
    }

    public static PacketResult HandleReq(Packet packet, PlayerSession session)
    {
        if (packet.GetBytes().Length > 0 || !session.PatchSent)
            return new PacketResult(PacketResultType.Disconnect, "Client tried to send a wrong packet size(ServerList)");

        session.ServerListSent = true;

        return new PacketResult(PacketResultType.Nothing);
    }
}
