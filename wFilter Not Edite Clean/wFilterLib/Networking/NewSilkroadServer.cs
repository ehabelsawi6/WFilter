using System.Net;
using System.Net.Sockets;
using wFilterLib.Networking.NetCoreServer;
using wFilterLib.Configs;
using wFilterLib.Database;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session;

namespace wFilterLib.Networking;

public class NewSilkroadServer : TcpServer
{
    #region Properties

    public IPEndPoint ServerEp;
    public ServerType SrvType;

    public PacketManager PacketManager;
    public XSql GetSql;

    #endregion


    public NewSilkroadServer(IPAddress address, int port) : base(address, port) { }

    public void Setup(IPEndPoint serverEp, ServerType serverType)
    {
        this.ServerEp = serverEp;
        SrvType = serverType;

        PacketManager = new(serverType);
        GetSql = new();

        GetSql.Connect(string.Format(
                "Server={0};Database={1};User Id={2};Password={3};MultipleActiveResultSets=true;"
                , Config.GetSql.SqlServer, Config.GetSql.ShardDatabase, Config.GetSql.User, Config.GetSql.Password));
        GetSql.Disconnect();
    }

    protected override TcpSession CreateSession() { return new PlayerSession(this); }


    protected override void OnStarted()
    {
        Globals.Logger.Info($"{SrvType} Started Successfully On {Address}:{Port}");
    }

    protected override void OnError(SocketError error)
    {
        Globals.Logger.Error($"TCP server caught an error with code {error}");
    }
}
