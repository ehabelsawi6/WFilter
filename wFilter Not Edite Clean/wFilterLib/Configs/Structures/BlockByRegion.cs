using System.Collections.Concurrent;
using wFilterLib.Helper;

namespace wFilterLib.Configs.Structures;

public class BlockByRegion : IJsonSerializable
{
    public List<int> ZerkRegions { get; set; } = new();
    public List<int> ReverseRegions { get; set; } = new();
    public List<int> PartyRegions { get; set; } = new();

    public ConcurrentDictionary<int, List<int>> Skills { get; set; } = new();
    public ConcurrentDictionary<int, List<int>> Scrolls { get; set; } = new();

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
