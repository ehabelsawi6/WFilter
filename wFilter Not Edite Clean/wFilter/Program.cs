using System.Net;
using wFilterLib.Networking;
using wFilterLib.Configs;
using wFilterLib;
using wFilterLib.Configs.Structures;
using wFilterLib.Database;
using wFilterLib.Events;
using wFilterLib.Helper;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.PacketHandlers;

namespace wkFilter;

internal class Program
{
    private static EventWaitHandle s_event;

    private static void Main(string[] args)
    {

        Console.Title = "wFilterV3 | Silkroad Packet Filter";


        //s_event = new EventWaitHandle(false,EventResetMode.ManualReset, "wFilterV3_Com", out var created);
        //if (!created)
        //{
        //    Console.WriteLine("wFilter is already running !");
        //    Console.Read();
        //  //  Environment.Exit(0);
        //}

        Console.WindowWidth = 120;
        Console.BufferHeight = Console.BufferHeight;

        //setup NLog config
        NLogConfig.Setup();

        //Load Config
        Settings.Load(ServerType.Agent);



        //Connect and Load sql tables

        Globals.Logger.Info("Connecting to database...");

        if (!SqlTables.Connect())
            Globals.Logger.Fatal("Couldn't connect to database , please check your config !");
        else
           SqlTables.Load();

        Globals.Logger.Info("Starting async servers...");
        //Start Services
        var modules = Config.GetModules;

        var gateway = new NewSilkroadServer(IPAddress.Parse(modules.PublicIp), modules.GatewayServer.PublicPort);
        gateway.Setup(new IPEndPoint(IPAddress.Parse(modules.GatewayServer.ModuleIp), modules.GatewayServer.ModulePort),
            ServerType.Gateway);

        RegisterGatewayHandlers.Setup(gateway.PacketManager);

        gateway.Start();


        var download = new NewSilkroadServer(IPAddress.Parse(modules.PublicIp), modules.DownloadServer.PublicPort);
        download.Setup(
            new IPEndPoint(IPAddress.Parse(modules.DownloadServer.ModuleIp), modules.DownloadServer.ModulePort),
            ServerType.Download);

        // RegisterGatewayHandlers.Setup(download.PacketManager);

        download.Start();


        var agent1 = new NewSilkroadServer(IPAddress.Parse(modules.PublicIp), modules.AgentServer1.PublicPort);
        agent1.Setup(new IPEndPoint(IPAddress.Parse(modules.AgentServer1.ModuleIp), modules.AgentServer1.ModulePort),
            ServerType.Agent);

        RegisterAgentHandlers.Setup(agent1.PacketManager);

        Globals.AgentServers.Add(agent1);
        agent1.Start();



        if (modules.AgentServer2.ModuleIp != "0")
        {
            var agent2 = new NewSilkroadServer(IPAddress.Parse(modules.PublicIp), modules.AgentServer2.PublicPort);
            agent2.Setup(
                new IPEndPoint(IPAddress.Parse(modules.AgentServer2.ModuleIp), modules.AgentServer2.ModulePort),
                ServerType.Agent);

            RegisterAgentHandlers.Setup(agent2.PacketManager);
            Globals.AgentServers.Add(agent2);
            agent2.Start();
        }

        Globals.UpdateStatus(ServerType.Gateway);
        Globals.UpdateStatus(ServerType.Agent);


        if (args.Count() > 1 && (int.Parse(args[2]) == 3 || int.Parse(args[2]) == 6)) //angelroad
            Config.IsAngelRoad = true;


      

        new Thread(ConsoleCommands).Start();
        var killCounter = new Thread(KillCounters.Initialize);
        killCounter.IsBackground = true;
        killCounter.Start();

       var survivalEvent = new Thread(Survival.Initialize);
       survivalEvent.IsBackground = true;
        survivalEvent.Start();

       var autoEvent = new Thread(AutoEventManager.Initialize);
       autoEvent.IsBackground = true;
        autoEvent.Start();


    }

    private static void ConsoleCommands()
    {
        while (true)
        {
            var cmd = Console.ReadLine()?.ToLower();

            switch (cmd)
            {
                case "/reload":
                    Settings.Load(ServerType.Agent);
                    if (SqlTables.Connect())
                        SqlTables.Load();
                    break;
                case "/count":
                    
                    break;
                case "/autoevent trivia":
                    AutoEventManager.StartTrivia();
                    break;
                case "/autoevent lottery":
                    AutoEventManager.StartLottery();
                    break;
                case "/autoevent luckynumber":
                    AutoEventManager.StartLuckyNumber();
                    break;
                case "/autoevent unique":
                    AutoEventManager.StartUniqueHunt();
                    break;
                case "/autoevent hideseek":
                    AutoEventManager.StartHideSeek();
                    break;
                case "/autoevent stop":
                    AutoEventManager.TryManualStart("stop");
                    break;
                default:
                    if (!string.IsNullOrEmpty(cmd) && cmd.StartsWith("/autoevent "))
                        AutoEventManager.TryManualStart(cmd.Replace("/autoevent ", ""));
                    break;
            }

            Thread.Sleep(100);
        }
    }
 
}