using wFilterLib;
using wFilterLib.Database.Models;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
        public static PacketResult CosInfoResponse(Packet packet, PlayerSession session)
        {
            var uid = packet.ReadUInt(); //Unique ID
            var refId = packet.ReadUInt(); //Model ID, can skip since the spawn packet comes first.

            RefObjCommon obj = null;
            if (Globals.RefObjCommon.ContainsKey(refId))
            {
                obj = Globals.RefObjCommon[refId];
            }

            packet.ReadUInt(); // MaxHP?
            packet.ReadUInt(); // MaxHP?

            //if (obj.TypeID4 == 1) //Normal COS
            //{
            //    OUT_REMOTE[i].ReadUInt8(); // UNK ?? something with spawned pet count
            //}
            //else if (obj.TypeID4 == 2) //Job COS
            //{
            //    OUT_REMOTE[i].ReadUInt8(); //Max transport slots
            //    byte currCount = OUT_REMOTE[i].ReadUInt8(); //Current transport items
            //    for (int q = 0; q < currCount; q++)
            //        ParseItem(OUT_REMOTE[i]);
            //    OUT_REMOTE[i].ReadUInt32(); //Owner Unique ID
            //}
            if (obj != null)
            {
                if (obj.TypeID4 == 3) //Attack COS
                {
                    packet.ReadInt64(); //Pet EXP
                    packet.ReadByte(); //Level?
                    packet.ReadUShort(); //HGP Points
                    packet.ReadUInt(); //??
                    packet.ReadAscii();
                    packet.ReadByte(); //??
                    var Owned_unique_id = packet.ReadUInt(); //Owned unique id
                    packet.ReadByte(); // UNK ?? something with spawned pet count
                    //Logger.Warn($"COS Name:{petname}, Owned_unique_id:{Owned_unique_id:X} cur id:{UNIQUE_ID} refID:{refID}");
                    if (Owned_unique_id == session.State.UniqueId)
                    {
                        session.State.FellowPetId = uid;
                    }
                }
            }
            else
                session.State.FellowPetId = 0;
            //else if (obj.TypeID4 == 4) //Pickup COS
            //{
            //    OUT_REMOTE[i].ReadUInt32(); //Pet settings in binary
            //    OUT_REMOTE[i].ReadAscii(); //COS Name
            //    OUT_REMOTE[i].ReadUInt8(); //COS inventory size
            //    byte currCount = OUT_REMOTE[i].ReadUInt8();
            //    for (int w = 0; w < currCount; w++)
            //    {
            //        ParseItem(OUT_REMOTE[i]);
            //    }
            //    OUT_REMOTE[i].ReadUInt32(); //Owner unique id
            //    OUT_REMOTE[i].ReadUInt8(); // UNK ?? something with spawned pet count
            //} 


            return new PacketResult(PacketResultType.Nothing);
        }

        public static PacketResult CosDismountResponse(Packet packet, PlayerSession session)
        {
            if (packet.GetBytes().Length >= 4)
            {
                var Dismounted_Pet_UniqueID = packet.ReadUInt();
                if (session.State.FellowPetId == Dismounted_Pet_UniqueID)
                    session.State.FellowPetId = 0;
            }

            return new PacketResult(PacketResultType.Nothing);
        }
    }
}
