namespace wFilterLib.Database.Models;

public class RefObjCommon
{
    public uint ID { get; set; } //(int, not null)
                                 // public string CodeName128 { get; set; } //(varchar(129), not null)
                                 // public string NameStrID128 { get; set; } //(varchar(129), not null)
                                 //  public byte Bionic { get; set; } //(tinyint, not null)
    public byte TypeID1 { get; set; } //(tinyint, not null)
    public byte TypeID2 { get; set; } //(tinyint, not null)
    public byte TypeID3 { get; set; } //(tinyint, not null)
    public byte TypeID4 { get; set; } //(tinyint, not null)
                                      //  public byte Rarity { get; set; } //(tinyint, not null)
                                      // public byte CashItem { get; set; } //(tinyint, not null)

}
