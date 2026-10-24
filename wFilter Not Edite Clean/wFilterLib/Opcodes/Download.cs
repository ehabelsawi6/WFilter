namespace wFilterLib.Opcodes;

public struct Download
{
    public enum Request : ushort
    {
        FILE_REQUEST = 0x6004,

    }

    public enum Response : ushort
    {
        FILE_CHUNK = 0x1001,
        FILE_COMPLETE = 0xA004,
    }
}
