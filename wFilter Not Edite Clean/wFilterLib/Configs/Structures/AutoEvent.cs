namespace wFilterLib.Configs.Structures;

public class AutoEvent : Helper.IJsonSerializable
{
    public bool Enable { get; set; } = false;
    public bool RunOneEventAtATime { get; set; } = true;
    public int RewardAmount { get; set; } = 1;
    public string RewardSilkType { get; set; } = "Own";
    public int AnswerTimeoutMinutes { get; set; } = 5;

    public TriviaSettings Trivia { get; set; } = new();
    public LotterySettings Lottery { get; set; } = new();
    public LuckyNumberSettings LuckyNumber { get; set; } = new();
    public UniqueHuntSettings UniqueHunt { get; set; } = new();
    public HideSeekSettings HideSeek { get; set; } = new();

    public string Dump()
    {
        throw new NotImplementedException();
    }

    public bool GenerateDefaults()
    {
        throw new NotImplementedException();
    }
}

public class TriviaSettings
{
    public bool Enable { get; set; } = true;
    public int Rounds { get; set; } = 1;
    public List<StartTime> Schedules { get; set; } = new();
    public List<TriviaQuestion> Questions { get; set; } = new()
    {
        new() { Question = "What is the first town in Silkroad?", Answer = "jangan" },
        new() { Question = "What town is in the hot desert?", Answer = "hotan" },
        new() { Question = "What town is known as the snow town?", Answer = "donwhang" },
        new() { Question = "What is the job of a trader?", Answer = "trade" },
        new() { Question = "How many degrees are in a circle?", Answer = "360" },
        new() { Question = "What is 7 x 8?", Answer = "56" }
    };
}

public class TriviaQuestion
{
    public string Question { get; set; } = "";
    public string Answer { get; set; } = "";
}

public class LotterySettings
{
    public bool Enable { get; set; } = true;
    public int RegisterDurationMinutes { get; set; } = 2;
    public int MinPlayers { get; set; } = 2;
    public List<StartTime> Schedules { get; set; } = new();
}

public class LuckyNumberSettings
{
    public bool Enable { get; set; } = true;
    public int MinNumber { get; set; } = 1;
    public int MaxNumber { get; set; } = 100;
    public List<StartTime> Schedules { get; set; } = new();
}

public class UniqueHuntSettings
{
    public bool Enable { get; set; } = true;
    public int DurationMinutes { get; set; } = 30;
    public List<StartTime> Schedules { get; set; } = new();
}

public class HideSeekSettings
{
    public bool Enable { get; set; } = true;
    public int DurationMinutes { get; set; } = 10;
    public List<StartTime> Schedules { get; set; } = new();
    public List<HideSeekLocation> Locations { get; set; } = new()
    {
        new() { Hint = "I am hiding near Donwhang town", RegionId = 26265 },
        new() { Hint = "I am hiding in the survival arena", RegionId = 25580 }
    };
}

public class HideSeekLocation
{
    public string Hint { get; set; } = "";
    public int RegionId { get; set; }
}
