using System.Text.Json.Serialization;

namespace wFilterLib.Configs.Structures;

public class Gui : Helper.IJsonSerializable
{
    public bool EnableGui = true;

    public bool GuiGrantName = true;
    public bool GuiUniqueHistory = true;
    //  [JsonIgnore]
    public bool GuiCustomTitle = true;
    public bool GuiSwitchTitle = true;
    [JsonIgnore]
    public bool GuiCharacterLock = false;
    //   [JsonIgnore]
    public bool GuiEventTimer = false;
    [JsonIgnore]
    public bool GuiRank = false;
    [JsonIgnore]
    public bool GuiRender = true;
    public bool GuiGlobalColor = false;

    public GlobalColors GlobalColorsIds = new();

    public string DiscordLink = "https://discord.gg/UxxDsEw2RS";
    public string FacebookLink = "https://discord.gg/UxxDsEw2RS";
    public string WebLink = "https://wfilter.online";

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
