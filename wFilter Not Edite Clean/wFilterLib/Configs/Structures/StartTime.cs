namespace wFilterLib.Configs.Structures;

public class StartTime
{
    public string DayOfWeek { get; set; } = Days.Everyday.ToString();
    public string Time { get; set; } = DateTime.Now.ToString("hh:mm");

    public enum Days
    {
        Everyday = -1,
        Sunday = 0,
        Monday = 1,
        Tuesday = 2,
        Wednesday = 3,
        Thursday = 4,
        Friday = 5,
        Saturday = 6,
        
    }
}
