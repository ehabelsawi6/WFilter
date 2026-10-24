using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;
using wFilterLib.Opcodes;

namespace wFilterLib.Networking.Session;

public static class SessionManager
{
	//public delegate void SessionEventHandler(PlayerSession session);

	private static readonly object _lock = new();

	private static List<PlayerSession?> gatewaySessions = new();
	private static List<PlayerSession?> downloadSessions = new();
	private static List<PlayerSession?> agentSessions = new();

	public static List<PlayerSession?> playerSessions => agentSessions;

	public static int GatewaySessionCount => gatewaySessions.Count;
	public static int DownloadSessionCount => downloadSessions.Count;

	public static int AgentSessionCount { get
	{
		lock (_lock)
		{
			return agentSessions.Count;
		}
	} }


	public static void SendPacketToNearestPlayers(Packet packet, int regionId)
	{
		try
		{
			lock (_lock)
			{
				if (AgentSessionCount < 1) return;

				foreach (var session in agentSessions)
				{
					if (session?.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

					if (session.State.Position.RegionID == regionId)
						session.SendPacketToClient(packet);
				}

			}
		}
		catch (Exception e)
		{
			Console.WriteLine(e);
			// ignored
		}
	}

    public static PlayerSession? GetSessionByCharName(string charName)
    {
        try
        {
            lock (_lock)
            {
                if (AgentSessionCount < 1) return null;

                foreach (var session in agentSessions)
                {
                    if (session?.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

                    if (session.State.CharName == charName)
                        return session;
                }
                return null;
            }
        }
        catch (Exception e)
        {
          //  Console.WriteLine(e);
            return null;
        }
    }

    public static void SendNoticeToNearestPlayers(string message, byte Color, int regionId)
    {
        try
        {
            lock (_lock)
            {
                if (AgentSessionCount < 1) return;

                foreach (var session in agentSessions)
                {
                    if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

                    if (session.State.Position.RegionID == regionId || session.State.TempPosition.RegionID == regionId)
                    {
                        switch (Color)
                        {
                            case 0:
                                session.SendPinkNotice(message);
                                break;
                            case 1:
                                session.SendGreenNotice(message);
                                break;
                            case 2:
                                session.SendBlueNotice(message);
                                break;
                            case 4:
                                session.SendNotice(message);
                                break;
                            default:
                                break;
                        }
                    }
                }

            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            // ignored
        }
    }

    public static void SendPacketToAll(Packet packet)
	{
		try
		{
			lock (_lock)
			{
				if (AgentSessionCount < 1) return;

				foreach (var session in agentSessions)
				{
					if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

					session.SendPacketToClient(packet);

				}

			}

		}
		catch (Exception e)
		{
			Console.WriteLine(e);
			// ignored
		}
	}

	public static void SendNoticeToAll(string message, byte Color)
	{
		try
		{
			lock (_lock)
			{
				if (AgentSessionCount < 1) return;

				foreach (var session in agentSessions)
				{
					if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

					switch (Color)
					{
						case 0:
							session.SendPinkNotice(message);
							break;
						case 1:
							session.SendGreenNotice(message);
							break;
						case 2:
							session.SendBlueNotice(message);
							break;
						case 4:
							session.SendNotice(message);
							break;
						default:
							break;
					}

				}

			}

		}
		catch (Exception e)
		{
			Console.WriteLine(e);
			// ignored
		}
	}

	public static int GetSessionCountForIp(string? ip)
	{
		var n = 0;

		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Ip == ip)
					n++;
			}
		}
		//  n += agentSessions.Count(session => session.State.Ip == ip);

		return n;
	}

