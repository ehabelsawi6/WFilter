using wFilterLib.Networking.NetCoreServer;
using System.Net;
using System.Net.Sockets;
using wFilterLib.Configs;
using wFilterLib.Database;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;
using wkFilter.NetworkStuff.PacketHandler.Agent;

namespace wFilterLib.Networking.Session;

public class PlayerSession : TcpSession
{
	public readonly NewSilkroadServer SilkroadServer;


	private ServerSession? _serverSession;
	private bool _serverConnected = false;

	public PlayerSession(TcpServer server) : base(server)
	{
		SilkroadServer = (NewSilkroadServer)server;
	}


	public Security? ServerSecurity = new();
	public Security? ClientSecurity = new();


	private bool _isStopped = false;

	private int _packetCount = 0;
	private bool _handshakeDone = false;
	private DateTime _lastPacketTime = DateTime.Now;


	public State? State;
	public ServerType ServerType => SilkroadServer.SrvType;
	public XSql GetSql => SilkroadServer.GetSql;

	public string TempHwid = "none";
	public bool PatchSent = false;
	public bool ServerListSent = false;
	public bool IsClientLess = false;
	public string? Ip = "";

	protected override void OnConnected()
	{
		//Console.WriteLine($"Chat TCP session with Id {Id} connected!");
		try
		{
			if (IsSocketDisposed || !IsConnected || IsDisposed)
			{
				DisconnectAndStop();
				return;
			}

			var tempIp = Socket.RemoteEndPoint as IPEndPoint;
			Ip = tempIp?.Address.ToString();

			if (!string.IsNullOrEmpty(Ip))
			{
				ClientSecurity?.GenerateSecurity(Configs.Config.GetModules.Blowfish, Configs.Config.GetModules.SecurityBytes, Configs.Config.GetModules.Handshake);
				TransferClient();
			}
			else
				DisconnectAndStop();

		}
		catch (Exception e)
		{
			Globals.Logger.Debug(e);
			DisconnectAndStop();
		}

	}

	protected override void OnDisconnected()
    {
        //Console.WriteLine($"Chat TCP session with Id {Id} disconnected!");

        if (_isStopped) return;
        SessionManager.OnDestroy(this);


        try
        {
            ClientSecurity = null;
            ServerSecurity = null;

            if (_serverSession is { IsConnected: true })
            {
	            _serverSession.Disconnect();
            }

            State?.Dispose();
            _serverSession?.Dispose();
        }

        catch
        {
            // ignored
        }
        finally
        {
            State = null;
        }



        _isStopped = true;
    }

