namespace wFilterLib.Database.Models;

public class GlobalLinking
{
    public ulong ID64 { get; set; }
    public uint RefItemID { get; set; }
    public uint OptLevel { get; set; }
    public ulong Variance { get; set; }
    public int Data { get; set; }
    public uint MagParamNum { get; set; }
    public List<ulong> MagParamList = new();
}

public class PetInfo
{
    public uint State { get; set; }
    public uint RefCharID { get; set; }
    public uint RentTime { get; set; }
    public string PetName = string.Empty;
}

public struct SocketData
{
    public byte nSlot;
    public int nOptID;
    public byte nOptLvl;
    public int nParam1;
    public int nParam2;
}

public struct AdvData
{
    public byte nSlot;
    public int nOptID;
    public int nOptValue;
}