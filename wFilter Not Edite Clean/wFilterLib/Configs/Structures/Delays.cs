namespace wFilterLib.Configs.Structures;

public class Delays : Helper.IJsonSerializable
{
    public uint GlobalDelay { get; set; } = 0;
    public uint ReverseDelay { get; set; } = 0;
    public uint ResurrectionDelay { get; set; } = 0;
    public uint StallDelay { get; set; } = 0;
    public uint ExchangeDelay { get; set; } = 0;
    public uint ZerkDelay { get; set; } = 0;
    public uint LogoutDelay { get; set; } = 0;

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
