namespace wFilterLib.Configs.Structures;

public class Job : Helper.IJsonSerializable
{
    public bool DisableReverse { get; set; } = false;
    public bool DisableResScroll { get; set; } = false;
    public bool DisableZerk { get; set; } = false;
    public bool DisableTrace { get; set; } = false;
    public bool DisablePremiumReturn { get; set; } = false;
    public bool DisablePremiumReverse { get; set; } = false;
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
