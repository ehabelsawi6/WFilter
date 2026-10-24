using wFilterLib;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;
using wFilterLib.Database.Models;

namespace wkFilter.NetworkStuff.PacketHandler.Agent
{
    public partial class AgentHandler
    {
        private static readonly object _lock = new();

        public static PacketResult GameNotifyResponse(Packet packet, PlayerSession session)
        {

            lock (_lock)
            {
                var operationType = packet.ReadUInt16();
                if (operationType is 0x0C05 or 0x0C06)
                {
                    var refObjId = packet.ReadUInt32();
                    if (refObjId > 0)
                    {
                        var killerName = "";
                        if (operationType == 0x0C06)
                            killerName = " - Killed by " + packet.ReadAscii();

                        var isFound = false;
                        foreach (var data in Globals.UniquesData.Where(data => data.RefObjId == refObjId))
                        {
                            isFound = true;
                            data.Time = DateTime.Now;
                            data.State = operationType == 0x0C05;
                            data.KillerName = killerName;
                        }

                        if (!isFound)
                        {
                            var data = new UniqueNotifyData();
                            data.State = operationType == 0x0C05;
                            data.Time = DateTime.Now;
                            data.KillerName = killerName;
                            data.RefObjId = refObjId;
                            Globals.UniquesData.Add(data);
                        }
                    }
                }
            }

            return new PacketResult(PacketResultType.Nothing);
        }
    }
}
