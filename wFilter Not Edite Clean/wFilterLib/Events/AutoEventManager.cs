using wFilterLib.Configs;
using wFilterLib.Configs.Structures;
using wFilterLib.Networking.Session;

namespace wFilterLib.Events;

public static class AutoEventManager
{
    private static readonly object LockObj = new();
    private static readonly HashSet<string> FiredKeys = new();
    private static readonly Random Rng = new();

    public static bool Busy;
    public static string CurrentEvent = "";

    public static bool TriviaActive;
    public static string TriviaAnswer = "";
    public static string TriviaWinner = "";

    public static bool LotteryActive;
    public static bool LotteryRegister;
    public static List<string> LotteryPlayers = new();

    public static bool LuckyNumberActive;
    public static int LuckyNumberValue;
    public static string LuckyNumberWinner = "";

    public static bool UniqueHuntActive;
    public static string UniqueHuntWinner = "";

    public static bool HideSeekActive;
    public static int HideSeekRegion;
    public static string HideSeekHint = "";
    public static string HideSeekWinner = "";

    public static async void Initialize()
    {
        try
        {
            while (true)
            {
                try
                {
                    var cfg = Config.GetAutoEvent;
                    if (cfg is { Enable: true })
                    {
                        CleanupFiredKeys();

                        if (cfg.Trivia.Enable)
                            TryStartFromSchedule("trivia", cfg.Trivia.Schedules, StartTrivia);

                        if (cfg.Lottery.Enable)
                            TryStartFromSchedule("lottery", cfg.Lottery.Schedules, StartLottery);

                        if (cfg.LuckyNumber.Enable)
                            TryStartFromSchedule("luckynumber", cfg.LuckyNumber.Schedules, StartLuckyNumber);

                        if (cfg.UniqueHunt.Enable)
                            TryStartFromSchedule("uniquehunt", cfg.UniqueHunt.Schedules, StartUniqueHunt);

                        if (cfg.HideSeek.Enable)
                            TryStartFromSchedule("hideseek", cfg.HideSeek.Schedules, StartHideSeek);
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                }

                await Task.Delay(5000);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
    }

    public static bool TryManualStart(string eventName)
    {
        switch (eventName.ToLower())
        {
            case "trivia":
                StartTrivia();
                return true;
            case "lottery":
                StartLottery();
                return true;
            case "luckynumber":
            case "lucky":
                StartLuckyNumber();
                return true;
            case "unique":
            case "uniquehunt":
                StartUniqueHunt();
                return true;
            case "hideseek":
            case "hs":
                StartHideSeek();
                return true;
            case "stop":
                StopCurrent("stopped by GM");
                return true;
            default:
                return false;
        }
    }

    public static bool HandleChat(PlayerSession session, string message, byte chatType)
    {
        if (session?.State == null || string.IsNullOrEmpty(session.State.CharName))
            return false;

        if (Config.GetAutoEvent == null)
            return false;

        if (!Config.GetAutoEvent.Enable && chatType != 3)
            return false;

        var text = message.Trim();
        if (string.IsNullOrEmpty(text))
            return false;

        if (chatType == 3)
        {
            var parts = text.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            if (parts.Length >= 1 &&
                (parts[0].Equals("!autoevent", StringComparison.OrdinalIgnoreCase) ||
                 parts[0].Equals("autoevent", StringComparison.OrdinalIgnoreCase)))
            {
                if (parts.Length < 2)
                {
                    session.SendNotice("Usage: !autoevent trivia|lottery|luckynumber|unique|hideseek|stop");
                    return true;
                }

                if (!TryManualStart(parts[1]))
                    session.SendNotice("Unknown auto event. Use trivia, lottery, luckynumber, unique, hideseek, stop");
                else
                    session.SendGreenNotice($"[Auto Event] command accepted: {parts[1]}");

                return true;
            }
        }

        lock (LockObj)
        {
            if (TriviaActive)
            {
                if (string.Equals(text, TriviaAnswer, StringComparison.OrdinalIgnoreCase))
                {
                    TriviaWinner = session.State.CharName;
                    TriviaActive = false;
                    Reward(session, "Trivia");
                    SessionManager.SendNoticeToAll($"[Trivia Event] {session.State.CharName} answered correctly!", 0);
                    EndIfIdle();
                    return true;
                }
            }

            if (LotteryActive && LotteryRegister)
            {
                if (text.Equals("!join", StringComparison.OrdinalIgnoreCase) ||
                    text.Equals("!lottery", StringComparison.OrdinalIgnoreCase))
                {
                    if (LotteryPlayers.Contains(session.State.CharName))
                    {
                        session.SendBlueNotice("[Lottery Event] You already joined");
                        return true;
                    }

                    LotteryPlayers.Add(session.State.CharName);
                    session.SendGreenNotice("[Lottery Event] You joined the lottery");
                    return true;
                }
            }

            if (LuckyNumberActive)
            {
                if (int.TryParse(text, out var number) && number == LuckyNumberValue)
                {
                    LuckyNumberWinner = session.State.CharName;
                    LuckyNumberActive = false;
                    Reward(session, "Lucky Number");
                    SessionManager.SendNoticeToAll($"[Lucky Number] {session.State.CharName} found the number {LuckyNumberValue}!", 0);
                    EndIfIdle();
                    return true;
                }
            }

            if (HideSeekActive)
            {
                if (text.Equals("!found", StringComparison.OrdinalIgnoreCase) ||
                    text.Equals("!seek", StringComparison.OrdinalIgnoreCase))
                {
                    var region = session.State.TempPosition?.RegionID ?? session.State.Position?.RegionID ?? 0;
                    if (region != HideSeekRegion)
                    {
                        session.SendBlueNotice("[Hide & Seek] You are not in the correct area");
                        return true;
                    }

                    HideSeekWinner = session.State.CharName;
                    HideSeekActive = false;
                    Reward(session, "Hide & Seek");
                    SessionManager.SendNoticeToAll($"[Hide & Seek] {session.State.CharName} found the hiding spot!", 0);
                    EndIfIdle();
                    return true;
                }
            }
        }

        return false;
    }

    public static void OnUniqueKilled(string killerName)
    {
        if (string.IsNullOrEmpty(killerName))
            return;

        lock (LockObj)
        {
            if (!UniqueHuntActive)
                return;

            UniqueHuntActive = false;
            UniqueHuntWinner = killerName;
        }

        var session = SessionManager.GetSessionByCharName(killerName);
        if (session != null)
            Reward(session, "Unique Hunt");

        SessionManager.SendNoticeToAll($"[Unique Hunt] {killerName} killed the unique and won the event!", 0);
        EndIfIdle();
    }

    private static void TryStartFromSchedule(string eventName, List<StartTime> schedules, Action starter)
    {
        if (schedules == null || schedules.Count == 0)
            return;

        var currentDay = DateTime.Now.DayOfWeek.ToString();
        var currentTime = DateTime.Now.ToString("HH:mm");
        var key = $"{eventName}-{DateTime.Now:yyyyMMddHHmm}";

        foreach (var schedule in schedules)
        {
            var everyday = schedule.DayOfWeek == StartTime.Days.Everyday.ToString();
            var dayMatch = everyday || currentDay == schedule.DayOfWeek;
            if (!dayMatch || currentTime != schedule.Time)
                continue;

            lock (LockObj)
            {
                if (FiredKeys.Contains(key))
                    return;
                FiredKeys.Add(key);
            }

            starter();
            return;
        }
    }

    public static void StartTrivia()
    {
        if (!CanStart("Trivia"))
            return;

        var cfg = Config.GetAutoEvent.Trivia;
        if (cfg.Questions == null || cfg.Questions.Count == 0)
        {
            SessionManager.SendNoticeToAll("[Trivia Event] cancelled, no questions configured", 1);
            Release();
            return;
        }

        _ = RunTrivia(cfg);
    }

    public static void StartLottery()
    {
        if (!CanStart("Lottery"))
            return;

        _ = RunLottery(Config.GetAutoEvent.Lottery);
    }

    public static void StartLuckyNumber()
    {
        if (!CanStart("Lucky Number"))
            return;

        _ = RunLuckyNumber(Config.GetAutoEvent.LuckyNumber);
    }

    public static void StartUniqueHunt()
    {
        if (!CanStart("Unique Hunt"))
            return;

        _ = RunUniqueHunt(Config.GetAutoEvent.UniqueHunt);
    }

    public static void StartHideSeek()
    {
        if (!CanStart("Hide & Seek"))
            return;

        var cfg = Config.GetAutoEvent.HideSeek;
        var locations = cfg.Locations?.Where(p => p.RegionId != 0).ToList() ?? new List<HideSeekLocation>();
        if (locations.Count == 0)
        {
            SessionManager.SendNoticeToAll("[Hide & Seek] cancelled, no locations configured", 1);
            Release();
            return;
        }

        _ = RunHideSeek(cfg, locations);
    }

    private static async Task RunTrivia(TriviaSettings cfg)
    {
        try
        {
            var rounds = Math.Max(1, cfg.Rounds);
            SessionManager.SendNoticeToAll($"[Trivia Event] starting with {rounds} round(s). Answer in chat!", 1);

            for (var i = 0; i < rounds; i++)
            {
                TriviaQuestion question;
                lock (Rng)
                    question = cfg.Questions[Rng.Next(cfg.Questions.Count)];

                lock (LockObj)
                {
                    TriviaAnswer = question.Answer?.Trim() ?? "";
                    TriviaWinner = "";
                    TriviaActive = true;
                }

                SessionManager.SendNoticeToAll($"[Trivia Event] Round {i + 1}/{rounds}: {question.Question}", 0);

                var timeout = Config.GetAutoEvent.AnswerTimeoutMinutes * 60 * 1000;
                var waited = 0;
                while (waited < timeout)
                {
                    await Task.Delay(1000);
                    waited += 1000;
                    if (!TriviaActive)
                        break;
                }

                if (TriviaActive)
                {
                    TriviaActive = false;
                    SessionManager.SendNoticeToAll("[Trivia Event] Time is up, nobody answered correctly", 2);
                }
            }

            SessionManager.SendNoticeToAll("[Trivia Event] has ended", 1);
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
        finally
        {
            TriviaActive = false;
            Release();
        }
    }

    private static async Task RunLottery(LotterySettings cfg)
    {
        try
        {
            lock (LockObj)
            {
                LotteryPlayers = new List<string>();
                LotteryRegister = true;
                LotteryActive = true;
            }

            var minutes = Math.Max(1, cfg.RegisterDurationMinutes);
            SessionManager.SendNoticeToAll($"[Lottery Event] is open for {minutes} minute(s). Type !join to participate", 0);

            await Task.Delay((minutes - 1) * 60 * 1000);
            if (minutes > 1)
                SessionManager.SendNoticeToAll("[Lottery Event] registration closes in 1 minute", 2);

            await Task.Delay(60 * 1000);

            lock (LockObj)
                LotteryRegister = false;

            string winner = "";
            lock (LockObj)
            {
                if (LotteryPlayers.Count < Math.Max(1, cfg.MinPlayers))
                {
                    SessionManager.SendNoticeToAll("[Lottery Event] cancelled, not enough players", 1);
                }
                else
                {
                    winner = LotteryPlayers[Rng.Next(LotteryPlayers.Count)];
                }
            }

            if (!string.IsNullOrEmpty(winner))
            {
                var session = SessionManager.GetSessionByCharName(winner);
                if (session != null)
                    Reward(session, "Lottery");

                SessionManager.SendNoticeToAll($"[Lottery Event] winner is {winner}!", 0);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
        finally
        {
            LotteryActive = false;
            LotteryRegister = false;
            LotteryPlayers.Clear();
            Release();
        }
    }

    private static async Task RunLuckyNumber(LuckyNumberSettings cfg)
    {
        try
        {
            var min = Math.Min(cfg.MinNumber, cfg.MaxNumber);
            var max = Math.Max(cfg.MinNumber, cfg.MaxNumber);
            int number;
            lock (Rng)
                number = Rng.Next(min, max + 1);

            lock (LockObj)
            {
                LuckyNumberValue = number;
                LuckyNumberWinner = "";
                LuckyNumberActive = true;
            }

            SessionManager.SendNoticeToAll($"[Lucky Number] Type a number between {min} and {max} in chat to win!", 0);

            var timeout = Config.GetAutoEvent.AnswerTimeoutMinutes * 60 * 1000;
            var waited = 0;
            while (waited < timeout)
            {
                await Task.Delay(1000);
                waited += 1000;
                if (!LuckyNumberActive)
                    break;
            }

            if (LuckyNumberActive)
            {
                LuckyNumberActive = false;
                SessionManager.SendNoticeToAll($"[Lucky Number] Time is up. The number was {LuckyNumberValue}", 2);
            }
            else
            {
                SessionManager.SendNoticeToAll("[Lucky Number] has ended", 1);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
        finally
        {
            LuckyNumberActive = false;
            Release();
        }
    }

    private static async Task RunUniqueHunt(UniqueHuntSettings cfg)
    {
        try
        {
            lock (LockObj)
            {
                UniqueHuntWinner = "";
                UniqueHuntActive = true;
            }

            var minutes = Math.Max(1, cfg.DurationMinutes);
            SessionManager.SendNoticeToAll($"[Unique Hunt] started for {minutes} minute(s). First unique kill wins!", 0);

            await Task.Delay(minutes * 60 * 1000);

            if (UniqueHuntActive)
            {
                UniqueHuntActive = false;
                SessionManager.SendNoticeToAll("[Unique Hunt] ended with no unique kill", 2);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
        finally
        {
            UniqueHuntActive = false;
            Release();
        }
    }

    private static async Task RunHideSeek(HideSeekSettings cfg, List<HideSeekLocation> locations)
    {
        try
        {
            HideSeekLocation loc;
            lock (Rng)
                loc = locations[Rng.Next(locations.Count)];

            lock (LockObj)
            {
                HideSeekRegion = loc.RegionId;
                HideSeekHint = loc.Hint;
                HideSeekWinner = "";
                HideSeekActive = true;
            }

            var minutes = Math.Max(1, cfg.DurationMinutes);
            SessionManager.SendNoticeToAll($"[Hide & Seek] {loc.Hint}", 0);
            SessionManager.SendNoticeToAll($"[Hide & Seek] Type !found when you reach the location. You have {minutes} minute(s)", 1);

            await Task.Delay(minutes * 60 * 1000);

            if (HideSeekActive)
            {
                HideSeekActive = false;
                SessionManager.SendNoticeToAll("[Hide & Seek] Time is up, nobody found the hiding spot", 2);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
        finally
        {
            HideSeekActive = false;
            Release();
        }
    }

    private static void StopCurrent(string reason)
    {
        lock (LockObj)
        {
            TriviaActive = false;
            LotteryActive = false;
            LotteryRegister = false;
            LuckyNumberActive = false;
            UniqueHuntActive = false;
            HideSeekActive = false;
        }

        SessionManager.SendNoticeToAll($"[Auto Event] {CurrentEvent} {reason}", 2);
        Release();
    }

    private static bool CanStart(string name)
    {
        lock (LockObj)
        {
            if (Config.GetAutoEvent == null || !Config.GetAutoEvent.Enable)
            {
                SessionManager.SendNoticeToAll("[Auto Event] system is disabled", 2);
                return false;
            }

            if (Config.GetAutoEvent.RunOneEventAtATime && Busy)
            {
                SessionManager.SendNoticeToAll($"[Auto Event] {CurrentEvent} is already running", 2);
                return false;
            }

            Busy = true;
            CurrentEvent = name;
            return true;
        }
    }

    private static void Reward(PlayerSession session, string eventName)
    {
        var amount = Math.Max(1, Config.GetAutoEvent.RewardAmount);
        var type = string.IsNullOrEmpty(Config.GetAutoEvent.RewardSilkType)
            ? "Own"
            : Config.GetAutoEvent.RewardSilkType;

        session.SendSilk(amount, type);
        session.SendGreenNotice($"[Auto Event] You won {amount} silk from {eventName}!");
    }

    private static void EndIfIdle()
    {
        lock (LockObj)
        {
            if (TriviaActive || LotteryActive || LuckyNumberActive || UniqueHuntActive || HideSeekActive)
                return;
        }
    }

    private static void Release()
    {
        lock (LockObj)
        {
            Busy = false;
            CurrentEvent = "";
        }
    }

    private static void CleanupFiredKeys()
    {
        if (FiredKeys.Count < 200)
            return;

        lock (LockObj)
            FiredKeys.Clear();
    }
}
