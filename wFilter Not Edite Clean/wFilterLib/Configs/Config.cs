using wFilterLib.Configs.Structures;

namespace wFilterLib.Configs;

public static class Config
{
    public static Sql GetSql = new();//
    public static Modules GetModules = new();//
    public static Protection GetProtection = new();
    public static Login GetLogin = new();//
    public static Delays GetDelays = new();//
    public static InGameLimits GetInGameLimits = new();//
    public static Job GetJob = new();
    public static Academy GetAcademy = new();
    public static Fortress GetFortress = new();
    public static PcLimit GetPcLimit = new();//
   // public static Pet GetPet = new();
    public static Teleport GetTeleport = new();
    public static Extra GetExtra = new();
    public static BlockedSkill GetBlockedSkill = new();
    public static BlockByRegion GetBlockByRegion = new();
    public static SilkPerHour GetSilkPerHour = new();
   // public static BadWords GetBadWords = new();
    public static GUISettings GetGUISettings = new();
    public static SurvivalEvent GetSurvivalEvent = new();

    //AngelRoad stuff
    public static bool IsAngelRoad = false;
   
}