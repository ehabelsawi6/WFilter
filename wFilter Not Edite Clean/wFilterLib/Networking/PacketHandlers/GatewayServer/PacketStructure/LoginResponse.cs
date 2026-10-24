using wFilterLib.SSA;

namespace wFilterLib.Networking.PacketHandlers.GatewayServer.PacketStructure;

public sealed class AgentServer
{
    public uint Token { get; set; }
    public string Ip { get; set; }
    public ushort Port { get; set; }
}

public sealed class Punishment
{
    public string Reason { get; set; }
    public DateTime DateTime { get; set; }
}

/// <summary>
/// 0xA102 - SERVER_GATEWAY_LOGIN_RESPONSE
/// </summary>
public sealed class LoginResponse
{
    public byte Result { get; set; }

    public AgentServer AgentServer = new();

    public LoginErrorCode LoginErrorCode { get; set; }
    public uint MaxAttempts { get; set; }
    public uint CurAttempts { get; set; }

    public LoginBlockType BlockType { get; set; }
    public Punishment Punishment = new();

    /// <summary>
    /// ReadPacket
    /// </summary>
    /// <param name="packet"></param>
    public void ReadPacket(Packet packet)
    {
        Result = packet.ReadByte();
        if (Result == 0x01)
        {
            AgentServer.Token = packet.ReadUInt();
            AgentServer.Ip = packet.ReadAscii();
            AgentServer.Port = packet.ReadUShort();
        }
        else if (Result == 0x02)
        {
            LoginErrorCode = (LoginErrorCode)packet.ReadByte();
            switch (LoginErrorCode)
            {
                case LoginErrorCode.InvalidCredentials:
                    MaxAttempts = packet.ReadUInt();
                    CurAttempts = packet.ReadUInt();
                    break;
                case LoginErrorCode.Blocked:
                    if (BlockType == LoginBlockType.Punishment)
                    {
                        Punishment.Reason = packet.ReadAscii();
                        Punishment.DateTime = packet.ReadDateTime();
                    }
                    break;
                case LoginErrorCode.AlreadyConnected:
                    break;
                case LoginErrorCode.ServerIsFull:
                    break;
                case LoginErrorCode.IpLimit:
                    break;
                case LoginErrorCode.UiioClientStartContentFailBillingFailed:
                    break;
                case LoginErrorCode.UiioClientStartContentFailBillingRelated:
                    break;
                case LoginErrorCode.UiioSmerrAdultOnlyServer:
                    break;
                case LoginErrorCode.UiioSmerrTeenoverOnlyServer:
                    break;
                case LoginErrorCode.UittTeenserverErrmgsAdult:
                    break;
            }
        }
    }

    /// <summary>
    /// WritePacket
    /// </summary>
    /// <returns>Packet</returns>
    public Packet WritePacket()
    {
        var packet = new Packet((ushort)Opcodes.Gateway.Response.LOGIN);
        packet.WriteByte(Result);
        if (Result == 0x01)
        {
            packet.WriteUInt(AgentServer.Token);
            packet.WriteAscii(AgentServer.Ip);
            packet.WriteUShort(AgentServer.Port);
        }
        else if (Result == 0x02)
        {
            packet.WriteByte((byte)LoginErrorCode);

            switch (LoginErrorCode)
            {
                case LoginErrorCode.InvalidCredentials:
                    packet.WriteUInt(MaxAttempts);
                    packet.WriteUInt(CurAttempts);
                    break;
                case LoginErrorCode.Blocked:
                    packet.WriteByte((byte)BlockType);
                    if (BlockType == LoginBlockType.Punishment)
                    {
                        packet.WriteAscii(Punishment.Reason);
                        packet.WriteDateTime(Punishment.DateTime);
                    }
                    break;
                case LoginErrorCode.AlreadyConnected:
                    break;
                case LoginErrorCode.ServerIsFull:
                    break;
                case LoginErrorCode.IpLimit:
                    break;
                case LoginErrorCode.UiioClientStartContentFailBillingFailed:
                    break;
                case LoginErrorCode.UiioClientStartContentFailBillingRelated:
                    break;
                case LoginErrorCode.UiioSmerrAdultOnlyServer:
                    break;
                case LoginErrorCode.UiioSmerrTeenoverOnlyServer:
                    break;
                case LoginErrorCode.UittTeenserverErrmgsAdult:
                    break;
            }
        }

        return packet;
    }
}

public enum LoginErrorCode
{
    /// <summary>
    /// <para>UIIT_STT_GLOBAL_PASSWORD_INPUT_ERROR</para>
    /// Password entry has failed %d out of %d times.
    /// </summary>
    InvalidCredentials = 1,

    /// <summary>
    /// Depends on subtype <see cref="LoginBlockType"/>
    /// </summary>
    Blocked = 2,

    /// <summary>
    /// <para>UIO_MSG_ERROR_OVERLAP</para>
    /// This user is already connected. The user may still be connected because of an error that forced the game to close. Please try again in 5 minutes.
    /// </summary>
    AlreadyConnected = 4,
    /// <summary>
    /// <para>UIO_MSG_ERROR_SERVER_BUSY_CONNECT_IMPOSSIBILE</para>
    /// The server is full, please try again later.
    /// </summary>
    ServerIsFull = 6,

    /// <summary>
    /// Cannot connect to the server because access to the current IP has exceeded its limit.
    /// </summary>
    IpLimit = 0xB,

    /// <summary>
    /// <para>TRANSLATION MISSING</para>
    /// 사용기간이 만료되어 서버에 접속할 수 없습니다. (This period has expired, you can not connect to the server.)
    /// </summary>
    UiioClientStartContentFailBillingFailed = 0xC,

    /// <summary>
    /// Billing server error occurred.
    /// </summary>
    UiioClientStartContentFailBillingRelated = 0xD,

    /// <summary>
    /// Only adults over the age of 18 are allowed to connect to the server.
    /// </summary>
    UiioSmerrAdultOnlyServer = 0xE,

    /// <summary>
    /// Only users over the age of 12 are allowed to connect to the server.
    /// </summary>
    UiioSmerrTeenoverOnlyServer = 0xF,

    /// <summary>
    /// Adults over the age of 18 are not allowed to connect to the Teen server.
    /// </summary>
    UittTeenserverErrmgsAdult = 0x10,
}

public enum LoginBlockType
{
    /// <summary>
    /// <para>UIO_MSG_ERROR_ACCOUNT_STOP</para>
    /// This account has been blocked according to the Terms of Service and cannot be accessed to play the game.
    /// Blocking reason:
    /// Completion time:
    /// </summary>
    Punishment = 1,

    /// <summary>
    /// <para>UIO_MSG_ERROR_ACCOUNT_CONNECT_IMPOSSIBILE</para>
    /// Cannot connect to the server because the server is now in inspection.
    /// </summary>
    AccountInspection = 2,

    /// <summary>
    /// <para>UIO_MSG_ERROR_THERE_IS_NO_ACCOUNT_INFO</para>
    /// ID is found, but the needed details are not found.\nFill in the needed information at Silkroad homepage to connect to the game.
    /// <para>SimpleMessageBox -> opens website</para>
    /// </summary>
    NoAccountInfo = 3,

    /// <summary>
    /// <para>UIO_MSG_ERROR_GRATIS_USER_BLOCKED</para>
    /// Cannot connect because the free service is over.
    /// </summary>
    FreeServiceOver = 4,
}