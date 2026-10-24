using wFilterLib.Database;

namespace wFilterLib;

public struct KillCounterData
{
    public int ID;
    public string CharName16;
    public int Kills;
};

public class KillCounters
{
    public static void Initialize()
    {
        while (true)
        {
            if (SqlTables.Connect())
                KillCounterCallback();
            // FTWCounterCallback();
            Thread.Sleep(10000);
        }
    }

    static void KillCounterCallback()
    {
        Globals.XSql.KillCounter();
    }

    void FTWCounterCallback()
    {

    }
}
