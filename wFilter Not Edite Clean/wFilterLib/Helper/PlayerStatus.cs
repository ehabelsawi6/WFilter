using wFilterLib.Networking.Session;
using wFilterLib.Networking.Session.Classes;
using wFilterLib.Networking.Session.Struct;

namespace wFilterLib.Helper;

public class PlayerStatus
{
    public string? UserName { get; set; }
    public string? CharName { get; set; }
    public string? Ip { get; set; }
    public string? HardwareId { get; set; }
    public bool IsClientLess { get; set; }
    public int Level { get; set; }
    public JobType JobType { get; set; }
    public GamePosition? Position { get; set; }
    public DateTime LoggedTime { get; set; }

    public void Update(PlayerSession? session)
    {
        if (session?.State == null) return;
        
        UserName = session.State?.UserName;
        CharName = session.State?.CharName;
        Ip = session.State?.Ip;
        HardwareId = session.State?.Hwid;
            
        IsClientLess = session.State.IsClientLess;
        Level = session.State.CurLevel;
        JobType = session.State.JobType;
        Position = session.State?.Position;
        //LoggedTime = session.State?.UserName;
    }
}

public class Blocked
{
    public uint Id { get; set; } //(int, not null)
                                 //  public WBlockType Type { get; set; } //(tinyint, not null)
    public string? IpOrHwid { get; set; } //(varchar(100,not null)
    public DateTime EndDate { get; set; } //(DateTime,not null)
}
