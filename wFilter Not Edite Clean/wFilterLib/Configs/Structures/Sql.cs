using wFilterLib.Helper;

namespace wFilterLib.Configs.Structures;

public class Sql : IJsonSerializable
{
    public string SqlServer { get; set; } = @"wegs";
    public string User { get; set; } = "sa";
    public string Password { get; set; } = "123456";
    public string AccountDatabase { get; set; } = "SRO_VT_ACCOUNT";
    public string ShardDatabase { get; set; } = "SRO_VT_SHARD";

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
