using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wFilterLib.Networking.PacketHandlers.GatewayServer;

public class CaptchaChallenge
{
    public static PacketResult HandleAck(Packet packet, PlayerSession session)
    {
        if (Config.GetLogin.CaptchaCode.Length <= 0)
            return new PacketResult(PacketResultType.Nothing);

        var captchaReq = new Packet((ushort)Opcodes.Gateway.Request.LOGIN_IBUV);
        captchaReq.WriteAscii(Config.GetLogin.CaptchaCode);

        session.SendPacketToServer(captchaReq);

        return new PacketResult(PacketResultType.Block);


    }

    public PacketResult HandleReq(Packet packet, PlayerSession session)
    {
        throw new NotImplementedException();
    }
}
