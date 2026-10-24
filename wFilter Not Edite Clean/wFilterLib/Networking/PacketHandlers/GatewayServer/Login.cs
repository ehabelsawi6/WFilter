using System.Drawing;
using wFilterLib.Configs;
using wFilterLib.Helper;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;
using wFilterLib.Networking.PacketHandlers.GatewayServer.PacketStructure;

namespace wFilterLib.Networking.PacketHandlers.GatewayServer;

public class Login
{
    public static PacketResult HandleAck(Packet packet, PlayerSession session)
    {
        var loginResponse = new LoginResponse();
        loginResponse.ReadPacket(packet);

        if (loginResponse.Result != 0x01)
            return new PacketResult(loginResponse.WritePacket(), PacketResultType.Override);


        loginResponse.AgentServer.Ip = Config.GetModules.PublicIp;
        loginResponse.AgentServer.Port = Config.GetModules.AgentServer1.PublicPort;

        //todo mulit agent support
        //foreach (var agent in Globals.AgentServers)
        //{
        //    if (agent.ServerEp.Port == loginResponse.AgentServer.Port)
        //    {
        //        loginResponse.AgentServer.Ip = Config.GetModules.PublicIp;
        //        loginResponse.AgentServer.Port = (ushort)agent.Port;
        //        break;
        //    }
        //}

        //if (!Globals.PlayerStatus.ContainsKey(loginResponse.AgentServer.Token))
        //    Globals.PlayerStatus.TryAdd(loginResponse.AgentServer.Token, new PlayerStatus());


        //if (Configs.Config.GetLogin.AllowClientLess)
        //    Globals.PlayerStatus[loginResponse.AgentServer.Token].IsClientLess =
        //        session.IsClientLess;

        return new PacketResult(loginResponse.WritePacket(), PacketResultType.Override);
    }

    public static PacketResult HandleReq(Packet packet, PlayerSession session)
    {
        packet.ReadByte(); // content id
        var userName = packet.ReadAscii().ToLower();

        if (session.Ip == Config.GetModules.PublicIp || Config.GetLogin.ExcludedAccounts.Contains(userName))
        {
            return new PacketResult(PacketResultType.Nothing);
        }

        if (!session.PatchSent || !session.ServerListSent)
            return new PacketResult(PacketResultType.Disconnect, session.Ip + " trying to login without sending patch/server list packet");

       
        if (Globals.GMSecurityList.ContainsKey(userName))
            if (Globals.GMSecurityList[userName.ToLower()] != session.Ip)
                return new PacketResult(PacketResultType.Disconnect, $"{userName} [GM] trying to login from non allowed Ip [{session.Ip}]");


        if (Globals.BlockData.ContainsKey(session.Ip))
        {
            if (Globals.BlockData[session.Ip].EndDate > DateTime.Now)
            {
                session.SendLoginErrorMsg(
                   $"Your IP has been blocked till {Globals.BlockData[session.Ip].EndDate}",
                   Color.Yellow.ToHexUInt());
                return new PacketResult(PacketResultType.Block);
            }

            var result = session.GetSql.ExecuteNonQuery(
                    $"use wFilter delete from _Blocked where Id = {Globals.BlockData[session.Ip].Id}")
                ;
            // PrintToConsole.Notify($"IP: {Globals.BlockData[session.State.Ip]} has been unblocked !");
            Globals.BlockData.TryRemove(session.Ip, out _);

        }

        return new PacketResult(PacketResultType.Nothing);
    }
}
