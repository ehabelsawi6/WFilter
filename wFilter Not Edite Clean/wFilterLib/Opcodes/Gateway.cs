namespace wFilterLib.Opcodes;

public struct Gateway
{
    public enum Request : ushort
    {
        CHECKVERSION = 0x6000,
        PATCH = 0x6100,
        NEWS = 0x6104,
        SERVERLIST = 0x6101,
        SERVERLIST_PING = 0x6106,
        LOGIN = 0x6102,
        LOGIN_IBUV = 0x6323,
        LOGIN_IBUV_CHALLENGE = 0x2322,
    }

    public enum Response : ushort
    {
        CHECKVERSION = 0x6000,
        PATCH = 0xA100,
        SERVERLIST = 0xA101,
        SERVERLIST_PING = 0xA106,
        LOGIN = 0xA102,
        LOGIN_IBUV_CONFIRM = 0xA323,
        LOGIN_IBUV_CHALLENGE = 0x2322,
        NEWS = 0xA104,
    }
}
