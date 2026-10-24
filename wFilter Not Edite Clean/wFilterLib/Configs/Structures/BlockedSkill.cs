using wFilterLib.Helper;

namespace wFilterLib.Configs.Structures;

public class BlockedSkill : IJsonSerializable
{
    public List<int> EveryWhere { get; set; } = new();
    public List<int> Job { get; set; } = new();
    public List<int> Fortress { get; set; } = new();
    public List<int> Fgw { get; set; } = new();
    public List<int> Arena { get; set; } = new();
    public List<int> Ctf { get; set; } = new();

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