	protected override void OnReceived(byte[] buffer, long offset, long size)
	{
		try
		{
			if (IsSocketDisposed || !IsConnected || IsDisposed || size <= 0)
			{
				DisconnectAndStop();
				return;
			}

			ClientSecurity?.Recv(buffer, 0, (int)size);

			var packets = ClientSecurity?.TransferIncoming();

			if (packets != null)
			{
				foreach (var packet in packets)
				{

					_packetCount++;

					if (!_handshakeDone)
					{
						if (packet.Opcode != 0x9000 && packet.Opcode != 0x5000 && packet.Opcode != 0x2001)
						{
							DisconnectAndStop(Ip + " sending packets before handshake done");
							return;
						}
					}

					if (packet.Opcode is 0x5000 or 0x9000)
					{
						if (!_handshakeDone)
							_handshakeDone = true;

						TransferClient();
						continue;
					}
					else if (packet.Opcode == 0x2001)
                    {
                        if (packet.GetBytes().Length == 12 && packet.ReadAscii() == "SR_Client")
                        {
                            if (ConnectToServer())
							{
								SessionManager.OnCreate(this);

								_serverConnected = true;

								if (ServerType == ServerType.Agent)
								{
									State = new();
									State.Ip = Ip;
								}


								continue;
							}

                            DisconnectAndStop();
                            Globals.Logger.Warn("Couldn't connect to the main server !");
                            return;
                        }

                        DisconnectAndStop("Seems the client sent a wrong size of 0x2001 packet !");
                        return;
                    }


					var currentTime = (DateTime.Now - _lastPacketTime).TotalSeconds;
					if (currentTime >= 1)
					{
						if (_packetCount > Configs.Config.GetProtection.PacketPerSec)
						{
							DisconnectAndStop($"Client({Ip}) was kicked for exceeding packet limit/second");
							return;
						}

						_packetCount = 0;
						_lastPacketTime = DateTime.Now;
					}


					if (ServerType == ServerType.Agent)
                    {

                        if (State != null && packet.Opcode == 0x7021 && State.SurvivalBlock)
                            continue;

						if (State != null && !Configs.Config.GetLogin.ExcludedAccounts.Contains(State.UserName))
						{
							//if (packet.Opcode == 0x750E && packet.Length > 0)
							//{
							//    DisconnectAndStop();
							//    return;
							//}


							#region CharScreen Exploit fix

							#region New shard exploit fix
							if (State.CharScreen)
							{
								if (_packetCount > 10)
								{
									DisconnectAndStop($"was kicked for sending to many packets in char screen!");
									return;
								}
							}
							#endregion

							if (State.CharScreen && packet.Opcode != 0x2002 && packet.Opcode != 0x7001 && packet.Opcode != 0x7007 && packet.Opcode != 0x7450)
							{
								DisconnectAndStop();
								return;
							}

							if (!State.CharScreen && (packet.Opcode == 0x7001 || packet.Opcode == 0x7007 || packet.Opcode == 0x7450))
							{
								DisconnectAndStop();
								return;
							}

							if (State.CharScreen && packet.Opcode == 0x7158)
							{
								try
								{
									switch (packet.ReadUInt8())
									{
										case 0:
											{
												if (packet.GetBytes().Length != 2)
												{
													if (Configs.Config.GetProtection.FirewallBan)
														Helper.Utility.BlockIp(Ip, "attempted to use a Shard exploit #7");

													DisconnectAndStop("attempted to use a Shard exploit #7");
													return;
												}

												if (packet.ReadUInt8() != 7)
												{
													if (Configs.Config.GetProtection.FirewallBan)
														Helper.Utility.BlockIp(Ip, "attempted to use a Shard exploit #13");

													DisconnectAndStop("attempted to use a Shard exploit #13");
													return;
												}
											}
											break;

										case 1:
											{

												if (packet.GetBytes().Length != 7)
												{
													if (Configs.Config.GetProtection.FirewallBan)
														Helper.Utility.BlockIp(Ip, "attempted to use a Shard exploit #8");

													DisconnectAndStop("attempted to use a Shard exploit #8");
													return;
												}

												packet.ReadUInt8(); // FromSlot
												packet.ReadUInt8(); // ToSlot
												packet.ReadUInt32(); // Item ID

												break;
											}
										default:
											{
												if (Configs.Config.GetProtection.FirewallBan)
													Helper.Utility.BlockIp(Ip, "attempted to use a Shard exploit #9");


												DisconnectAndStop("attempted to use a Shard exploit #9");
												return;

												// break;
											}
									}
								}

								catch
								{
									if (Configs.Config.GetProtection.FirewallBan)
										Helper.Utility.BlockIp(Ip, "attempted to use a Shard exploit #9");

									DisconnectAndStop("attempted to use a Shard exploit #9");
									return;
								}
							}

							#endregion
						}

					}

		


					if (ServerType == ServerType.Agent)
					{
						if (packet.Opcode != 0x1337 && packet.Opcode != 0x2113 && packet.Opcode != 0x2002 &&
					 State?.PingCounter != 0 && State.IsAfk)
						{
							SetAfkStatus(false);
							State.PingCounter = 0;
						}

						if (Configs.Config.GetExtra.BlockPHBot)
						{
							if (packet.Opcode == State?.phbotOpcode)
                            {
								var invRet = AgentHandler.InventoryOperationRequest(packet, this);
								if (invRet.PacketResultType == PacketResultType.Nothing)
								{
									var tradePacket = new Packet((ushort)Opcodes.Agent.Request.INVENTORY_OPERATION);
									tradePacket.WriteByteArray(packet.GetBytes());
									SendPacketToServer(tradePacket);
								}
								//ServerSecurity?.Send(packet);
                                continue;
							}

                            //if (packet.Opcode == (ushort)Opcodes.Agent.Request.INVENTORY_OPERATION)
                            //{
                            //    byte OperationType = packet.ReadUInt8();
                            //    if (OperationType != 0x18)
                            //        continue;
                            //}
						}
					}




					var packetResult = SilkroadServer.PacketManager.HandlePacket(PacketMode.Client, packet, this);

					switch (packetResult.PacketResultType)
					{
						case PacketResultType.Disconnect:
							DisconnectAndStop(packetResult.DisconnectReason);
							return;
						case PacketResultType.Override:
							for (var index = 0; index < packetResult.PacketCount; index++)
								ServerSecurity?.Send(packetResult[index]);
							continue;
						case PacketResultType.Block:
							continue;
						case PacketResultType.Nothing:
							ServerSecurity?.Send(packet);
							continue;
						default:
							break;
					}
				}
			}

			if (_serverConnected)
				_serverSession?.TransferServer();
		}
		catch (Exception e)
		{
			Globals.Logger.Debug(e);
			DisconnectAndStop();
		}

	}

