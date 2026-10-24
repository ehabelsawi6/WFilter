namespace wFilterLib.Configs.Structures;

public class BadWords : Helper.IJsonSerializable
{
    public List<string> WordsList { get; set; } = new();

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
