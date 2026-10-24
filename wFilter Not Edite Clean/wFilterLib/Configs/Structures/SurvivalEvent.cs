namespace wFilterLib.Configs.Structures;

public partial class SurvivalEvent : Helper.IJsonSerializable
{
    public bool Enable { get; set; } = false;
    public int MinPlayers { get; set; } = 2;
    public int MaxPlayers { get; set; } = 30;
    public bool BlockZerk { get; set; } = false;
   // public int TeleportId { get; set; } = 0;
    public byte RequireLevel { get; set; } = 0;
    public int PlayingDuration { get; set; } = 30;
    public int RegisterDuration { get; set; } = 10;

    public int RegionId { get; set; } = 25580;
    public int PosX { get; set; } = 0;
    public int PosY { get; set; } = 0;
    public int PosZ { get; set; } = 0;

    #region Reward

    public RewardTypes RewardType { get; set; } = RewardTypes.Silk;
    public int RewardCount { get; set; } = 1;

    public enum RewardTypes
    {
        Gold,
        Silk,
        Item
    }

    public string RewardCodeName { get; set; } = "";

    #endregion

    #region Schedule

    public List<StartTime> Schedules { get; set; } = new();

    #endregion

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}

