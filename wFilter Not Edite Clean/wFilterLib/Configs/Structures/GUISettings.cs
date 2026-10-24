using wFilterLib.Database.Models;

namespace wFilterLib.Configs.Structures;

public class GUISettings : Helper.IJsonSerializable
{
    public bool TitleManager { get; set; } = false;
    public bool UniqueStatus { get; set; } = false;
    public bool EventTimes { get; set; } = false;
    public bool GrantName { get; set; } = false;
    public bool CustomTitle { get; set; } = false;
    public bool DynamicShop { get; set; } = false;
    public bool Facebook { get; set; } = false;
    public bool Discord { get; set; } = false;
    public bool Website { get; set; } = false;
    public string FacebookLink { get; set; } = "https://wFilter.online";
    public string DiscordLink { get; set; } = "https://wFilter.online";
    public string WebsiteLink { get; set; } = "https://wFilter.online";

    public List<Top5KillCounterData> KillCounters { get; set; } = new();

    public GlobalColors GlobalColors { get; set; } = new();


    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
