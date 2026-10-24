using wFilterLib.Networking.Session.Classes;
using wFilterLib.SSA;

namespace wFilterLib.Database.Models;

/// <summary>
/// S->C SERVER_AGENT_MOVEMENT_RESPONSE = 0xB021
/// TESTME
/// </summary>
public class MovementResponseEntity
{
    public uint TargetID { get; set; }
    public bool HasDestination { get; set; }
    public GamePosition DestPos { get; set; }
    public bool HasSource { get; set; }
    public bool IsDungeon { get; set; }
    public GamePosition SrcPos { get; set; }
    public MovementAngleAction AngleAction { get; set; }
    public ushort Angle { get; set; }

    #region Logic

    public bool ReadFromPacket(Packet packet)
    {
        try
        {
            TargetID = packet.ReadUInt();
            HasDestination = packet.ReadBool();


            if (HasDestination)
            {
                //Has destination
                DestPos = new GamePosition();
                DestPos.ReadFromPacket(packet);
            }
            else
            {
                //No destination
                AngleAction = (MovementAngleAction)packet.ReadByte();
                Angle = packet.ReadUShort();
            }

            /*HasSource = packet.ReadBool();

            if (HasSource)
            {
                var regionId = packet.ReadInt16();

                float x, y, z;
                if (regionId < short.MaxValue)
                {
                    //Normal world
                    x = packet.ReadInt16();
                    y = packet.ReadInt16();
                    z = packet.ReadInt16();
                }
                else
                {
                    //Dungeon
                    IsDungeon = true;
                    x = packet.ReadInt32();
                    y = packet.ReadInt32();
                    z = packet.ReadInt32();
                }

                SrcPos = new GamePosition(regionId, x, y, z);
            }*/

            return true;
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            return false;
            // throw;
        }
    }
    #endregion

}
