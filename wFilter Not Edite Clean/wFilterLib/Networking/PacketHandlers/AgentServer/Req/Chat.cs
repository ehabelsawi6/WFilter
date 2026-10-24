using wFilterLib.Networking.Session;
using wFilterLib.Configs;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Opcodes;
using wFilterLib.SSA;
using wFilterLib;
using wFilterLib.Events;

namespace wkFilter.NetworkStuff.PacketHandler.Agent;

public partial class AgentHandler
{
    public static PacketResult ChatRequest(Packet pck, PlayerSession? session)
    {
        if (session == null)
            return new PacketResult(PacketResultType.Disconnect);
        
        var chatType = pck.ReadByte();
        var message = "";

        if (chatType is 1 or 6 or 3){
            message = pck.ReadAscii();
        }

        if (chatType is 1 or 6 or 3 && AutoEventManager.HandleChat(session, message, chatType))
            return new PacketResult(PacketResultType.Block);

        if (Config.GetSurvivalEvent.Enable)
            if (chatType is 1 or 3 && (message.ToLower().Contains("!register") || message.ToLower().Contains("!cancel")))
        {
            if (!Globals.SurvivalEvent)
            {
                session.SendBlueNotice("there is no event running atm...");
                return new PacketResult(PacketResultType.Block);
            }

            if (Globals.SurvivalEvent && !Globals.SurvivalEventRegister)
            {
                session.SendBlueNotice("[Survival Event] Register is closed");
                return new PacketResult(PacketResultType.Block);
            }


            if (Globals.SurvivalEvent && Globals.SurvivalEventRegister)
            {
                if (message.Contains("!register"))
                { 
                    if (SessionManager.GetSurvivalCountForHwid(session.State.Hwid) > 1)
                    {
                        session.SendBlueNotice("[Survival Event] You already registered with another character");
                        return new PacketResult(PacketResultType.Block);
                    }
                    
                    if (Globals.SurvivalEventRegisteredCharacters.Contains(session.State.CharName))
                    {
                        session.SendBlueNotice("[Survival Event] You already registered");
                        return new PacketResult(PacketResultType.Block);
                    }
                    else
                    {
                        if (Globals.SurvivalEventRegisteredCharacters.Count >= Config.GetSurvivalEvent.MaxPlayers)
                        {
                            session.SendBlueNotice("[Survival Event] Sorry there is no place for u , Register list is full");
                            return new PacketResult(PacketResultType.Block);
                        }

                        Globals.SurvivalEventRegisteredCharacters.Add(session.State.CharName);
                        session.SendGreenNotice("[Survival Event] You have successfully registered");
                        return new PacketResult(PacketResultType.Block);
                    }
                }
                else if (message.Contains("!cancel"))
                {
                    if (!Globals.SurvivalEventRegisteredCharacters.Contains(session.State.CharName))
                    {
                        session.SendBlueNotice("[Survival Event] You are not registered");
                        return new PacketResult(PacketResultType.Block);
                    }
                    else
                    {
                        Globals.SurvivalEventRegisteredCharacters.Remove(session.State.CharName);
                        session.SendGreenNotice("[Survival Event] You have successfully unregister");
                        return new PacketResult(PacketResultType.Block);
                    }
                }
            }
        }

        if (Config.GetExtra.BadWords.Count > 0 && (chatType == 1 || chatType == 6 || chatType == 3))
        {

            foreach (var word in Config.GetExtra.BadWords)
            {
                if (message.ToLower().Contains(word))
                {
                    session.SendNotice("Some expressions are not allowed in our server.");
                    return new PacketResult(PacketResultType.Block);
                }

            } 
        }

            #region AngelRoad

            if (Config.IsAngelRoad && (chatType == 1 || chatType == 3))
            {
                if(chatType == 1) // normal chat
                {
                    if (message.Contains("roll the dice"))
                    {
                        if (!Globals.RollTheDice)
                        {
                            string fortressGuildOwner = session.GetSql.Read<string>("select top 1 chr.CharName16 from sro_vt_shard.._char as chr inner join sro_vt_shard.._GuildMember as guild ON chr.CharID = guild.CharID inner join sro_vt_shard.._SiegeFortress as fortress ON guild.GuildID = fortress.GuildID where guild.MemberClass =0");

                            if (fortressGuildOwner == session.State.CharName)
                            {
                                if (Globals.RollDiceLastTime > DateTime.Now)
                                {
                                    session.SendNotice($"Your next Roll The Dice starts at {Globals.RollDiceLastTime}!");
                                    return new PacketResult(PacketResultType.Block);
                                }

                                Globals.RollTheDice = true;
                                SessionManager.SendNoticeToAll($"[{fortressGuildOwner}] has started Roll The Dice,type \"roll the dice\" in chat to participate", 4);
                                //   AgentContext2.SendNoticeOnline($"[{fortressGuildOwner}] has started Roll The Dice,type \"roll the dice\" in chat to participate");

                                new Thread(Globals.RollTheDiceNormal).Start();

                                Globals.RollDiceCharList.Add(session.State.SqlCharName);
                            }
                            else
                                session.SendNotice("The fortress guild owner only allowed to start Roll The Dice!");
                        }
                        else
                        {
                            if (Globals.RollDiceCharList.Contains(session.State.SqlCharName))
                                session.SendNotice("You have already participated once!");
                            else
                            {
                                Globals.RollDiceCharList.Add(session.State.SqlCharName);
                                session.SendNotice("You have successfully participated in Roll The Dice!");
                            }
                        }
                        return new PacketResult(PacketResultType.Block);
                    }

                    if (message.Contains("reputation"))
                    {
                        string itemName = message.Split(' ')[1];

                        session.GetSql.ExecuteNonQuery($"exec sro_vt_shard..__RepExchange '{session.State.SqlCharName}','{itemName}'");
                        return new PacketResult(PacketResultType.Block);
                    }

                    if (message.Contains("coupon-reset-skill"))
                    {
                        session.GetSql.ExecuteNonQuery($"exec sro_vt_shard..__ResetPlayerSkillsProcedure '{session.State.SqlCharName}'");
                        return new PacketResult(PacketResultType.Disconnect);
                    }

                    if (message.Contains("coupon-reset-stats"))
                    {
                        session.GetSql.ExecuteNonQuery($"exec sro_vt_shard..__ResetPlayerStatProcedure '{session.State.SqlCharName}'");
                        return new PacketResult(PacketResultType.Disconnect);
                    }

                    if (message.Contains("coupon-weapon-ara") || message.Contains("coupon-weapon-arb") || message.Contains("coupon-weapon-arc")|| message.Contains("coupon-weapon-ard"))
                    {
                        string weaponCodeName = "ITEM_%_17_S_RARE_CHRISTMAS";
                        string weaponType = message.Split(' ')[0];
                        string weaponName = message.Split(' ')[1].ToLower();


                        bool error = false;

                        if (weaponType.Contains("ara"))
                            weaponCodeName = weaponCodeName.Replace("_S_", "_C_").Replace("_CHRISTMAS","").Replace("17","15");
                        else if (weaponType.Contains("arb"))
                            weaponCodeName = weaponCodeName.Replace("_S_", "_C_").Replace("_CHRISTMAS","").Replace("17","16");
                        else if (weaponType.Contains("arc"))
                            weaponCodeName = weaponCodeName.Replace("_S_", "_C_");
                        else if (weaponType.Contains("ard"))
                            weaponCodeName = weaponCodeName.Replace("_S_", "_D_");


                        switch (weaponName)
                        {
                            case "axe":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_AXE");
                                break;
                            case "crossbow":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_CROSSBOW");
                                break;
                            case "cutter":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_DAGGER");
                                break;
                            case "cursed-rod":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_DARKSTAFF");
                                break;
                            case "rod":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_STAFF");
                                break;
                            case "stromer":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_TSTAFF");
                                break;
                            case "sword-eu":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_SWORD");
                                break;
                            case "crusader":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_TSWORD");
                                break;
                            case "shield-eu":
                                weaponCodeName = weaponCodeName.Replace("%", "EU_SHIELD");
                                break;
                            case "blade":
                                weaponCodeName = weaponCodeName.Replace("%", "CH_BLADE");
                                break;
                            case "shooter":
                                weaponCodeName = weaponCodeName.Replace("%", "CH_BOW");
                                break;
                            case "shield-ch":
                                weaponCodeName = weaponCodeName.Replace("%", "CH_SHIELD");
                                break;
                            case "spear":
                                weaponCodeName = weaponCodeName.Replace("%", "CH_SPEAR");
                                break;
                            case "sword-ch":
                                weaponCodeName = weaponCodeName.Replace("%", "CH_SWORD");
                                break;
                            case "polearm":
                                weaponCodeName = weaponCodeName.Replace("%", "CH_TBLADE");
                                break;


                            default:
                                session.SendBlueNotice("Unknown Weapon Name!");
                                error = true;
                                break;
                        }

                        if (error)
                            return new PacketResult(PacketResultType.Block);


                        session.GetSql.ExecuteNonQuery($"exec sro_vt_shard..__AddCouponWeaponProcedure '{session.State.SqlCharName}','{weaponCodeName}'");
                        return new PacketResult(PacketResultType.Block);
                    }
                }

                else if(chatType == 3) // gm chat
                {
                    if (message.Contains("roll the dice"))
                    {
                        if (!Globals.RollTheDice)
                        {
                            
                            Globals.RollTheDice = true;
                            SessionManager.SendNoticeToAll($"[{session.State.CharName}] has started Roll The Dice,type \"roll the dice\" in chat to participate",4);

                            new Thread(Globals.RollTheDiceGM).Start();

                            Globals.RollDiceCharList.Add(session.State.SqlCharName);
                        }
                        else
                            session.SendNotice("Roll the dice is already running");

                        return new PacketResult(PacketResultType.Block);
                    }


                    if (message.Contains("eventstart"))
                    {
                        session.GetSql.ExecuteNonQuery($"exec sro_vt_log.._CustomEventControl 1");
                        return new PacketResult(PacketResultType.Block);
                    }
                    else if (message.Contains("eventtemp"))
                    {
                        session.GetSql.ExecuteNonQuery($"exec sro_vt_log.._CustomEventControl 2");
                        return new PacketResult(PacketResultType.Block);

                    }
                    else if (message.Contains("eventend"))
                    {
                        session.GetSql.ExecuteNonQuery($"exec sro_vt_log.._CustomEventControl 3");
                        return new PacketResult(PacketResultType.Block);
                    }
                    else if (message.StartsWith("autoevent", StringComparison.OrdinalIgnoreCase) ||
                             message.StartsWith("!autoevent", StringComparison.OrdinalIgnoreCase))
                    {
                        AutoEventManager.HandleChat(session, message, chatType);
                        return new PacketResult(PacketResultType.Block);
                    }
                }
            }

            #endregion
        

        if (chatType == 7)
        {
            if (Globals.GMControlList.ContainsKey(session.State.UserName.ToLower()))
            {
                var GM = Globals.GMControlList[session.State.UserName.ToLower()];


                if (!GM.Notice)
                {
                    session.SendNotice("You are not allowed to send notice");
                    return new PacketResult(PacketResultType.Block);
                }
            }
            else
            {
                session.SendNotice("You are not allowed to use GM Commands");
                return new PacketResult(PacketResultType.Block);
            }
            pck.ReadByte();
            message = pck.ReadAscii();


            if (message.StartsWith('1'))
            {
                SessionManager.SendNoticeToAll(message.Remove(0, 1), 1);
                return new PacketResult(PacketResultType.Block);
            }
            else if (message.StartsWith('2'))
            {
                SessionManager.SendNoticeToAll(message.Remove(0, 1), 2);
                return new PacketResult(PacketResultType.Block);
            }
            else if (message.StartsWith('4'))
            {
                SessionManager.SendNoticeToAll(message.Remove(0, 1), 4);
                return new PacketResult(PacketResultType.Block);
            }
            else
            {
                SessionManager.SendNoticeToAll(message, 0);
                return new PacketResult(PacketResultType.Block);

            }
        }




        return new PacketResult(PacketResultType.Nothing);
    }

