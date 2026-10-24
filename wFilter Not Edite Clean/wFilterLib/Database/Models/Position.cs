using wFilterLib.SSA;

namespace wFilterLib.Database.Models;

public struct Position
{
    private int _regionId;
    public int RegionId
    {
        get => _regionId;
        set => _regionId = value;
    }


    private float _x;
    public float X
    {
        get => _x;
        set => _x = value;
    }

    private float _y;
    public float Y
    {
        get => _y;
        set => _y = value;
    }
    private float _z;
    public float Z
    {
        get => _z;
        set => _z = value;
    }

    private ushort _angle;
    public ushort Angle
    {
        get => _angle;
        set => _angle = value;
    }


    public byte XSec
    {
        get => Convert.ToByte(_regionId >> 0 & 0xFF);
        set => _regionId = (ushort)(_regionId & ~(0xFF << 0) | (value & 0xFF) << 0);
    }
    public byte YSec
    {
        get => Convert.ToByte(_regionId >> 8 & 0xFF);
        set => _regionId = (ushort)(_regionId & ~(0xFF << 8) | (value & 0xFF) << 8);
    }


    public Position(Packet packet)
    {
        _regionId = packet.ReadInt16();
        _x = packet.ReadSingle();
        _y = packet.ReadSingle();
        _z = packet.ReadSingle();
        _angle = packet.ReadUShort();
    }

    //TODO: operators
    //TODO: equal shit
    //TODO: distance to
}
