namespace wFilterLib.Configs.Structures;

public class Protection : Helper.IJsonSerializable
{
    public int BytesPerSec = 1000;
    public int PacketPerSec = 30;
    public bool FirewallBan = false;

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
