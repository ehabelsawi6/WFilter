using wFilterLib.Configs;

namespace wFilterLib.Database;

public static class SqlTables
{
    public static bool Connect() => Globals.XSql.Connect(string.Format(
                "Server={0};Database={1};User Id={2};Password={3};MultipleActiveResultSets=true;"
                , Config.GetSql.SqlServer,"wFilter", Config.GetSql.User, Config.GetSql.Password));

    public static bool Load()
    {
        try
        {
            Globals.Logger.Info("Loading database tables...");

            #region load regions

            Globals.XSql.LoadIntoList(Globals.ArenaRegions,
               $"use {Config.GetSql.ShardDatabase} SELECT wRegionID FROM dbo._RefRegion WHERE ContinentName LIKE 'ARENA_%'");
            Globals.XSql.LoadIntoList(Globals.FgwRegions,
               $"use {Config.GetSql.ShardDatabase} SELECT wRegionID FROM dbo._RefRegion WHERE ContinentName LIKE 'GOD_%'");
            Globals.XSql.LoadIntoList(Globals.FortressRegions,
               $"use {Config.GetSql.ShardDatabase} SELECT wRegionID FROM dbo._RefRegion WHERE ContinentName LIKE 'FORT_%'");
            Globals.XSql.LoadIntoList(Globals.TownsRegions,
               $"use {Config.GetSql.ShardDatabase} SELECT wRegionID FROM dbo._RefRegion WHERE IsBattleField = 0");
            Globals.XSql.LoadIntoList(Globals.FwTeleports,
               $"use {Config.GetSql.ShardDatabase} SELECT ID FROM _RefTeleport WHERE CodeName128 LIKE '%_FORT_%' AND GenWorldID !=1");
            Globals.XSql.LoadIntoList(Globals.SkillIds,
               $"use {Config.GetSql.ShardDatabase} select ID from _RefSkill where (Basic_Code like 'SKILL_CH_%' OR Basic_Code like 'SKILL_EU_%') and Param2 = 1701213281  and Service = 1 ");

            #endregion load regions


            Globals.XSql.LoadHwans();
            Globals.XSql.LoadObjects();
            Globals.XSql.LoadBlocked();
            Globals.XSql.LoadEventList();
            Globals.XSql.LoadCustomIcons();
            Globals.XSql.LoadGMLoginSecurity();
            Globals.XSql.LoadGMControl();
            Globals.XSql.LoadDShopTitlesList();

            Globals.XSql.Disconnect();

            Globals.Logger.Info("All database tables has been loaded !");

            return true;
        }
        catch (Exception e)
        {
            Globals.Logger.Error("Failed to load database tables !");
            Globals.Logger.Debug("Failed to load database tables!" + Environment.NewLine + e.ToString());
            return false;
        }
    }
}