	protected override void OnError(SocketError error)
	{
		//Globals.Logger.Debug($"{Ip} PlayerSession caught an error with code {error}");
	//	DisconnectAndStop();
	}

    private bool ConnectToServer()
	{
		try
		{
			_serverSession = new(SilkroadServer.ServerEp.Address, SilkroadServer.ServerEp.Port);
			_serverSession.PlayerSession = this;
			_serverSession.ConnectAsync();

			return true;
		}
		catch (Exception e)
		{
			Globals.Logger.Debug(e);
			DisconnectAndStop();
		}
		return false;
	}

	public void TransferClient()
	{
		if (ClientSecurity == null)
			return;
		try
		{
			var kvp = ClientSecurity?.TransferOutgoing();
            if (kvp == null) return;
            foreach (var item in kvp)
            {
                SendAsync(item.Key.Buffer, 0, item.Key.Buffer.Length);

                while (BytesPending + BytesSending > 10485760)
                    Thread.Yield();
            }
        }
		catch (Exception e)
		{
			Globals.Logger.Debug(e);
			DisconnectAndStop();
		}
	}

	public void DisconnectAndStop(string reason = "")
	{
		try
		{
            if (reason.Length > 0)
            {
                Globals.Logger.Warn(reason);
                if (Configs.Config.GetProtection.FirewallBan)
                    Helper.Utility.BlockIp(Ip, reason);
            }


            //...

            Disconnect();

            _serverSession?.Disconnect();

            while (IsConnected)
                Thread.Yield();
        }
        catch (Exception e)
        {
            Globals.Logger.Debug(e);
           // DisconnectAndStop();
        }

    }


    #region Session Helper

    public void TeleportToPos(int regionId ,int posX,int posY , int posZ)
    {
        GetSql.ExecuteNonQuery(
            $"use wFilter Insert _InstantTeleportDelivery (CharID,WorldID,WorldLayerID,RegionID,PosX,PosY,PosZ) values ({State.CharId},1,1,{regionId},{posX},{posY},{posZ})");

    }

    public void TeleportToDonwhang()
	{
		/*var pTeleportTo = new Packet((ushort) CustomOpcodes.FILTER_GS_GUI_MAIN);
        pTeleportTo.WriteUInt(State.UniqueId); // unique id
        pTeleportTo.WriteByte(8); // type
        pTeleportTo.WriteUInt(0x1); // worldlayer id ?
        pTeleportTo.WriteUInt(0x1); // world id
        pTeleportTo.WriteShort(26265); //region id
        pTeleportTo.WriteSingle(859); // x
        pTeleportTo.WriteSingle(106); // y
        pTeleportTo.WriteSingle(1640); // z
        SendPacketToServer(pTeleportTo);*/
		GetSql.ExecuteNonQuery(
			$"use wFilter Insert _InstantTeleportDelivery (CharID,WorldID,WorldLayerID,RegionID,PosX,PosY,PosZ) values ({State.CharId},1,1,26265,859,106,1640)");

	}

	public void LiveTitleUpdate(byte id)
	{
		var liveTitle = new Packet((ushort)Opcodes.Custom.Framework.MAIN);
		liveTitle.WriteUInt(State.UniqueId);
		liveTitle.WriteByte(2);
		liveTitle.WriteByte(id);
		SendPacketToServer(liveTitle);

	}

