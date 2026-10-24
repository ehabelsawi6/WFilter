
namespace wFilterLib.Database.Models.DynamicShop;

public class M_Titles
{
  //  public int Id { get; set; }
    public int TitleId { get; set; }
    public int Price { get; set; }
}

public class M_Colors
{
    //  public int Id { get; set; }
    public int NameColorPrice { get; set; }
    public int TitleColorPrice { get; set; }
    public int CustomTitlePrice { get; set; }
}