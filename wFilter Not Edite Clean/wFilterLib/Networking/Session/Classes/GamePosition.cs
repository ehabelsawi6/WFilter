using wFilterLib.SSA;

namespace wFilterLib.Networking.Session.Classes;

public class GamePosition
{
    //--------------------------------------------------------------------------

    #region Public properties

    public int RegionID { get; set; }

    public float X { get; set; }

    /// <summary>
    /// Height.
    /// </summary>
    public float Y { get; set; }

    public float Z { get; set; }

    public int Angle { get; set; }

    #endregion

    //--------------------------------------------------------------------------

    #region Constructors

    public GamePosition(int regionId, float x, float y, float z)
    {
        RegionID = regionId;
        X = x;
        Y = y;
        Z = z;
    }

    public GamePosition()
    {

    }

    #endregion

    //--------------------------------------------------------------------------

    #region Logic

    public bool ReadFromPacket(Packet packet)
    {
        try
        {
            RegionID = packet.ReadInt16();

            float x, y, z;

            if (RegionID < short.MaxValue)
            {
                //Normal world
                x = packet.ReadInt16();
                y = packet.ReadInt16();
                z = packet.ReadInt16();
            }
            else
            {
                //Dungeon
                x = packet.ReadInt32();
                y = packet.ReadInt32();
                z = packet.ReadInt32();
            }

            X = x;
            Y = y;
            Z = z;
        }
        catch (Exception e)
        {
            Console.WriteLine(e);

        }

        return true;
    }
    #endregion

    //--------------------------------------------------------------------------
}
public enum MovementAngleAction : byte
{
    Obsolete = 0,
    Forward = 1,
}
