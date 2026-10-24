
using System.Collections.Concurrent;
using wFilterLib.Helper;

namespace wFilterLib.Configs.Structures;

public class PcLimit : IJsonSerializable
{
    public int Ip { get; set; } = 0;
    public int Account { get; set; } = 0;
    public int Arena { get; set; } = 0;
    public int Ctf { get; set; } = 0;
    public int Job { get; set; } = 0;
    public int Fw { get; set; } = 0;

    public ConcurrentDictionary<int, int> RegionPcLimit { get; set; } = new();

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