	public static int GetSessionCountForHwid(string hwid)
	{
		var n = 0;

		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid)
					n++;
			}
		}
		//n += agentSessions.Count(session => session.State.Hwid == hwid);

		return n;
	}

	public static int GetJobSessionCountForHwid(string hwid)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid && session.State.IsJob)
					n++;
			}
		}
		//n += agentSessions.Count(session => session.State.Hwid == hwid && session.State.IsJob);

		return n;
	}

	public static int GetFwSessionCountForHwid(string hwid)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid && session.State.Location == PlayerLocation.Fortress)
					n++;
			}
		}
		// n += agentSessions.Count(session =>
		// session.State.Hwid == hwid && session.State.Location == PlayerLocation.Fortress);

		return n;
	}

	public static int GetCtfRegionSessionCountForHwid(string hwid)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid && session.State.Location == PlayerLocation.Ctf)
					n++;
			}
		}
		//   n += agentSessions.Count(session =>
		// session.State.Hwid == hwid && session.State.Location == PlayerLocation.Ctf);

		return n;
	}

	public static int GetCtfSessionCountForHwid(string hwid)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid && session.State.CtfRegistered)
					n++;
			}
		}
		//  n += agentSessions.Count(session =>
		//               session.State.Hwid == hwid && session.State.CtfRegistered);

		return n;
	}

	public static int GetArenaSessionCountForHwid(string hwid)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid && session.State.ArenaRegistered)
					n++;
			}
		}
		//   n += agentSessions.Count(session =>
		//  session.State.Hwid == hwid && session.State.ArenaRegistered);

		return n;
	}

	public static int GetArenaRegionSessionCountForHwid(string hwid)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid && session.State.Location == PlayerLocation.Arena)
					n++;
			}
		}
		// n += agentSessions.Count(session =>
		// session.State.Hwid == hwid && session.State.Location == PlayerLocation.Arena);

		return n;
	}

	public static int GetCustomRegionSessionCountForHwid(string hwid, int regionId)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid && session.State.TempPosition.RegionID == regionId)
					n++;
			}
		}
		// n += agentSessions.Count(session =>
		// session.State.Hwid == hwid && session.State.TempPosition.RegionID == regionId);

		return n;
	}
	public static int GetSilkPerHourCountForHwid(string hwid)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session?.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;
				if(session?.State?.SilkTimer == null) continue;

				if (session.State.Hwid == hwid && session.State.SilkTimer.Enabled)
					n++;
			}
		}
		// n += agentSessions.Count(session =>
		// session.State.Hwid == hwid && session.State.Location == PlayerLocation.Fortress);

		return n;
	}
	
	public static int GetSurvivalCountForHwid(string hwid)
	{
		var n = 0;
		lock (_lock)
		{
			if (AgentSessionCount < 1) return 0;

			foreach (var session in agentSessions)
			{
				if (session?.State == null || string.IsNullOrEmpty(session.State.CharName)) continue;

				if (session.State.Hwid == hwid && Globals.SurvivalEventRegisteredCharacters.Contains(session.State.CharName))
					n++;
			}
		}
		// n += agentSessions.Count(session =>
		// session.State.Hwid == hwid && session.State.Location == PlayerLocation.Fortress);

		return n;
	}
	public static PlayerSession GetStateByUniqueID(uint targetUniqueId)
	{
		lock (_lock)
		{
			return agentSessions.FirstOrDefault(session => session.State.UniqueId == targetUniqueId);
		}
	}

    public static void SendCharacterInfo(PlayerSession session)
    {
        lock (_lock)
        {
			foreach (var s in agentSessions)
			{
				if (s.State.TempPosition.RegionID != session.State.TempPosition.RegionID)
					continue;


                var customPacket = new Packet((ushort)Custom.Response.Customs);
                customPacket.WriteByte(0x41);

                customPacket.WriteUInt(s.State.UniqueId);
                customPacket.WriteInt32(s.State.NameColor);
                customPacket.WriteInt32(s.State.TitleColor);


                customPacket.WriteBool(!string.IsNullOrEmpty(s.State.CustomTitleName));
                if (!string.IsNullOrEmpty(s.State.CustomTitleName))
                    customPacket.WriteAscii(s.State.CustomTitleName);

                customPacket.WriteInt32(s.State.CustomIconId);
              //  customPacket.WriteByte(s.State.CustomTitleCredits);
                //customPacket.WriteBool(session.State.IsLocked);
                customPacket.WriteInt32(s.State.DSPoints);

                session.SendPacketToClient(customPacket);

                session.AfkStatus(s);
            }
        }
    }

    public static void OnCreate(PlayerSession session)
	{
		lock (_lock)
		{
			switch (session.ServerType)
			{
				case ServerType.Download:
					downloadSessions.Add(session);
					break;
				case ServerType.Gateway:
					gatewaySessions.Add(session);
					break;
				case ServerType.Agent:
					agentSessions.Add(session);
					break;
				default:
					break;
			}

			Globals.UpdateStatus(session.ServerType);
		}
	}

	public static void OnDestroy(PlayerSession session)
	{
		var st = session.ServerType;
		lock (_lock)
		{
			switch (session.ServerType)
			{
				case ServerType.Download:
					downloadSessions.Remove(session);
					break;
				case ServerType.Gateway:
					gatewaySessions.Remove(session);
					break;
				case ServerType.Agent:
                    if (session.State != null && Globals.SurvivalEventRegisteredCharacters.Contains(session.State.CharName))
                        Globals.SurvivalEventRegisteredCharacters.Remove(session.State.CharName);
                    agentSessions.Remove(session);
                    break;
				default:
					break;
			}

			Globals.UpdateStatus(st);
		}
	}
}
