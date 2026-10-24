namespace wFilterLib.Database.Models;

public class RefHWANLevel
{
    public byte HwanLevel { get; set; } //(tinyint, not null)
    public string Title_CH70 { get; set; } //(varchar(70), null)
    public string Title_EU70 { get; set; } //(varchar(70), null)
}