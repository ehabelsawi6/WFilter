using wFilterLib.SSA;

namespace wFilterLib.Database.Models;

public class InventoryItem
{
    public byte Slot { get; set; }
    public uint RefItemId { get; set; }
    public byte OptLevel { get; set; }
    public ushort MaxStack { get; set; }
    public ushort StackCount { get; set; }

    public InventoryItem(Packet packet /*,Session session, TextData textData*/)
    {
        try
        {
            //TODO: Group to decrease packet.ReadX calls

            Slot = packet.ReadByte();

            var rentType = packet.ReadUInt();
            if (rentType == 1)
            {
                packet.ReadUShort(); //CanDelete
                packet.ReadUInt(); //PeriodBeginTime
                packet.ReadUInt(); //PeriodEndTime
            }
            else if (rentType == 2)
            {
                packet.ReadUShort(); //CanDelete
                packet.ReadUShort(); //CanRecharge
                packet.ReadUInt(); //MeterRateTime
            }
            else if (rentType == 3)
            {
                packet.ReadUShort(); //CanDelete
                packet.ReadUShort(); //CanRecharge
                packet.ReadUInt(); //PeriodBeginTime
                packet.ReadUInt(); //PeriodEndTime
                packet.ReadUInt(); //PackingTime
            }

            RefItemId = packet.ReadUInt();


            //var item = new RefObjItem(RefItemID); //TODO: Add reference manager
            var item = Globals.RefObjCommon[RefItemId];
            //  this.MaxStack = item.MaxStack;

            //   Console.WriteLine($"Slot: {this.Slot} | ItemID: {this.RefItemID}");
            if (item.TypeID1 == 3)
            {
                //ITEM_
                if (item.TypeID2 == 1)
                {
                    //ITEM_CH
                    //ITEM_EU
                    //AVATAR_
                    OptLevel = packet.ReadByte();
                    packet.ReadULong(); //Variance
                    packet.ReadUInt(); //Data
                    var magParamNum = packet.ReadByte();
                    for (var i = 0; i < magParamNum; i++)
                    {
                        packet.ReadULong(); //MagParamPair
                    }

                    for (var i = 0; i < 2; i++)
                    {
                        packet.ReadByte(); //bindingOptionType
                        var bindingOptionCount = packet.ReadByte();
                        for (var bindingOptionIndex = 0; bindingOptionIndex < bindingOptionCount; bindingOptionIndex++)
                        {
                            packet.ReadByte(); //Slot
                            packet.ReadUInt(); //ID
                            packet.ReadUInt(); //nParam1 or OptValue depending on Type
                        }
                    }
                }
                else if (item.TypeID2 == 2)
                {
                    //ITEM_COS
                    if (item.TypeID3 == 1)
                    {
                        var state = packet.ReadByte();
                        if (state == 2 || state == 3 || state == 4)
                        {
                            packet.ReadUInt(); //Model
                            packet.ReadAscii(); //PetName
                            if (item.TypeID4 == 2)
                            {
                                //ITEM_COS_P (Ability)
                                packet.ReadUInt();

                            }

                            var hasInventoryExt = packet.ReadBool();

                            if (hasInventoryExt)
                            {
                                //  packet.ReadDateTime();
                                packet.ReadUInt();
                                packet.ReadUInt();
                                packet.ReadUInt();
                                packet.ReadUShort();
                            }
                        }


                        //TODO: @Cherno: Write some stuff so we can log from wFilterLib
                        //if (unkByte0 != 0)
                        //    g.Log.Write("CharacterDataHandler: unkByte1 != 0 (Value: {0})", unkByte0);
                    }
                    else if (item.TypeID3 == 2)
                    {
                        //ITEM_ETC_TRANS_MONSTER
                        packet.ReadUInt(); //RefObjID
                    }
                    else if (item.TypeID3 == 3)
                    {
                        //MAGIC_CUBE
                        packet.ReadUInt(); //Quantity
                    }
                }
                else if (item.TypeID2 == 3)
                {
                    //ITEM_ETC_
                    StackCount = packet.ReadUShort(); //StackCount

                    if (item.TypeID3 == 11)
                    {
                        //ITEM_ETC_ARCHEMY
                        if (item.TypeID4 == 1 || item.TypeID4 == 2)
                        {
                            //MAGICSTONE, ATTRSTONE
                            packet.ReadByte();
                        }
                    }
                    else if (item.TypeID3 == 14 && item.TypeID4 == 2)
                    {
                        //ITEM_MALL_GACHA_CARD_WIN
                        //ITEM_MALL_GACHA_CARD_LOSE
                        var magParamCount = packet.ReadByte();
                        for (var i = 0; i < magParamCount; i++)
                        {
                            packet.ReadULong(); //magParamPair
                        }
                    }
                }
            }
        }
        catch
        {
            // Logger.Error($"[InventoryItem CharData parse]Cannot Read ItemID[{RefItemId}] Slot[{Slot}]");
        }
    }
}
