using System.Net;
using System.Net.Sockets;
using wkFilter.Database;
using wkFilter.Networking.PacketStuff;
using wkFilter.Networking.Session;

namespace wkFilter.Networking;

public class SilkroadServer
{
    public IPEndPoint serverEp;
    public ServerType SrvType;

    Thread m_accept_thread;
    //Thread m_poll_thread;

    AutoResetEvent m_connection_completed = new(false);
    bool m_is_running;
    bool m_is_stopped;
    readonly Socket listenerSocket;

    IPEndPoint bindEp;
    public string BindIp { get { return bindEp.Address.ToString(); } }
    public int BindPort { get { return bindEp.Port; } }

    public PacketManager PacketManager;
    public XSql GetSql;

    public SilkroadServer(IPEndPoint bindEp, IPEndPoint serverEp, ServerType serverType)
    {
        listenerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        listenerSocket.NoDelay = true;

        this.bindEp = bindEp;
        this.serverEp = serverEp;
        this.SrvType = serverType;

        PacketManager = new(serverType);
        GetSql = new();

        GetSql.Connect(string.Format(
                "Server={0};Database={1};User Id={2};Password={3};MultipleActiveResultSets=true;"
                , Configs.Config.GetSql.SqlServer, Configs.Config.GetSql.ShardDatabase, Configs.Config.GetSql.User, Configs.Config.GetSql.Password));
        GetSql.Disconnect();
    }

    public bool Start()
    {
        if (m_is_stopped)
        {
            throw new Exception("This server object was already used. Create new.");
        }

        try
        {
            listenerSocket.Bind(bindEp);
        }
        catch (SocketException)
        {
            Globals.Logger.Error( "Failed to start server because of BIND error");
            return false;
        }

        try
        {
            listenerSocket.Listen(5);
        }
        catch (SocketException)
        {
            Globals.Logger.Error("Failed to start server because of LISTEN error");
            return false;
        }

        m_accept_thread = new Thread(AcceptClientWorker);
        m_accept_thread.IsBackground = true;
        // m_poll_thread = new Thread(UserContextPollWorker);


        Globals.Logger.Info($"Server started [{bindEp}] -> [{serverEp}] Type [{SrvType}]");
        m_is_running = true;

        m_accept_thread.Start();
        //m_poll_thread.Start();

        return true;
    }

    void AcceptClientWorker()
    {
        while (m_is_running)
        {
            try
            {
                //m_connection_completed.Reset();
                listenerSocket.BeginAccept(new AsyncCallback(OnAcceptCallback), null);
                m_connection_completed.WaitOne();

            }
            catch (Exception e)
            {
                Globals.Logger.Error($"Failed to BeginAccept on server [{bindEp}]", bindEp);
                Globals.Logger.Debug($"Failed to BeginAccept on server [{ bindEp}] --> {e}");
                //  Global.logmgr.WriteLog(LogLevel.Warning, "Failed to BeginAccept on server [{0}]", m_bind_addr);
            }
        }
    }

    void OnAcceptCallback(IAsyncResult iar)
    {
        m_connection_completed.Set();

        try
        {
            var playerSocket = listenerSocket.EndAccept(iar);

            var playerSession = new PlayerSession(this,playerSocket);
            playerSession.Start();
        }
        catch(Exception e)
        {
            Globals.Logger.Error($"Failed OnAcceptCallback");
            Globals.Logger.Debug($"Failed OnAcceptCallback --> {e}");
        }
    }
}