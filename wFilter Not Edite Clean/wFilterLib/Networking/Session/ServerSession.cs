using System.Net;
using System.Net.Sockets;
using wFilterLib.Database.Models;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;
using TcpClient = wFilterLib.Networking.NetCoreServer.TcpClient;

namespace wFilterLib.Networking.Session;

public class ServerSession : TcpClient
{
	public PlayerSession? PlayerSession;

	public ServerSession(IPAddress address, int port) : base(address, port) { }

	public void Setup(PlayerSession? playerSession) { PlayerSession = playerSession; }

	protected override void OnConnected()
	{
		// Console.WriteLine($"TCP client connected a new session with Id {Id}");
	}

	protected override void OnReceived(byte[] buffer, long offset, long size)
	{
        //  Console.WriteLine($"{buffer.Length} | {(int)offset} | {(int)size}");

        if (IsSocketDisposed || !IsConnected || IsDisposed || size <= 0)
        {
            this.PlayerSession?.DisconnectAndStop();
            return;
        }

        try
		{
			PlayerSession?.ServerSecurity?.Recv(buffer, 0, (int)size);

			var packets = PlayerSession?.ServerSecurity?.TransferIncoming();

			if (packets != null)
			{
				foreach (var packet in packets)
				{
					if (packet.Opcode is 0x5000 or 0x9000)
					{
						TransferServer();
						continue;
					}

					if (packet.Opcode == 0x300A)
					{
						PlayerSession?.ClientSecurity?.Send(packet);
						PlayerSession?.TransferClient();
						PlayerSession?.DisconnectAndStop();
						continue;

					}

                    #region SERVER_AGENT_SILK_UPDATE

                    if (packet.Opcode == 0x3153)
                    {
                        if (packet.GetBytes().Length == 12)
                        {
                            var silkOwn = packet.ReadUInt32();//Fixing the silk package, will differ from different types of silk packs
                            var silkGift = packet.ReadUInt32();//aka RP
                            var silkPoint = packet.ReadUInt32();
                            if (PlayerSession?.State != null)
                            {
	                            var silk = PlayerSession?.GetSql.Get_CurSilkPack_By_JID(PlayerSession.State.UserJid);
	                            if (silk != null)
	                            {
		                            if (silk.Own != silkOwn || silk.Gift != silkGift || silk.Point != silkPoint)
		                            {
			                            var serverAgentSilkUpdate = new Packet(0x3153);
			                            serverAgentSilkUpdate.WriteUInt32(silk.Own);
			                            serverAgentSilkUpdate.WriteUInt32(silk.Gift);
			                            serverAgentSilkUpdate.WriteUInt32(silk.Point);
			                            PlayerSession?.ClientSecurity?.Send(serverAgentSilkUpdate);
			                            PlayerSession?.TransferClient();
			                            continue;
		                            }
	                            }
                            }
                        }
                    }

                    #endregion SERVER_AGENT_SILK_UPDATE

                    #region SERVER_SILK_UPDATE_NOTIFY
                    if (packet.Opcode == 0x3154)
                    {
                        //We are deleting the records on this table because it cuases the silk pack spam bug message
                        this.PlayerSession?.GetSql.ExecuteNonQuery($"TRUNCATE TABLE {Configs.Config.GetSql.AccountDatabase}.dbo.SK_SilkChange_BY_Web; ");
                        //0x100 = RP receieved from packet, correct 0x04 = RP, 0x00 is used for silk.
                        var silkType = packet.ReadUInt16();
                        var amount = packet.ReadUInt32();
                        //Overwriting the packet with the correct RP value
                        if (silkType == 0x100)
                        {
                            var serverSilkUpdateNotify = new Packet(0x3154);
                            serverSilkUpdateNotify.WriteUInt16(0x04);
                            serverSilkUpdateNotify.WriteInt32(amount);
                            PlayerSession?.ClientSecurity?.Send(serverSilkUpdateNotify);
                            PlayerSession?.TransferClient();
                            continue;
                        }
                    }

                    #endregion SERVER_SILK_UPDATE_NOTIFY

                    if (PlayerSession != null)
                    {
                        var packetResult = PlayerSession.SilkroadServer.PacketManager.HandlePacket(PacketMode.Server, packet, PlayerSession);

                        switch (packetResult.PacketResultType)
                        {
                            case PacketResultType.Disconnect:
                                PlayerSession?.DisconnectAndStop(packetResult.DisconnectReason);
                                return;
                            case PacketResultType.Override:
                                for (var index = 0; index < packetResult.PacketCount; index++)
                                    PlayerSession?.ClientSecurity?.Send((packetResult[index] )!);
                                continue;
                            case PacketResultType.Block:
                                continue;
                            case PacketResultType.Nothing:
                                PlayerSession?.ClientSecurity?.Send(packet);
                                continue;
                        }
                    }
                }
			}



			PlayerSession?.TransferClient();
		}
		catch (Exception e)
		{
			Globals.Logger.Debug(e);
			PlayerSession?.DisconnectAndStop();
		}

	}

	public void TransferServer()
	{
		try
		{
			var kvp = PlayerSession?.ServerSecurity?.TransferOutgoing();
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
			PlayerSession?.DisconnectAndStop();
		}
	}

	//public void DisconnectAndStop()
	//{
	//    Disconnect();
	//    PlayerSession.DisconnectAndStop();
	//    //while (IsConnected)
	//    //    Thread.Yield();
	//}

	protected override void OnDisconnected()
	{
		// Console.WriteLine($"TCP client disconnected a session with Id {Id}");
		if (PlayerSession is { IsConnected: true })
		{
			PlayerSession?.DisconnectAndStop();
		}
      
	}

	protected override void OnError(SocketError error)
	{
		//Globals.Logger.Debug($"ServerSession caught an error with code {error}");
	//	PlayerSession.DisconnectAndStop();
	}
}
