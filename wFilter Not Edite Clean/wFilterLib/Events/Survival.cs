using wFilterLib.Configs;
using wFilterLib.Configs.Structures;
using wFilterLib.Database;
using wFilterLib.Database.Models;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.Session.Classes;
using wFilterLib.SSA;

namespace wFilterLib.Events;

public class Survival
{
    public static async void Initialize()
    {
        try
        {
            while (true)
            {
                if (SqlTables.Connect() && Config.GetSurvivalEvent.Enable && !Globals.SurvivalEvent)
                {
                    if (Config.GetGUISettings.KillCounters.All(p => p.RegionID != Config.GetSurvivalEvent.RegionId))
                    {
                        Top5KillCounterData counterData = new()
                        {
                            RegionID = Config.GetSurvivalEvent.RegionId,
                            TableName = "_SurvivalEventRecords"
                        };

                        Config.GetGUISettings.KillCounters.Add(counterData);
                    }

                    if (!Config.GetExtra.AutoCapeRegions.Contains(Config.GetSurvivalEvent.RegionId))
                        Config.GetExtra.AutoCapeRegions.Add(Config.GetSurvivalEvent.RegionId);
                
                    if(!Config.GetBlockByRegion.PartyRegions.Contains(Config.GetSurvivalEvent.RegionId))
                        Config.GetBlockByRegion.PartyRegions.Add(Config.GetSurvivalEvent.RegionId);
                
                    if(!Config.GetBlockByRegion.ReverseRegions.Contains(Config.GetSurvivalEvent.RegionId))
                        Config.GetBlockByRegion.ReverseRegions.Add(Config.GetSurvivalEvent.RegionId);
                
                    foreach (var schedule in Config.GetSurvivalEvent.Schedules)
                    {
                        var currentDay = DateTime.Now.DayOfWeek.ToString();
                        var currentTime = DateTime.Now.ToString("HH:mm");

                        if (schedule.DayOfWeek == StartTime.Days.Everyday.ToString() && currentTime == schedule.Time)
                        {
                            Globals.SurvivalEvent = true;

                            RegisterStart();

                            break;
                        } 
                        if (currentDay == schedule.DayOfWeek && currentTime == schedule.Time)
                        {
                            Globals.SurvivalEvent = true;

                            RegisterStart();

                            break;
                        }

                    }
                }


                await Task.Delay(5000);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
           // throw;
        }
    }


    
    public static async void RegisterStart()
    {
        try
        {
            Globals.SurvivalEventRegister = true;

            var regDur = Config.GetSurvivalEvent.RegisterDuration;
            SessionManager.SendNoticeToAll($"[Survival Event] Registration is now open for {regDur} minutes",2);
            SessionManager.SendNoticeToAll($"[Survival Event] Type !register to register | !cancel to unregister",1);

            regDur--;
            await Task.Delay(regDur * 60000);

            RegisterMinute();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            //throw;
        }

    }

    public static async void RegisterMinute()
    {
        try
        {
            SessionManager.SendNoticeToAll($"[Survival Event] Registration will close after 1 minute", 2);
            await Task.Delay(60000);
            Globals.SurvivalEventRegister = false;
            //   SessionManager.SendNoticeToAll($"[Survival Event] Registration has closed", 2);

            if (Globals.SurvivalEventRegisteredCharacters.Count < Config.GetSurvivalEvent.MinPlayers)
            {
                SessionManager.SendNoticeToAll($"[Survival Event] has been cancelled due to insufficient number of participants", 1);
                Globals.SurvivalEvent = false;

                Globals.SurvivalEventRegisteredCharacters.Clear();

                return;
            }

            Start();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
          //  throw;
        }

    }

    public static async void Start()
    {
        try
        {
            var config = Config.GetSurvivalEvent;
        
        
            var positions = new Queue<GamePosition>();
        
            positions.Enqueue(new GamePosition(config.RegionId,1230,1,650));
            positions.Enqueue(new GamePosition(config.RegionId,1130,1,650));
            positions.Enqueue(new GamePosition(config.RegionId,1030,1,650));
            positions.Enqueue(new GamePosition(config.RegionId,930,1,650));
            positions.Enqueue(new GamePosition(config.RegionId,830,1,650));
            positions.Enqueue(new GamePosition(config.RegionId,730,1,650));
            positions.Enqueue(new GamePosition(config.RegionId,685,1,650));
        
            positions.Enqueue(new GamePosition(config.RegionId,1230,1,1285));
            positions.Enqueue(new GamePosition(config.RegionId,1130,1,1285));
            positions.Enqueue(new GamePosition(config.RegionId,1030,1,1285));
            positions.Enqueue(new GamePosition(config.RegionId,930,1,1285));
            positions.Enqueue(new GamePosition(config.RegionId,830,1,1285));
            positions.Enqueue(new GamePosition(config.RegionId,730,1,1285));
            positions.Enqueue(new GamePosition(config.RegionId,685,1,1285));
        
            positions.Enqueue(new GamePosition(config.RegionId,650,1,1230));
            positions.Enqueue(new GamePosition(config.RegionId,650,1,1130));
            positions.Enqueue(new GamePosition(config.RegionId,650,1,1030));
            positions.Enqueue(new GamePosition(config.RegionId,650,1,930));
            positions.Enqueue(new GamePosition(config.RegionId,650,1,830));
            positions.Enqueue(new GamePosition(config.RegionId,650,1,730));
            positions.Enqueue(new GamePosition(config.RegionId,650,1,685));
        
            positions.Enqueue(new GamePosition(config.RegionId,1285,1,1230));
            positions.Enqueue(new GamePosition(config.RegionId,1285,1,1130));
            positions.Enqueue(new GamePosition(config.RegionId,1285,1,1030));
            positions.Enqueue(new GamePosition(config.RegionId,1285,1,930));
            positions.Enqueue(new GamePosition(config.RegionId,1285,1,830));
            positions.Enqueue(new GamePosition(config.RegionId,1285,1,730));
            positions.Enqueue(new GamePosition(config.RegionId,1285,1,685));
        
            SessionManager.SendNoticeToAll($"[Survival Event] has just started !", 0);

            var posX = config.PosX;
            var poxY = config.PosY;

            foreach (var session in Globals.SurvivalEventRegisteredCharacters.Select(SessionManager.GetSessionByCharName))
            {
                // session!.State!.InSurvival = true;

                if (session.State.IsJob)
                {
                    session.SendBlueNotice(
                        "[Survival Event] You have failed to join Survival Event because you are under job mode");
                    continue;
                }

                if (session.State.CurLevel < config.RequireLevel)
                {
                    session.SendBlueNotice(
                        "[Survival Event] You have failed to join Survival Event because your level is too low");
                    continue;
                }

                session!.State!.SurvivalBlock = true;
                var pos = positions.Dequeue();
                session?.TeleportToPos(config.RegionId, (int)pos.X, (int)pos.Y, (int)pos.Z);

                posX++;
                poxY++;
            }

            await Task.Delay(5000);

            var holdTimer = new Packet(0x34B1);
            holdTimer.WriteByte(255);
            holdTimer.WriteByte(14);
            holdTimer.WriteInt32(20 * 60 * 1000 - 60000);

            var rndX = new Random();
            var rndZ = new Random();
        
        

        
            foreach (var session in Globals.SurvivalEventRegisteredCharacters.Select(SessionManager.GetSessionByCharName))
            {
                session?.SendBlueNotice($"[Survival Event] Please hold on a minute !");
                session?.SendPacketToClient(holdTimer);

                /*var pos = positions.Dequeue();
            
            var pMovement = new Packet(0x7021);
            pMovement.WriteByte(1);
            pMovement.WriteInt16(pos.RegionID);
            pMovement.WriteInt32(pos.X);
            pMovement.WriteInt32(pos.Y);
            pMovement.WriteInt32(pos.Z);
            session?.SendPacketToServer(pMovement);*/
            }

            await Task.Delay(60000);
            Globals.SurvivalStartTime = DateTime.Now;
            foreach (var session in Globals.SurvivalEventRegisteredCharacters.Select(SessionManager.GetSessionByCharName))
            {
                session!.State!.SurvivalBlock = false;
                var playingTimer = new Packet(0x34B1);
                playingTimer.WriteByte(255);
                playingTimer.WriteByte(14);
                playingTimer.WriteInt32((20 * 60 * 1000) - (config.PlayingDuration * 60 * 1000));
                session?.SendPacketToClient(playingTimer);
                session?.SendBlueNotice($"[Survival Event] You free to go now , survive to win !");
            }

            await Task.Delay(config.PlayingDuration * 60 * 1000);
            Globals.SurvivalEvent = false;

            SessionManager.SendNoticeToAll($"[Survival Event] has just ended !", 0);


            var winners = Globals.AgentServers[0].GetSql.Read<SurvivalWinners>("exec wFilter.._SurvivalEvent");

            await Task.Delay(5000);

            if (!string.IsNullOrEmpty(winners.Top1))
                SessionManager.SendNoticeToAll($"[Survival Event] Top1 winner is {winners.Top1} !", 0);
            if (!string.IsNullOrEmpty(winners.Top2))
                SessionManager.SendNoticeToAll($"[Survival Event] Top2 winner is {winners.Top2} !", 2);
            if (!string.IsNullOrEmpty(winners.Top3))
                SessionManager.SendNoticeToAll($"[Survival Event] Top2 winner is {winners.Top3} !", 1);



            var pGetUp = new Packet(0x3053);
            pGetUp.WriteByte(2);
            foreach (var session in Globals.SurvivalEventRegisteredCharacters.Select(SessionManager.GetSessionByCharName))
            {
                session!.State!.SurvivalBlock = true;
                session?.SendPacketToServer(pGetUp);
                await Task.Delay(2000);
                session?.TeleportToDonwhang();
            }


            if (Config.GetExtra.AutoCapeRegions.Contains(Config.GetSurvivalEvent.RegionId))
                Config.GetExtra.AutoCapeRegions.Remove(Config.GetSurvivalEvent.RegionId);

            if (Config.GetBlockByRegion.PartyRegions.Contains(Config.GetSurvivalEvent.RegionId))
                Config.GetBlockByRegion.PartyRegions.Remove(Config.GetSurvivalEvent.RegionId);

            if (Config.GetBlockByRegion.ReverseRegions.Contains(Config.GetSurvivalEvent.RegionId))
                Config.GetBlockByRegion.ReverseRegions.Remove(Config.GetSurvivalEvent.RegionId);

            Globals.SurvivalEventRegisteredCharacters.Clear();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            //;
        }
    }

    public class SurvivalWinners
    {
        public string Top1 { get; set; }
        public string Top2 { get; set; }
        public string Top3 { get; set; }
    }
}

