using wFilterLib.Configs.Structures;
using wFilterLib.Helper;
using wFilterLib.Networking.PacketStuff;

namespace wFilterLib.Configs;

public static class Settings
{
    static NLog.Logger logger = NLog.LogManager.GetLogger("Settings");

    public const string SqlPath = "Configs/Sql.json";
    public const string ModulesPath = "Configs/Modules.json";
    public const string ProtectionPath = "Configs/Protection.json";
    public const string LoginPath = "Configs/Login.json";
    public const string DelaysPath = "Configs/Delays.json";
    public const string InGameLimitsPath = "Configs/InGameLimits.json";
    public const string JobPath = "Configs/Job.json";
    public const string AcademyPath = "Configs/Academy.json";
    public const string FortressPath = "Configs/Fortress.json";
    public const string PcLimitsPath = "Configs/PcLimits.json";
    //public const string PetPath = "Configs/Pet.json";
    public const string TeleportPath = "Configs/Teleport.json";
    public const string ExtraPath = "Configs/Extra.json";
    public const string BlockedSkillsPath = "Configs/BlockedSkills.json";
    public const string BlockByRegionPath = "Configs/BlockByRegion.json";
    public const string SilkPerHourPath = "Configs/SilkPerHour.json";
   // public const string BadWordsPath = "Configs/BadWords.json";
    public const string GUISettingsPath = "Configs/GUISettings.json";
    public const string SurvivalEventPath = "Configs/SurvivalEvent.json";