	public void SendPacketToClient(Packet pck)
	{
		ClientSecurity?.Send(pck);
		TransferClient();
	}

	public void SendPacketToServer(Packet pck)
	{
		ServerSecurity?.Send(pck);
		_serverSession?.TransferServer();
	}

	public void SendNotice(string text)
	{
		var send = new Packet(0x3026);
		send.WriteByte(7);
		send.WriteAscii(text);
		SendPacketToClient(send);
	}

	public void SendPinkNotice(string text)
	{
		var pBuffer = new Packet((ushort)Opcodes.Custom.Response.Customs);
		pBuffer.WriteByte(0x0F);
		pBuffer.WriteByte(0x02);
		pBuffer.WriteByte(0);
		pBuffer.WriteUnicode(text);
		SendPacketToClient(pBuffer);
	}

	public void SendGreenNotice(string text)
	{
		var pBuffer = new Packet((ushort)Opcodes.Custom.Response.Customs);
		pBuffer.WriteByte(0x0F);
		pBuffer.WriteByte(0x03);
		pBuffer.WriteByte(0);
		pBuffer.WriteUnicode(text);
		SendPacketToClient(pBuffer);
	}

	public void SendBlueNotice(string text)
	{
		var pBuffer = new Packet((ushort)Opcodes.Custom.Response.Customs);
		pBuffer.WriteByte(0x0F);
		pBuffer.WriteByte(0x04);
		pBuffer.WriteByte(0);
		pBuffer.WriteUnicode(text);
		SendPacketToClient(pBuffer);
	}

	public void SendLoginErrorMsg(string msg, uint color)
	{
		var errorMsg = new Packet(0xB003);
		errorMsg.WriteAscii(msg);
		errorMsg.WriteUInt(color);
		SendPacketToClient(errorMsg);
	}

	public void SetAfkStatus(bool isAfk)
    {
        if (Config.GetModules.PublicIp == "65.108.27.225")
            return;

		var pAfk = new Packet(0x3131);
		pAfk.WriteByte(0);
		pAfk.WriteBool(isAfk);
		pAfk.WriteUInt(State.UniqueId);
		SessionManager.SendPacketToNearestPlayers(pAfk, State.Position.RegionID);

		State.IsAfk = isAfk;
	}
	public void AfkStatus(PlayerSession target)
	{
        if (Config.GetModules.PublicIp == "65.108.27.225")
            return;

        if (!target.State.IsAfk)
			return;

		var pAfk = new Packet(0x3131);
		pAfk.WriteByte(0);
		pAfk.WriteByte(1);
		pAfk.WriteUInt(target.State.UniqueId);
        SendPacketToClient(pAfk);
	}



	#region SilkPetHourSystem

	public void InitializeSilkTimerObject(double tickingInterval)
	{
		if (State == null) return;
		State.SilkTimer = new System.Timers.Timer(tickingInterval);
		State.SilkTimer.Elapsed += (sender, args) => RewardSilk();
		State.SilkTimer.AutoReset = true;
		State.SilkTimer.Enabled = true;
	}

	public void RewardSilk()
	{
		try
		{
			if (Configs.Config.GetSilkPerHour.Enable && Configs.Config.GetSilkPerHour.RewardEvery > 0)
			{
				if (!Configs.Config.GetSilkPerHour.RewardAfk && State.IsAfk)
				{
					SendNotice(
						$"You did not get silks from silk per hour because you were afk !");
					return;
				}

				if (string.IsNullOrEmpty(State?.CharName)) return;
				if (State.CurLevel < Configs.Config.GetSilkPerHour.MinLevel) return;
				SendSilk(Configs.Config.GetSilkPerHour.RewardAmount, Configs.Config.GetSilkPerHour.SilkType);
			}
			else State.SilkTimer.Enabled = false;
		}
		catch
		{
			if (State != null) State.SilkTimer.Enabled = false;
		}
	}


	#endregion
	public void SendSilk(int amount, string type)
	{
		GetSql.ExecuteNonQuery($"use wFilter exec _SilkSystem '{State.UserName}','{type}',{amount}");
	}

	#endregion
}