    public static PacketResult ChatResponse(Packet pck, PlayerSession session)
    {
        var chatType = pck.ReadByte();


        if (chatType == 6)
        {
            string CharName16 = pck.ReadAscii();
            string CharName16_copy = CharName16;
            string Message = pck.ReadAscii();

            if (Config.GetLogin.ExcludedAccounts.Contains(session.State.UserName))
            {
                if (Message.StartsWith("1`"))
                {
                    Message = Message.Remove(0, 2);
                    session.State.CurrentGlobalColor = 0x9D2235;
                }
                else if (Message.StartsWith("2`"))
                {
                    Message = Message.Remove(0, 2);
                    session.State.CurrentGlobalColor = 0x0080ff;
                }
                else if (Message.StartsWith("3`"))
                {
                    Message = Message.Remove(0, 2);
                    session.State.CurrentGlobalColor = 0x008b8b;
                }
                else if (Message.StartsWith("4`"))
                {
                    Message = Message.Remove(0, 2);
                    session.State.CurrentGlobalColor = 0x2ef600;
                }
                else if (Message.StartsWith("5`"))
                {
                    Message = Message.Remove(0, 2);
                    session.State.CurrentGlobalColor = 0xFF4500;
                }
                else if (Message.StartsWith("6`"))
                {
                    Message = Message.Remove(0, 2);
                    session.State.CurrentGlobalColor = 0xFF0000;
                }
                else if (Message.StartsWith("7`"))
                {
                    Message = Message.Remove(0, 2);
                    session.State.CurrentGlobalColor = 0x8b1a89;
                }
            }

            string Message_copy = Message;

            if (CharName16.ToLower() == session.State.CharName.ToLower())
            {
                var pBuffer = new Packet((ushort)Custom.Response.Customs);
                pBuffer.WriteByte(0x0F);
                pBuffer.WriteByte(0x05);
                pBuffer.WriteByte(0);

                if (!string.IsNullOrEmpty(session.State.m_CustomLinkedItemName))
                {
                    var leftmsg = Message.Substring(0, session.State.m_GlobalLinkedItemBegin);
                    var rightmsg = Message.Substring(leftmsg.Length);

                    var tempMsg = leftmsg + session.State.m_CustomLinkedItemName + rightmsg;
                    var wholeMsg = $"{CharName16}:{tempMsg}";

                    pBuffer.WriteUnicode(wholeMsg);
                }
                else
                {
                    pBuffer.WriteUnicode($"{CharName16}:{Message}");
                }

                pBuffer.WriteByte(0x06); // global chat type (6= Global)
                pBuffer.WriteUInt(session.State.CurrentGlobalColor); // 0xFFFF00 yellow default color
                pBuffer.WriteUInt(session.State.UniqueId);


                if (session.State.m_GlobalLinkedItemSlot != 0)
                {
                    var g = session.GetSql.GetItemForGlobalLinking(session.State.CharId, session.State.m_GlobalLinkedItemSlot);
                    byte TypeID1, TypeID2, TypeID3, TypeID4;

                    var objdata = Globals.RefObjCommon[g.RefItemID];
                    if (objdata != null && objdata.ID != 0)
                    {
                        TypeID1 = objdata.TypeID1;
                        TypeID2 = objdata.TypeID2;
                        TypeID3 = objdata.TypeID3;
                        TypeID4 = objdata.TypeID4;
                    }
                    else
                        goto getRidOfIT;

                    if ((TypeID1 == 3 && TypeID2 == 2 && TypeID3 == 1 && TypeID4 == 1) || (TypeID1 == 3 && TypeID2 == 2 && TypeID3 == 1 && TypeID4 == 2))
                    {
                        pBuffer.WriteByte(1);
                        pBuffer.WriteUInt(0);
                        pBuffer.WriteUInt(g.RefItemID);

                        if (TypeID2 == 2 && TypeID4 == 2 && g.Data != 0) // ITEM_COS_PICK
                        {
                            var gPet = session.GetSql.GetGrabPetInfo(g.Data);

                            if (gPet.State is 1 or 3) // Alive
                            {
                                if (gPet.RefCharID != 0)
                                {
                                    pBuffer.WriteByte(3);
                                    pBuffer.WriteUInt(gPet.RefCharID);
                                    if (!string.IsNullOrEmpty(gPet.PetName))
                                        pBuffer.WriteAscii(gPet.PetName);
                                    else
                                        pBuffer.WriteUShort(0);
                                    pBuffer.WriteUInt(gPet.RentTime);
                                    pBuffer.WriteByte(0);
                                }
                                else pBuffer.WriteByte(1);
                            }
                            else if (gPet.State == 0) //Dead
                                pBuffer.WriteByte(1);
                        }
                        else if (TypeID2 == 2 && TypeID4 == 1) // ITEM_COS_GROWTH
                        {
                            var aPet = session.GetSql.GetAttackPetInfo(g.Data);

                            if (aPet.State is 1 or 3) // Alive
                            {
                                if (aPet.RefCharID != 0)
                                {
                                    pBuffer.WriteByte(3);
                                    pBuffer.WriteUInt(aPet.RefCharID);
                                    if (!string.IsNullOrEmpty(aPet.PetName))
                                        pBuffer.WriteAscii(aPet.PetName);
                                    else
                                        pBuffer.WriteUShort(0);
                                    pBuffer.WriteByte(0);
                                }
                                else pBuffer.WriteByte(1);
                            }
                            else if (aPet.State == 0)
                            {
                                pBuffer.WriteByte(4);
                                pBuffer.WriteUInt(aPet.RefCharID);
                                if (!string.IsNullOrEmpty(aPet.PetName))
                                    pBuffer.WriteAscii(aPet.PetName);
                                else
                                    pBuffer.WriteUShort(0);
                                pBuffer.WriteByte(0);

                            }
                        }
                    }
                    else if ((TypeID1 == 3 && TypeID2 == 1) || (TypeID1 == 3 && TypeID2 == 3))
                    {
                        pBuffer.WriteByte(1);
                        pBuffer.WriteUInt(0);
                        pBuffer.WriteUInt(g.RefItemID);

                        if (TypeID1 == 3)
                        {
                            if (TypeID2 == 1)  //ITEM_EU_CH_AVATAR
                            {
                                pBuffer.WriteByte((byte)g.OptLevel);
                                pBuffer.WriteInt64(g.Variance);
                                if (g.Data == -1 && (TypeID1 == 3 && TypeID2 == 1 && TypeID3 == 14 && TypeID4 == 1))//nasruns
                                {
                                    pBuffer.WriteByte(0); //rent time over.
                                    pBuffer.WriteByte(0); //rent time over.
                                    pBuffer.WriteByte(0); //rent time over.
                                    pBuffer.WriteByte(128); //rent time over.
                                }
                                else
                                    pBuffer.WriteInt32(g.Data);
                                pBuffer.WriteByte((byte)g.MagParamNum);

                                if (g.MagParamNum != 0)
                                {
                                    foreach (var param in g.MagParamList)
                                    {
                                        pBuffer.WriteUInt((uint)(param % 4294967296));
                                        pBuffer.WriteUInt((uint)(param / 4294967296));
                                    }
                                }
                                var (sock, adv) = session.GetSql.GetSocketAndAdv(g.ID64);
                                pBuffer.WriteByte(1);//socket flag
                                pBuffer.WriteByte((byte)sock.Count());

                                foreach (var s in sock)
                                {
                                    pBuffer.WriteByte(s.nSlot);
                                    pBuffer.WriteUShort((ushort)s.nOptID);
                                    pBuffer.WriteUShort((ushort)s.nOptLvl);
                                    pBuffer.WriteUShort((ushort)s.nParam1);
                                    pBuffer.WriteUShort((ushort)s.nParam2);
                                }

                                pBuffer.WriteByte(2);//adv flag
                                pBuffer.WriteByte((byte)adv.Count());

                                foreach (var a in adv)
                                {
                                    pBuffer.WriteByte(a.nSlot);
                                    pBuffer.WriteInt32(a.nOptID);
                                    pBuffer.WriteInt32(a.nOptValue);
                                }
                            }
                            else if (TypeID2 == 3) //ITEM_ETC
                            {
                                pBuffer.WriteUShort((ushort)g.Data); //amount
                                if (TypeID3 == 11 && (TypeID4 == 1 || TypeID4 == 2)) // magicstone & attrstone
                                    pBuffer.WriteUShort((ushort)g.OptLevel);
                                else if (TypeID3 == 14 && TypeID4 == 2) // GACHA_CARD_WIN/LOSE
                                {
                                    pBuffer.WriteByte((byte)g.MagParamNum);

                                    if (g.MagParamNum != 0)
                                    {
                                        foreach (var param in g.MagParamList)
                                        {
                                            pBuffer.WriteUInt((uint)(param % 4294967296));
                                            pBuffer.WriteUInt((uint)(param / 4294967296));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                    goto getRidOfIT;

                getRidOfIT:
                {
                    pBuffer.WriteByte(0); // has linked item ?
                }

                session.State.m_CustomLinkedItemName = string.Empty;
                session.State.m_GlobalLinkedItemBegin = 0;
                session.State.m_GlobalLinkedItemEnd = 0;
                session.State.m_GlobalLinkedItemSlot = 0;

                SessionManager.SendPacketToAll(pBuffer);

            }
            //else
            //{
            var chatReplacedPacket = new Packet((ushort)wFilterLib.Opcodes.Agent.Response.CHAT_UPDATE);
            chatReplacedPacket.WriteByte(6);
            chatReplacedPacket.WriteAscii(CharName16_copy);
            chatReplacedPacket.WriteAscii(Message_copy);
            session.SendPacketToClient(chatReplacedPacket);


            //}

            return new PacketResult(PacketResultType.Block);
        }

        return new PacketResult(PacketResultType.Nothing);
    }
}
