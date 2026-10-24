namespace wFilterLib.Events;

public interface IWEvent
{
    public string Name { get; set; }
    public bool Active { get; set; }
    public int Rounds { get; set; }
    public int CurrentRound { get; set; }
    public Task Setup(string name,int rounds);
    public Task Start();
    public Task Round();
   // public Task RoundRepeat();
    public Task End();
    public Task Reward();
}

public class Setting
{
    public int Rounds { get; set; } = 1;
    
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
}