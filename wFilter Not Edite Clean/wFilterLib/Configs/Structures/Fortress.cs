namespace wFilterLib.Configs.Structures;

public class Fortress : Helper.IJsonSerializable
{
    public bool DisableResScroll { get; set; } = false;
    public bool DisableZerk { get; set; } = false;
    public bool DisableTrace { get; set; } = false;
    public bool DisablePetRide { get; set; } = false;
    public List<int> DisableScrolls { get; set; } = new();

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
