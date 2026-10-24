using Newtonsoft.Json;

namespace wFilterLib.Configs.Structures;

public class Modules : Helper.IJsonSerializable
{

    public string PublicIp = "167.233.214.148";
    public Module GatewayServer { get; set; } = new("GatewayServer");
    public Module DownloadServer { get; set; } = new("DownloadServer");

    public Module AgentServer1 { get; set; } = new("AgentServer(1)");
    public Module AgentServer2 { get; set; } = new("AgentServer(2)");

    public bool Blowfish = true;
    public bool SecurityBytes = true;
    public bool Handshake = true;

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}

public class Module
{

    private readonly string _moduleName;

    public string ModuleName()
    {
        return _moduleName;
    }

    public Module(string moduleName)
    {
        _moduleName = moduleName;
    }

    /// <summary>
    /// Module Settings
    /// </summary>
    public string ModuleIp { get; set; } = "167.233.214.148";

    public ushort ModulePort { get; set; } = 0;
    public ushort PublicPort = 0;
}