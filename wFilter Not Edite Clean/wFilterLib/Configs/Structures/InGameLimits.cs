namespace wFilterLib.Configs.Structures;

public class InGameLimits : Helper.IJsonSerializable
{
    public byte MaxPlus { get; set; } = 0;
    public byte MaxDevilPlus { get; set; } = 0;
    public byte MaxGuildUsers { get; set; } = 0;
    public byte MaxUnionGuilds { get; set; } = 0;
    public byte ArenaRegisterLevel { get; set; } = 0;
    public byte CtfRegisterLevel { get; set; } = 0;
    public byte GlobalRequireLevel { get; set; } = 0;
    public byte ReverseRequireLevel { get; set; } = 0;
    public byte StallRequireLevel { get; set; } = 0;
    public byte ResurrectionRequireLevel { get; set; } = 0;

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
