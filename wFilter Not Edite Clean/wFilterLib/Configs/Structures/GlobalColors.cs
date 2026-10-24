namespace wFilterLib.Configs.Structures;

public class GlobalColors : Helper.IJsonSerializable
{
    public int Green { get; set; } = 0;
    public int Blue { get; set; } = 0;
    public int Crimson { get; set; } = 0;
    public int Purple { get; set; } = 0;
    public int Orange { get; set; } = 0;
    public int DarkCyan { get; set; } = 0;
    public int Red { get; set; } = 0;

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
