namespace wFilterLib.Configs.Structures;

public class Login : Helper.IJsonSerializable
{
    public string ServerName { get; set; } = "wkFilter";
    public ushort MaxPlayers { get; set; } = 1000;
    public ushort FakePlayers { get; set; } = 0;
    public string CaptchaCode { get; set; } = "0";
    public bool AllowClientLess { get; set; } = false;
    public List<string> ExcludedAccounts { get; set; } = new();

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
