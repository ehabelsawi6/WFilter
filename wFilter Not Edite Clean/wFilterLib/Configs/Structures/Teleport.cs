using System.Collections.Concurrent;

namespace wFilterLib.Configs.Structures;

public class Teleport : Helper.IJsonSerializable
{
    public ConcurrentDictionary<uint, List<TeleportProp>> TeleportByTime { get; set; } = new();
    public List<uint> ThiefOnlyTeleports { get; set; } = new() /*{1000, 2000, 3000}*/;
    public List<uint> HunterOnlyTeleports { get; set; } = new() /*{1000, 2000, 3000}*/;
    public List<uint> TraderOnlyTeleports { get; set; } = new() /*{1000, 2000, 3000}*/;

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}

public class TeleportProp
{
    public string Start { get; set; } = "12:10 PM";
    public string End { get; set; } = "12:20 PM";
}

