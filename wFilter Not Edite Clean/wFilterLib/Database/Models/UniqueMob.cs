namespace wFilterLib.Database.Models;

public class UniqueMob
{
    public byte PageID = 0;
    public byte LineID = 0;
    public string Status = "";
    public string Killer = "";
    public string Time = "";
}

public class UniqueNotifyData
{
    public uint RefObjId;
    public bool State;
    public string KillerName = "";
    public DateTime Time;
}