using wFilterLib;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Networking.Session.Struct;
using wFilterLib.SSA;
using wFilterLib.Database.Models;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
        public static PacketResult CharacterEndHandler(Packet packet, PlayerSession session)
        {
            packet = session.State.CharacterDataPacket;

                packet.Lock();

            #region Basic info   

                session.State.ServerTime = packet.ReadUInt(); //ServerTime
                session.State.RefObjId = packet.ReadUInt();
                /*session.State.Scale = */packet.ReadByte();
                session.State.CurLevel = packet.ReadByte();
                /*session.State.MaxLevel =*/ packet.ReadByte();
                session.State.ExpOffset = packet.ReadULong();
                session.State.SExpOffset = packet.ReadUInt();
                session.State.RemainGold = packet.ReadULong();
                session.State.RemainSkillPoint = packet.ReadUInt();
                /*session.State.RemainStatPoint = */packet.ReadUShort();
                /*session.State.RemainHwanCount = */packet.ReadByte();
                /*session.State.GatheredExpPoint = */packet.ReadUInt();
                /*session.State.Hp = */packet.ReadUInt();
                /*session.State.Mp = */packet.ReadUInt();
                /*session.State.AutoInverstExp = (AutoInverstFlag)*/packet.ReadByte();


                session.State.Race = (session.State.RefObjId < 14875 ? CharacterRace.Chinese : CharacterRace.Europe);

                #endregion

                #region Pk information

                /*session.State.DailyPk = */packet.ReadByte();
                /*session.State.TotalPk = */packet.ReadUShort();
                /*session.State.PkPenaltyPoint = */packet.ReadUInt();

                #endregion

                #region TitleName(HWANLEVEL)

                session.State.HwanLevel = packet.ReadByte();


                //if (!Configs.Config.GetGui.EnableGui || !Configs.Config.GetGui.GuiSwitchTitle)
                //    return new PacketResult(PacketResultType.Nothing);
                //if (session.State.HwanLevel <= 0 || session.State.HwanLevel ==255 ||
                //    session.State.CharTitles.ContainsKey(session.State.HwanLevel))
                //    return new PacketResult(PacketResultType.Nothing);
                //if (!Program.RefHwan.ContainsKey(session.State.HwanLevel))
                //    return new PacketResult(PacketResultType.Nothing);
                //Task.Run(async () => await Program.DatabaseConnection.INSERT_PLAYER_HWAN(session.State.CharName, session.State.HwanLevel));

                //session.State.CharTitles.Add(session.State.HwanLevel,
                //    session.State.Race == CharacterRace.Chinese
                //        ? Program.RefHwan[session.State.HwanLevel].Title_CH70
                //        : Program.RefHwan[session.State.HwanLevel].Title_EU70);

                #endregion

//#if !dev
//                return new PacketResult(PacketResultType.Nothing);
//#endif
                #region Pvp(Pvpstate)

                /*session.State.PvpCape = (FrPvpMode)*/packet.ReadByte();

                #endregion

                //packet.GetBytes().AsSpan().IndexOf((ushort)session.State.CharName.Length);
                //var skipItems = packet.SeekRead()
                #region Inventory

                 /*session.State.InventorySize =*/ packet.ReadByte();
                // session.State.Inventory = new List<KeyValuePair<byte, InventoryItem>>(session.State.InventorySize);
                
                var inventoryItemCount = packet.ReadByte();
            //  var ss =  packet.RemainingRead();
                for (var i = 0; i < inventoryItemCount; i++)
                {
                    var inventoryItem = new InventoryItem(packet);
                  //  session.State.Inventory.Add(new KeyValuePair<byte, InventoryItem>(inventoryItem.Slot, inventoryItem));

                    if (inventoryItem.Slot == 8)
                        session.State.IsJob = true;
                }

                #endregion

                #region AvatarInventory
                packet.ReadByte(); // AvatarInventorySize
               // session.State.AvatarInventorySize = packet.ReadByte();
              //  session.State.AvatarInventory = new List<KeyValuePair<byte, InventoryItem>>(session.State.AvatarInventorySize);
                var avatarItemCount = packet.ReadByte();
                for (var i = 0; i < avatarItemCount; i++)
                {
                    /*var avatarItem = */
                    _ = new InventoryItem(packet);
                    //   session.State.AvatarInventory.Add(new KeyValuePair<byte, InventoryItem>(avatarItem.Slot, avatarItem));
                }

                #endregion

                #region Masteries
                packet.ReadByte();

              //  session.State.Masteries = new List<KeyValuePair<uint, byte>>();
                var nextMastery = packet.ReadByte();
                while (nextMastery == 1)
                {
                     packet.ReadUInt();
                     packet.ReadByte();
                    
                    // session.State.Masteries.Add(new KeyValuePair<uint, byte>(packet.ReadUInt(), packet.ReadByte()));
                    nextMastery = packet.ReadByte();
                }

                packet.ReadByte();

                #endregion

                #region Skills

                var nextSkill = packet.ReadByte();
                while (nextSkill == 1)
                {
                    packet.ReadUInt(); //skill.ID
                    packet.ReadByte(); //skill.Enabled
                    nextSkill = packet.ReadByte();
                }
                #endregion

                #region Quests

                //Quests
                //ERROR: Wrong skill count
                var completedQuestCount = packet.ReadUShort();
                packet.ReadUInt32Array(completedQuestCount);

                var activeQuestCount = packet.ReadByte();
                // session.State.ActiveQuests = new List<RefQuest>(activeQuestCount);
                for (var i = 0; i < activeQuestCount; i++)
                {
                    packet.ReadUInt();
                    // var quest = new RefQuest(); //TODO: Add reference manager
                    // session.State.ActiveQuests.Add(quest);

                    packet.ReadByte(); //AchivementCount
                    packet.ReadByte(); //RequiresAutoShareParty
                    var type = packet.ReadByte();
                    if (type == 28)
                    {
                        packet.ReadUInt(); //remainingTime
                    }
                    packet.ReadByte(); //Status

                    if (type != 8)
                    {
                        var objectiveCount = packet.ReadByte();
                        for (var objectiveIndex = 0; objectiveIndex < objectiveCount; objectiveIndex++)
                        {
                            packet.ReadByte(); //ID
                            packet.ReadByte(); //Status
                            packet.ReadAscii(); //Name
                            var taskCount = packet.ReadByte(); //TaskCount
                            packet.ReadUInt32Array(taskCount); //TaskValues
                        }
                    }

                    if (type == 88)
                    {
                        //NPCs
                        var refObjCount = packet.ReadByte();
                        packet.ReadUInt32Array(refObjCount); //RefObjects
                    }
                }
                packet.ReadByte();

                #endregion

                #region collectionBook

                var collectionBookStartedThemeCount = packet.ReadUInt();
                for (var i = 0; i < collectionBookStartedThemeCount; i++)
                {
                    packet.ReadUInt(); //theme.Index
                    packet.ReadUInt(); //theme.StartedTimeStamp
                    packet.ReadUInt(); //theme.Pages
                }

                #endregion

                #region UniqueID

                session.State.UniqueId = packet.ReadUInt();

                #endregion

                #region Position

                //Position
                var position = new Position(packet);

                session.State.TempPosition.RegionID = position.RegionId;
                session.State.TempPosition.X = position.X;
                session.State.TempPosition.Y = position.Y;
                session.State.TempPosition.Z = position.Z;
                session.State.TempPosition.Angle = position.Angle;

                //Movement
                var hasDestination = packet.ReadBool();
                packet.ReadByte(); //Movement.Type
                if (hasDestination)
                {
                    packet.ReadUShort();
                    if (position.RegionId < short.MaxValue)
                    {        
                        //World
                        packet.ReadUShort(); //XOffset
                        packet.ReadUShort(); //YOffset
                        packet.ReadUShort(); //ZOffset
                    }
                    else
                    {
                        //Dungeon
                        packet.ReadUInt(); //XOffset
                        packet.ReadUInt(); //YOffset
                        packet.ReadUInt(); //ZOffset
                    }
                }
                else
                {
                    packet.ReadByte(); //Source //0 = Spinning, 1 = Sky-/Key-walking
                    packet.ReadUShort(); //Angel //Represents the new angle, character is looking at
                }

                #endregion

                #region State

                /*session.State.LifeState = (LifeState)*/packet.ReadByte();
                packet.ReadByte(); // State.unkByte0
                /*session.State.MotionState = (MotionState)*/packet.ReadByte();
                /*session.State.BodyMode = (BodyMode)*/packet.ReadByte(); // State.Status    //0 = None, 1 = Hwan, 2 = Untouchable, 3 = GameMasterInvincible, 5 = GameMasterInvisible, 5 = ?, 6 = Stealth, 7 = Invisible         
                packet.ReadSingle(); // State.WalkSpeed            
                packet.ReadSingle(); // State.RunSpeed            
                packet.ReadSingle(); // State.HwanSpeed

                var buffCount = packet.ReadByte();

                for (var i = 0; i < buffCount; i++)
                {
                    packet.ReadUInt(); //Buff.RefSkillID
                    packet.ReadUInt(); //Buff.Duration

                    if (Globals.SkillIds.Contains(1701213281)) //1701213281->atfe-> "auto transfer effect" like Recovery Division
                        packet.ReadBool(); //IsCreator
                }
                #endregion

                #region CharName

                if (session.State.CharName != packet.ReadAscii())
                    return new PacketResult(PacketResultType.Disconnect);

                #endregion

                #region Job

                session.State.JobName = packet.ReadAscii();
                session.State.JobType = (JobType)packet.ReadByte();
                /*session.State.JobLevel =*/ packet.ReadByte();
                /*session.State.JobExp =*/ packet.ReadUInt();
                /*session.State.JobContribution =*/ packet.ReadUInt();
                /*session.State.JobReward =*/ packet.ReadUInt();
                /*session.State.PvpState = (PvpState)*/packet.ReadByte();
                session.State.OnTransport = packet.ReadBool();
                /*session.State.InCombat =*/ packet.ReadBool();
                //Console.WriteLine($"PvpState: {session.State.PvpState}");

                if (session.State.OnTransport)
                {
                    /*session.State.Transport = */packet.ReadUInt();
                }

                packet.ReadByte(); // PVPFlag                 //0 = Red Side, 1 = Blue Side, 0xFF = None
                packet.ReadULong(); // GuideFlag
                session.State.UserJid = packet.ReadInt32();
                // packet.ReadByte(); //GMFlag
                // packet.ReadByte(); //ActivationFlag  //ConfigType:0 --> (0 = Not activated, 7 = activated) //ConfigType:1
                                   //
                // var hotKeysCount = packet.ReadByte();
                // for (var i = 0; i < hotKeysCount; i++)
                // {
                //     packet.ReadByte(); //hotkey.SlotSeq
                //     packet.ReadByte(); //hotkey.SlotContentType
                //     packet.ReadUInt(); //hotkey.SlotData
                // }

                // packet.ReadUShort(); //AutoHPConfig            //ConfigType:11
                // packet.ReadUShort(); //AutoMPConfig            //ConfigType:12
                // packet.ReadUShort(); //AutoUniversalConfig     //ConfigType:13
                // packet.ReadByte(); //AutoPotionDelay         //ConfigType:14

                // var blockedWhisperCount = packet.ReadByte();  

                // for (var i = 0; i < blockedWhisperCount; i++)
                // {
                //     packet.ReadAscii(); //Target
                // }
                //
                // packet.ReadUInt(); //unkUShort0      //Structure changes!!!
                // packet.ReadByte(); //unkByte4        //Structure changes!!!


                #endregion

                session.State.CharacterDataPacket = null;
            
            return new PacketResult(PacketResultType.Nothing);
        }



        public static PacketResult CharacterDataHandler(Packet pck, PlayerSession session)
        {
            session.State.CharacterDataPacket.WriteByteArray(pck.GetBytes());
            return new PacketResult(PacketResultType.Nothing);
        }

        public static PacketResult CharacterBeginHandler(Packet pck, PlayerSession session)
        {
            session.State.CharacterDataPacket = new Packet((ushort)wFilterLib.Opcodes.Agent.Response.CHAR_DATA);
            return new PacketResult(PacketResultType.Nothing);
        }
    }

}
