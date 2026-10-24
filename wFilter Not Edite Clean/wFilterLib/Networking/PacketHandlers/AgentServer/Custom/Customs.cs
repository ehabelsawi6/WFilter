using wFilterLib;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.Opcodes;
using wFilterLib.SSA;
using System.Globalization;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public enum MsgOpcodeTypes : byte
    {
        ClientInfo = 0x01,
        GUISettings = 0x99,
        AntiPHBOT = 55,
        Chest_Response = 0x17,
        Chest_RequestItem = 0x18,
        Chest_RequestList = 0x19,
        Chest_RequestAllList = 0x20,
        TitlesList = 0x21,
        TitlesListRemoveRequest = 0x22,
        TitlesListChangeRequest = 0x23,
        UniqueStatusRequest = 0x24,
        UniqueStatusResponse = 0x25,
        OnCharacterInfoRequest = 0x40,
        OnCharacterInfo = 0x41,
        OnJobStatusInfo = 0x56,
        OnJobStatusBuyCoins = 0x57,
        OnJobStatusBuyImmo = 0x58,
        OnJobStatusBuyBox = 0x59,
        CustomIcons = 0x79,
        CustomTitleUpdate = 0x81,
        GrantNameChange = 0x80,
        OnEventTimesRequest = 0x60,
        EventTimesResponse = 0x61,
        UnLockRequest = 0x62,
        UnLockResponse = 0x63,
        LockRequest = 0x64,
        LockResponse = 0x65,
        DShopRequest = 0x30,
        DShopResponse = 0x31
    };

    public static PacketResult HandleCustoms(Packet packet, PlayerSession session)
    {
        var operationType = (MsgOpcodeTypes)packet.ReadByte();

        switch (operationType)
        {
            case MsgOpcodeTypes.OnEventTimesRequest:
                if (!Globals.EventTimeList.IsEmpty)
                {
                    var eventTimes = new Packet((ushort)Custom.Response.Customs);

                    eventTimes.WriteByte((byte)MsgOpcodeTypes.EventTimesResponse);

                    eventTimes.WriteByte((byte)Globals.EventTimeList.Count);
                    foreach (var event_time in Globals.EventTimeList.OrderBy(p => p.Value.Name))
                    {
                        eventTimes.WriteAscii(event_time.Value.Name); // event name
                        eventTimes.WriteAscii(event_time.Value.Time + " " + event_time.Value.Day); // event time
                    }

                    session.SendPacketToClient(eventTimes);

                }

                break;
            case MsgOpcodeTypes.ClientInfo:
                session.State.JobType = (JobType)packet.ReadByte();
                session.State.CurLevel = packet.ReadByte();
                session.State.IsJob = session.State.JobType != JobType.None;
                break;

            case MsgOpcodeTypes.TitlesListRemoveRequest:
                var pTitleRemove = new Packet((ushort)Custom.Framework.MAIN);
                pTitleRemove.WriteUInt(session.State.UniqueId);
                pTitleRemove.WriteByte(2);
                pTitleRemove.WriteByte(0);
                session.SendPacketToServer(pTitleRemove);
                break;
            case MsgOpcodeTypes.TitlesListChangeRequest:
                var titleId = packet.ReadByte();
                if (session.State.CharTitles.Contains(titleId) ||
                    (session.State.CustomTitleName.Length > 0 && titleId == 255))
                {
                    var pTitleChange = new Packet((ushort)Custom.Framework.MAIN);
                    pTitleChange.WriteUInt(session.State.UniqueId);
                    pTitleChange.WriteByte(2);
                    pTitleChange.WriteByte(titleId);
                    session.SendPacketToServer(pTitleChange);
                }

                break;
            case MsgOpcodeTypes.UniqueStatusRequest:
                lock (_lock)
                {
                    if (Globals.UniquesData.Count > 0)
                    {
                        var responsePacket = new Packet((ushort)Custom.Response.Customs);
                        responsePacket.WriteUInt8(MsgOpcodeTypes.UniqueStatusResponse);
                        responsePacket.WriteUInt8(Globals.UniquesData.Count);
                        foreach (var data in Globals.UniquesData)
                        {
                            responsePacket.WriteUInt32(data.RefObjId);
                            responsePacket.WriteBool(data.State);
                            responsePacket.WriteAscii(data.KillerName);

                            var endTime = DateTime.Now;

                            var lastSeen = string.Empty;
                            lastSeen = Convert.ToString((endTime - data.Time).Days);
                            lastSeen += "d ";
                            lastSeen += Convert.ToString((endTime - data.Time).Hours);
                            lastSeen += "h ";
                            lastSeen += Convert.ToString((endTime - data.Time).Minutes);
                            lastSeen += "m ";
                            lastSeen += Convert.ToString((endTime - data.Time).Seconds);
                            lastSeen += "s ago";

                            responsePacket.WriteAscii(lastSeen);
                        }

                        session.SendPacketToClient(responsePacket);

                    }
                }

                break;
            case MsgOpcodeTypes.OnCharacterInfoRequest:
                var targetUniqueId = packet.ReadUInt();
                if (targetUniqueId != 0)
                {
                    var target = SessionManager.GetStateByUniqueID(targetUniqueId);

                    if (target != null)
                    {
                        if (!string.IsNullOrEmpty(target.State.CustomTitleName) ||
                            target.State.NameColor != 0 ||
                            target.State.TitleColor != 0 || target.State.CustomIconId != 0 ||
                            target.State.DSPoints != 0)
                        {

                            var customPacket = new Packet((ushort)Custom.Response.Customs);
                            customPacket.WriteByte(0x41);

                            customPacket.WriteUInt(targetUniqueId);
                            customPacket.WriteInt32(target.State.NameColor);
                            customPacket.WriteInt32(target.State.TitleColor);


                            customPacket.WriteBool(!string.IsNullOrEmpty(target.State.CustomTitleName));
                            if (!string.IsNullOrEmpty(target.State.CustomTitleName))
                                customPacket.WriteAscii(target.State.CustomTitleName);

                            customPacket.WriteInt32(target.State.CustomIconId);
                            customPacket.WriteByte(0);
                            customPacket.WriteInt32(0);

                            //customPacket.WriteBool(session.State.IsLocked);

                            session.SendPacketToClient(customPacket);

                            session.AfkStatus(target);
                        }
                    }
                }

                break;
            case MsgOpcodeTypes.CustomTitleUpdate:
                var NewCustomTtile = wFilterLib.Helper.Utility.CleanString(packet.ReadAscii());

                if (NewCustomTtile.Length > 50 || string.IsNullOrEmpty(NewCustomTtile))
                    return new PacketResult(PacketResultType.Block);

                if (NewCustomTtile.ToLower().Contains("gm")
                  //  || NewCustomTtile.ToLower().Contains("game master")
                  //  || NewCustomTtile.ToLower().Contains("gamemaster")
                    || NewCustomTtile.ToLower().Contains("master")
                    || NewCustomTtile.ToLower().Contains("helper")
                    || NewCustomTtile.ToLower().Contains("developer")
                    || NewCustomTtile.ToLower().Contains("dev")
                    || NewCustomTtile.ToLower().Contains("supporter")
                    || NewCustomTtile.ToLower().Contains("support")
                    || NewCustomTtile.ToLower().Contains("assistant")
                    || NewCustomTtile.ToLower().Contains("admin")
                    || NewCustomTtile.ToLower().Contains("administrator")
                    || NewCustomTtile.ToLower().Contains("streamer")
                    || NewCustomTtile.ToLower().Contains("owner")
                    || NewCustomTtile.ToLower().Contains("captain")
                    || NewCustomTtile.ToLower().Contains("general")
                    || NewCustomTtile.ToLower().Contains("vip")
                    || NewCustomTtile.ToLower().Contains("unique")
                    || NewCustomTtile.ToLower().Contains("hunter")
                    || NewCustomTtile.ToLower().Contains("trader")
                    || NewCustomTtile.ToLower().Contains("thief")
                    || NewCustomTtile.ToLower().Contains("seller")
                    || NewCustomTtile.ToLower().Contains("hero")
                   )
                {
                    session.SendNotice("It's not allowed to use this title.");
                    return new PacketResult(PacketResultType.Block);
                }

                if (session.State.DSPoints != 0)
                {
                    if (Globals.DShopCustomTitlePrice > session.State.DSPoints)
                    {
                        session.SendBlueNotice($"You don't have enough DS-Points !");
                        return new PacketResult(PacketResultType.Block);
                    }

                    session.State.CustomTitleName = NewCustomTtile;


                    session.State.DSPoints -= Globals.DShopCustomTitlePrice;
                    session.GetSql.ExecuteNonQuery(
                        $"use wfilter update _CharacterCustoms set CustomTitleName= '{NewCustomTtile}', DSPoints = {session.State.DSPoints} where CharName like '{session.State.SqlCharName}'");

                    //session.GetSql.ExecuteNonQuery(
                    //    $"use wfilter UPDATE _CharacterCustoms SET CustomTitleName= '{NewCustomTtile}', CustomTitleCredits = {session.State.CustomTitleCredits} WHERE CharName like '{session.State.SqlCharName}'");


                    var pCustomTitle = new Packet((ushort)Custom.Response.Customs);
                    pCustomTitle.WriteUInt8(MsgOpcodeTypes.OnCharacterInfo);
                    pCustomTitle.WriteInt32(session.State.UniqueId);
                    pCustomTitle.WriteInt32(session.State.NameColor);
                    pCustomTitle.WriteInt32(session.State.TitleColor);
                    pCustomTitle.WriteBool(!string.IsNullOrEmpty(session.State.CustomTitleName));
                    if (!string.IsNullOrEmpty(session.State.CustomTitleName))
                        pCustomTitle.WriteAscii(session.State.CustomTitleName);

                    pCustomTitle.WriteInt32(session.State.CustomIconId);
                   // pCustomTitle.WriteByte(session.State.CustomTitleCredits);
                    pCustomTitle.WriteInt32(session.State.DSPoints);

                    SessionManager.SendPacketToNearestPlayers(pCustomTitle, session.State.Position.RegionID);

                    //.....

                    session.LiveTitleUpdate(255);

                }
                else
                {
                    session.SendBlueNotice("Sorry you don't have enough DS-Points for upgrading your title.");
                    return new PacketResult(PacketResultType.Block);
                }

                break;
            case MsgOpcodeTypes.GrantNameChange:

                var cNewGrantname = wFilterLib.Helper.Utility.CleanString(packet.ReadAscii());
                if (cNewGrantname.Length > 12 || string.IsNullOrEmpty(cNewGrantname))
                {
                    session.SendBlueNotice("Please make sure the new Grant Name isn't (empty / > 12 length)");
                    return new PacketResult(PacketResultType.Block);
                }

                var grantNameChange = new Packet((ushort)Custom.Framework.MAIN);
                grantNameChange.WriteUInt(session.State.UniqueId);
                grantNameChange.WriteByte(1); // grantname update
                grantNameChange.WriteAscii(cNewGrantname);
                session.SendPacketToServer(grantNameChange);
                break;

            case MsgOpcodeTypes.UnLockRequest:
                //if(packet.ReadInt32() == session.State.UniqueId)
                //{
                var pinCode = wFilterLib.Helper.Utility.CleanString(packet.ReadAscii());
                var rememberMe = packet.ReadBool();

                if (pinCode.Length == 4)
                {
                    if (pinCode == session.State.PinCode)
                    {
                        if (rememberMe && session.State.Hwid != session.State.SavedPC)
                        {
                            session.GetSql.ExecuteNonQuery(
                                $"use wfilter update _CharacterCustoms set SavedPC = '{session.State.Hwid}' where CharName like '{session.State.SqlCharName}'");
                        }

                        session.State.IsLocked = false;
                        session.SendPacketToServer(session.State.GameReadyPacket);

                        var pUnlock = new Packet((ushort)Custom.Response.Customs);
                        pUnlock.WriteUInt8(MsgOpcodeTypes.UnLockResponse);
                        pUnlock.WriteUInt8(2);

                        session.SendPacketToClient(pUnlock);
                    }
                    else
                    {
                        session.State.PinFailedTimes++;
                        session.SendBlueNotice(
                            $"You have entered a wrong PIN Code [{session.State.PinFailedTimes} / 3]");
                        if (session.State.PinFailedTimes >= 3)
                            return new PacketResult(PacketResultType.Disconnect);

                    }
                }

                //}
                return new PacketResult(PacketResultType.Block);
            case MsgOpcodeTypes.LockRequest:
                var pinCode2 = wFilterLib.Helper.Utility.CleanString(packet.ReadAscii());

                if (session.State.PinCode.Length == 4)
                {
                    session.SendBlueNotice($"Your Character is already locked !");
                    return new PacketResult(PacketResultType.Block);
                }
                else if (pinCode2.Length > 4)
                    return new PacketResult(PacketResultType.Disconnect,
                        $"{session.State.CharName} tried to play around lock system len !");

                session.GetSql.ExecuteNonQuery(
                    $"use wfilter update _CharacterCustoms set PINCode = {int.Parse(pinCode2)},IsLocked = 1 where CharName like '{session.State.SqlCharName}'");

                session.State.PinCode = pinCode2;

                session.SendNotice(
                    $"Your Character has been locked ,Restart to check it out ,Please remember your PIN Code [{pinCode2}]");

                break;
            case MsgOpcodeTypes.DShopRequest:

                if (packet.ReadUInt() == session.State.UniqueId)
                {
                    var type = packet.ReadByte();

                    if (type == 1) // buy titleName
                    {
                        var tId = packet.ReadByte();
                        if (session.State.CharTitles.Contains(tId))
                        {
                            session.SendBlueNotice($"You are already own this title !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (!Globals.DShopTitlesList.ContainsKey(tId))
                        {
                            session.SendBlueNotice($"This title is not for sell !! , trying smth buddy ?");
                            return new PacketResult(PacketResultType.Block);
                        }

                        if (Globals.DShopTitlesList[tId].Price > session.State.DSPoints)
                        {
                            session.SendBlueNotice($"You don't have enough DS-Points !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        session.State.DSPoints -= Globals.DShopTitlesList[tId].Price;
                        session.GetSql.ExecuteNonQuery(
                            $"use wfilter update _CharacterCustoms set DSPoints = {session.State.DSPoints} where CharName like '{session.State.SqlCharName}'");

                        session.GetSql.ExecuteNonQuery(
                            $"use wfilter insert into _Title_Storage(CharName, TitleID) values('{session.State.CharName}', {tId})");

                        // session.LiveTitleUpdate(tId);
                        session.State.CharTitles.Add(tId);

                        var titlesPacket = new Packet((ushort)Custom.Response.Customs);
                        titlesPacket.WriteUInt8(0x21);
                        titlesPacket.WriteUInt16(session.State.CharTitles.Count);
                        foreach (var titleId2 in session.State.CharTitles)
                            titlesPacket.WriteByte(titleId2);

                        session.SendPacketToClient(titlesPacket);

                        session.SendGreenNotice($"Your New TitleName has been added to Your Title Manager !");


                        goto update_Client;


                    }

                    else if (type == 2)
                    {
                        var nameColor = packet.ReadUInt().ToString("X");

                        if (Globals.DShopNameColorPrice > session.State.DSPoints)
                        {
                            session.SendBlueNotice($"You don't have enough DS-Points !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        session.State.DSPoints -= Globals.DShopNameColorPrice;

                        session.GetSql.ExecuteNonQuery(
                            $"use wfilter update _CharacterCustoms set DSPoints = {session.State.DSPoints},NameColor ='{nameColor}'  where CharName like '{session.State.SqlCharName}'");
                        session.State.NameColor = int.Parse(nameColor, NumberStyles.HexNumber);

                        session.SendGreenNotice($"Your New Name Color has been assigned to your character !");

                        goto update_Client;
                    }

                    else if (type == 3)
                    {
                        var titleColor = packet.ReadUInt().ToString("X");

                        if (Globals.DShopTitleColorPrice > session.State.DSPoints)
                        {
                            session.SendBlueNotice($"You don't have enough DS-Points !");
                            return new PacketResult(PacketResultType.Block);
                        }

                        session.State.DSPoints -= Globals.DShopTitleColorPrice;

                        session.GetSql.ExecuteNonQuery(
                            $"use wfilter update _CharacterCustoms set DSPoints = {session.State.DSPoints},TitleColor ='{titleColor}'  where CharName like '{session.State.SqlCharName}'");
                        session.State.TitleColor = int.Parse(titleColor, NumberStyles.HexNumber);

                        session.SendGreenNotice($"Your New Title Color has been assigned to your character !");

                        goto update_Client;
                    }

                    update_Client:
                    {
                        var pCustomTitle = new Packet((ushort)Custom.Response.Customs);
                        pCustomTitle.WriteUInt8(MsgOpcodeTypes.OnCharacterInfo);
                        pCustomTitle.WriteInt32(session.State.UniqueId);
                        pCustomTitle.WriteInt32(session.State.NameColor);
                        pCustomTitle.WriteInt32(session.State.TitleColor);
                        pCustomTitle.WriteBool(!string.IsNullOrEmpty(session.State.CustomTitleName));
                        if (!string.IsNullOrEmpty(session.State.CustomTitleName))
                            pCustomTitle.WriteAscii(session.State.CustomTitleName);

                        pCustomTitle.WriteInt32(session.State.CustomIconId);
                      //  pCustomTitle.WriteByte(session.State.CustomTitleCredits);
                        pCustomTitle.WriteInt32(session.State.DSPoints);
                        if (type == 1)
                            session.SendPacketToClient(pCustomTitle);
                        else
                            SessionManager.SendPacketToNearestPlayers(pCustomTitle, session.State.Position.RegionID);

                    }

                }

                break;
            default:
                return new PacketResult(PacketResultType.Block);
        }

        return new PacketResult(PacketResultType.Block);
    }
}
