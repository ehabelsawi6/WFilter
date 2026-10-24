namespace wFilterLib.Opcodes;

public struct Custom
{
    public enum Request : ushort
    {
        Hwid = 0x8892,
        Customs = 0x1337,

        PLAYERINFO = 0x3560,
        GUI_GRANTNAME = 0x3501,
        GUI_CUSTOMTITLE = 0x1202,
        GUI_REQUEST_TITLEINFO = 0x1200,
        GUI_APPLYTITLE = 0x1201,
    }

    public enum Response : ushort
    {
        Customs = 0x1338,

        GUI_SETTINGS = 0x5114,
        GUI_CUSTOMTITLEUPDATE = 0x5106,
        GUI_CUSTOMTITLESINFO = 0x5105,
        GUI_REMOVECUSTOMTITLE = 0x5107,
        GUI_SWITCHTITLEINFO = 0x5104,
        GUI_UPDATE_TITLECOLOR = 0x5109,
        GUI_UPDATE_TITLECOLOR_INFO = 0x5108,
    }
    public enum Framework : ushort
    {
        MAIN = 0x3500,
        DPSMeter = 0x5010,
    }
}
