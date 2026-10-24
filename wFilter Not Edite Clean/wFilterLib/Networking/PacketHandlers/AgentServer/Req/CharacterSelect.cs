using wFilterLib;
using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Opcodes;
using wFilterLib.SSA;
using wFilterLib.Networking.Session.Classes;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{

    public static PacketResult CharacterSelectRequest(Packet packet, PlayerSession session)
    {
        if (session.State.CharName.Length > 0)
            return new PacketResult(PacketResultType.Disconnect);


        session.State.Position = new GamePosition();

        var charname = packet.ReadAscii();
        session.State.CharName = wFilterLib.Helper.Utility.CleanString(charname);

        charname = charname.Replace("]", "%");
        charname = charname.Replace("[", "%");

        session.State.SqlCharName = wFilterLib.Helper.Utility.CleanString(charname);
        
        //if (!Globals.PlayerStatus.ContainsKey(session.State.TokenId))
        //    return new PacketResult(PacketResultType.Disconnect);
        //Globals.PlayerStatus[session.State.TokenId].CharName = session.State.CharName;


        var pCustomIcons = new Packet((ushort)Custom.Response.Customs);
        pCustomIcons.WriteByte((byte)MsgOpcodeTypes.CustomIcons);
        pCustomIcons.WriteInt32(Globals.CustomIcons.Count);
        foreach (var icon in Globals.CustomIcons)
        {
            pCustomIcons.WriteInt32(icon.Key);
            pCustomIcons.WriteAscii(icon.Value);
        }
        session.SendPacketToClient(pCustomIcons);


        session.GetSql.UpdateHwanList(session);

        //  Program.DatabaseConnection.ChangeDatabase(Configs.Config.GetSql.ShardDatabase);
        session.State.CharId = (int) session.GetSql.Read<int>(
            $"use {Config.GetSql.ShardDatabase} Select top 1 CharID from dbo._Char where CharName16 like '{session.State.SqlCharName}'");


        session.State.CharScreen = false;

//        session.GetSql.ReadQuery(session);

        return new PacketResult(PacketResultType.Nothing);
    }
}