    public static bool Load(ServerType serverType)
    {
        try
        {
            logger.Info("Loading Configs files...");

            if (!Directory.Exists("Configs"))
                Directory.CreateDirectory("Configs");



            #region Modules

            if (!File.Exists(ModulesPath))
            {
                logger.Warn($"{ModulesPath} was not found , Creating default file...");
                PersistenceHelper.WriteFile(Config.GetModules, ModulesPath);
            }

            Config.GetModules = PersistenceHelper.ReadFile<Modules>(ModulesPath);
            logger.Info($"{ModulesPath} loaded successfully !");

            #endregion

            #region Protection

            if (!File.Exists(ProtectionPath))
            {
                logger.Warn($"{ProtectionPath} was not found , Creating default file...");
                PersistenceHelper.WriteFile(Config.GetProtection, ProtectionPath);
            }

            Config.GetProtection = PersistenceHelper.ReadFile<Protection>(ProtectionPath);
            logger.Info($"{ProtectionPath} loaded successfully !");

            #endregion

            #region Login

            if (!File.Exists(LoginPath))
            {
                logger.Warn($"{LoginPath} was not found , Creating default file...");
                PersistenceHelper.WriteFile(Config.GetLogin, LoginPath);
            }

            Config.GetLogin = PersistenceHelper.ReadFile<Login>(LoginPath);
            logger.Info($"{LoginPath} loaded successfully !");

            #endregion



            if (serverType == ServerType.Agent)
            {
                #region PcLimits

                if (!File.Exists(PcLimitsPath))
                {
                    logger.Warn($"{PcLimitsPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetPcLimit, PcLimitsPath);
                }

                Config.GetPcLimit = PersistenceHelper.ReadFile<PcLimit>(PcLimitsPath);
                logger.Info($"{PcLimitsPath} loaded successfully !");

                #endregion

                #region Sql

                if (!File.Exists(SqlPath))
                {
                    logger.Warn($"{SqlPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetSql, SqlPath);
                }

                Config.GetSql = PersistenceHelper.ReadFile<Sql>(SqlPath);
                logger.Info($"{SqlPath} loaded successfully !");

                #endregion

                #region Delays

                if (!File.Exists(DelaysPath))
                {
                    logger.Warn($"{DelaysPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetDelays, DelaysPath);
                }

                Config.GetDelays = PersistenceHelper.ReadFile<Delays>(DelaysPath);
                logger.Info($"{DelaysPath} loaded successfully !");

                #endregion

                #region InGameLimits

                if (!File.Exists(InGameLimitsPath))
                {
                    logger.Warn($"{InGameLimitsPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetInGameLimits, InGameLimitsPath);
                }

                Config.GetInGameLimits = PersistenceHelper.ReadFile<InGameLimits>(InGameLimitsPath);
                logger.Info($"{InGameLimitsPath} loaded successfully !");

                #endregion

                #region Job

                if (!File.Exists(JobPath))
                {
                    logger.Warn($"{JobPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetJob, JobPath);
                }

                Config.GetJob = PersistenceHelper.ReadFile<Job>(JobPath);
                logger.Info($"{JobPath} loaded successfully !");

                #endregion

                #region Academy

                if (!File.Exists(AcademyPath))
                {
                    logger.Warn($"{AcademyPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetAcademy, AcademyPath);
                }

                Config.GetAcademy = PersistenceHelper.ReadFile<Academy>(AcademyPath);
                logger.Info($"{AcademyPath} loaded successfully !");

                #endregion

                #region Fortress

                if (!File.Exists(FortressPath))
                {
                    logger.Warn($"{FortressPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetFortress, FortressPath);
                }

                Config.GetFortress = PersistenceHelper.ReadFile<Fortress>(FortressPath);
                logger.Info($"{FortressPath} loaded successfully !");

                #endregion

                #region Pet

                //if (!File.Exists(PetPath))
                //{
                //    logger.Warn($"{PetPath} was not found , Creating default file...");
                //    PersistenceHelper.WriteFile(Config.GetPet, PetPath);
                //}

                //Config.GetPet = PersistenceHelper.ReadFile<Pet>(PetPath);
                //logger.Info($"{PetPath} loaded successfully !");

                #endregion

                #region Teleport

                if (!File.Exists(TeleportPath))
                {
                    logger.Warn($"{TeleportPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetTeleport, TeleportPath);
                }

                Config.GetTeleport = PersistenceHelper.ReadFile<Teleport>(TeleportPath);
                logger.Info($"{TeleportPath} loaded successfully !");

                #endregion

                #region Extra

                if (!File.Exists(ExtraPath))
                {
                    logger.Warn($"{ExtraPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetExtra, ExtraPath);
                }

                Config.GetExtra = PersistenceHelper.ReadFile<Extra>(ExtraPath);
                logger.Info($"{ExtraPath} loaded successfully !");

                #endregion

                #region BlockedSkills

                if (!File.Exists(BlockedSkillsPath))
                {
                    logger.Warn($"{BlockedSkillsPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetBlockedSkill, BlockedSkillsPath);
                }

                Config.GetBlockedSkill = PersistenceHelper.ReadFile<BlockedSkill>(BlockedSkillsPath);
                logger.Info($"{BlockedSkillsPath} loaded successfully !");

                #endregion

                #region BlockByRegion

                if (!File.Exists(BlockByRegionPath))
                {
                    logger.Warn($"{BlockByRegionPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetBlockByRegion, BlockByRegionPath);
                }

                Config.GetBlockByRegion = PersistenceHelper.ReadFile<BlockByRegion>(BlockByRegionPath);
                logger.Info($"{BlockByRegionPath} loaded successfully !");

                #endregion

                #region SilkPerHour

                if (!File.Exists(SilkPerHourPath))
                {
                    logger.Warn($"{SilkPerHourPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetSilkPerHour, SilkPerHourPath);
                }

                Config.GetSilkPerHour = PersistenceHelper.ReadFile<SilkPerHour>(SilkPerHourPath);
                logger.Info($"{SilkPerHourPath} loaded successfully !");

                #endregion

                #region BadWords

                //if (!File.Exists(BadWordsPath))
                //{
                //    logger.Warn($"{BadWordsPath} was not found , Creating default file...");
                //    PersistenceHelper.WriteFile(Config.GetBadWords, BadWordsPath);
                //}

                //Config.GetBadWords = PersistenceHelper.ReadFile<BadWords>(BadWordsPath);
                //logger.Info($"{BadWordsPath} loaded successfully !");

                #endregion

                #region GUI Settings 

                if (!File.Exists(GUISettingsPath))
                {
                    logger.Warn($"{GUISettingsPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetGUISettings, GUISettingsPath);
                }

                Config.GetGUISettings = PersistenceHelper.ReadFile<GUISettings>(GUISettingsPath);
                logger.Info($"{GUISettingsPath} loaded successfully !");

                #endregion

                #region Survival Event

                if (!File.Exists(SurvivalEventPath))
                {
                    logger.Warn($"{SurvivalEventPath} was not found , Creating default file...");
                    PersistenceHelper.WriteFile(Config.GetSurvivalEvent, SurvivalEventPath);
                }

                Config.GetSurvivalEvent = PersistenceHelper.ReadFile<SurvivalEvent>(SurvivalEventPath);
                logger.Info($"{SurvivalEventPath} loaded successfully !");

                #endregion
            }


            logger.Info("All Configs files has been loaded !");

            return true;
        }
        catch (Exception e)
        {
            logger.Fatal("Something went wront while loading configs files , please check log/error.log");

            logger.Error(e);
            return false;
        }

    }

    private static void Check()
    {

    }
}
