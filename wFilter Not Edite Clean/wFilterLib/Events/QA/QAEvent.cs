using wFilterLib.Networking.Session;

namespace wFilterLib.Events.QA;

public class QAEvent : IWEvent
{
    public string Name { get; set; }
    public bool Active { get; set; }
    public int Rounds { get; set; }
    public int CurrentRound { get; set; }
    
    public KeyValuePair<string, string> CurrentQuestion { get; private set; }
    
    public Task Setup(string name = "Question And Answer",int rounds = 1)
    {
        this.Name = name;
        this.Rounds = rounds;
        Active = false;
        CurrentRound = 0;
        
        return Task.CompletedTask;
    }

    public async Task Start()
    {
        while (EventManager.GetActiveEvents.Count > 0)
            await Task.Delay(60000);

        Active = true;
        
        SessionManager.SendNoticeToAll($"[{Name}] Event starting in 5 minute with [{Rounds}] round/s",1);
        await Task.Delay(5 * 60000);

        for (var i = 0; i < this.Rounds; i++)
        {     
            CurrentRound++;
            await Round();
        }

        await End();
    }

    public async Task Round()
    {
        SessionManager.SendNoticeToAll($"[{Name}] Event round {CurrentRound}", 1);
        
        var rand = new Random();
        CurrentQuestion = EventManager.Questions.ElementAt(rand.Next(0, EventManager.Questions.Count));
        await Task.Delay(1000);
        
        SessionManager.SendNoticeToAll($"[{Name}] Question: {CurrentQuestion.Key}", 1);


        await Reward();

    }

    public async Task End()
    {
        Active = false;
    }

    public async Task Reward()
    {
        throw new NotImplementedException();
    }
}