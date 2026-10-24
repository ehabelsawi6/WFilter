using System.Collections.Concurrent;

namespace wFilterLib.Events;

public static class EventManager
{
    public static List<IWEvent> Events = new();

    public static List<IWEvent> GetActiveEvents => Events.Where(p => p.Active).ToList();


    #region Events

    public static ConcurrentDictionary<string, string> Questions = new();

    #endregion
}