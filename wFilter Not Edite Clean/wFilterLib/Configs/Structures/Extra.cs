using wFilterLib.Helper;

namespace wFilterLib.Configs.Structures;

public class Extra : IJsonSerializable
{
    public string WelcomeMessage = "Welcome [{playername}] To [{servername}]";

    public bool DisableStallOutSideTown { get; set; } = false;
    public bool DisableDropItemInTown { get; set; } = false;
    public bool BlockPHBot { get; set; } = false;
    public bool DisableAlchemySystem { get; set; } = false;
    public bool EnablePlusNotice { get; set; } = true;
    public byte PlusNoticeMinPlus { get; set; } = 1;
    public byte PlusNoticeColor { get; set; } = 0;
    public string PlusNoticeMessage { get; set; } = "[{player}] has successfully enhanced an item to +{plus}!";
    public bool DisableZerkPetRide { get; set; } = false;
    public List<string> BadWords { get; set; } = new();
    public List<int> DisableScrollsOutSideTown { get; set; } = new();
    public List<int> AutoCapeRegions { get; set; } = new();
    public List<int> DisableExcStallRestartExitByRegion { get; set; } = new();
    public List<ushort> ExtraOpcodesWhiteList { get; set; } = new();

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}
