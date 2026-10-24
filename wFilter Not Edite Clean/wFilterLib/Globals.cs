using System.Collections.Concurrent;
using wFilterLib.Database;
using wFilterLib.Database.Models;
using wFilterLib.Helper;
using wFilterLib.Networking;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session;

namespace wFilterLib;

public static class Globals
{
    public static NLog.Logger Logger = NLog.LogManager.GetLogger("Main");

    public static string ServerName = "wfilter";
    public static string ServerId = "0";

    public static List<NewSilkroadServer> AgentServers = new();
    public static ConcurrentDictionary<uint, PlayerStatus> PlayerStatus = new();
    public static ConcurrentDictionary<string?, Blocked> BlockData = new();

    public static List<UniqueNotifyData> UniquesData = new();


    public static ConcurrentDictionary<int, EventTime> EventTimeList = new();
    public static ConcurrentDictionary<string, string> CustomTitleList = new();
    public static ConcurrentDictionary<byte, uint> TitlesColor = new();
    public static ConcurrentDictionary<string, uint> CharNameColor = new();
    public static ConcurrentDictionary<byte, RefHWANLevel> RefHwan = new();
    public static ConcurrentDictionary<uint, RefObjCommon> RefObjCommon = new();
    public static ConcurrentDictionary<int, string> CustomIcons = new();
    public static ConcurrentDictionary<string, string> GMSecurityList = new();
    public static ConcurrentDictionary<string, GMControl> GMControlList = new();

    //Dynamic Shop
    public static ConcurrentDictionary<int, Database.Models.DynamicShop.M_Titles> DShopTitlesList = new();
    public static int DShopNameColorPrice = 0;
    public static int DShopTitleColorPrice = 0;
    public static int DShopCustomTitlePrice = 0;

    public static List<int> ArenaRegions = new();
    public static List<int> FgwRegions = new();
    public static List<int> FortressRegions = new();
    public static List<int> TownsRegions = new();

    public static List<int> FwTeleports = new();

    public static List<int> SkillIds = new();


    public static XSql XSql = new();
    
    
    public static bool RollTheDice = false;
    public static DateTime RollDiceLastTime = DateTime.Now.AddDays(-1);
    public static List<string> RollDiceCharList = new List<string>();

    #region Events


    #region Survival

    public static bool SurvivalEvent = false;
    public static bool SurvivalEventRegister = false;

    public static List<string> SurvivalEventRegisteredCharacters = new();
    public static DateTime SurvivalStartTime = DateTime.MinValue;
    
    #endregion


    #endregion

    public static void UpdateStatus(ServerType serverType)
    {
        //var gateway = SessionManager.GatewaySessionCount;
        //var agent = SessionManager.AgentSessionCount;
        //Console.Title = $"[wFilter V3] | Gateway({gateway}) Agent({agent}) | ServerName:{ServerName} | ServerId:{ServerId}";

        if (serverType == ServerType.Gateway)
        {
            var gateway = SessionManager.GatewaySessionCount;
            Console.Title = $"[wFilter V3 - Gateway] | Connections({gateway})";
        }
        else if (serverType == ServerType.Agent)
        {
            var agent = SessionManager.AgentSessionCount;
            Console.Title = $"[wFilter V3 - Agent] | Connections({agent})";

        }
        else if (serverType == ServerType.Download)
        {
            var download = SessionManager.DownloadSessionCount;
            Console.Title = $"[wFilter V3 - Download] | Connections({download})";

        }

    }







    #region AngelRoad

    public static void RollTheDiceNormal()
    {
        Thread.Sleep(60000);

        Random random = new Random();
        int randomPos = random.Next(Globals.RollDiceCharList.Count);

        XSql.ExecuteNonQuery($"exec ilegendbot..GiveReward 'silk','{Globals.RollDiceCharList[randomPos]}',{Globals.RollDiceCharList.Count}");

        XSql.ExecuteNonQuery($"insert into ilegendbot..iLegend_Tool (Service,Type,Message,Date) values (1,'Notice','[{Globals.RollDiceCharList[randomPos]}] has won Roll The Dice and got [{Globals.RollDiceCharList.Count}] silk(s)',GETDATE())");


        //  AgentContext.SendNoticeOnline($"[{FilterMain.RollDiceCharList[randomPos]}] has won Roll The Dice and got [{FilterMain.RollDiceCharList.Count}] silk(s)");
        // AgentContext2.SendNoticeOnline($"[{FilterMain.RollDiceCharList[randomPos]}] has won Roll The Dice and got [{FilterMain.RollDiceCharList.Count}] silk(s)");

        Globals.RollDiceCharList.Clear();
        Globals.RollTheDice = false;
        Globals.RollDiceLastTime = DateTime.Now.AddDays(1);
    }

    public static void RollTheDiceGM()
    {
        Thread.Sleep(60000);

        Random random = new Random();
        int randomPos = random.Next(Globals.RollDiceCharList.Count);

      
        XSql.ExecuteNonQuery($"exec ilegendbot..GiveReward 'silk','{Globals.RollDiceCharList[randomPos]}',{Globals.RollDiceCharList.Count}");

        XSql.ExecuteNonQuery($"insert into ilegendbot..iLegend_Tool (Service,Type,Message,Date) values (1,'Notice','[{Globals.RollDiceCharList[randomPos]}] has won Roll The Dice and got [{Globals.RollDiceCharList.Count}] silk(s)',GETDATE())");


        //  AgentContext.SendNoticeOnline($"[{FilterMain.RollDiceCharList[randomPos]}] has won Roll The Dice and got [{FilterMain.RollDiceCharList.Count}] silk(s)");
        // AgentContext2.SendNoticeOnline($"[{FilterMain.RollDiceCharList[randomPos]}] has won Roll The Dice and got [{FilterMain.RollDiceCharList.Count}] silk(s)");

        Globals.RollDiceCharList.Clear();
        Globals.RollTheDice = false;
     //   Globals.RollDiceLastTime = DateTime.Now.AddDays(1);
    }

    #endregion
}
