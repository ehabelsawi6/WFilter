using wFilterLib.Networking.PacketHandlers.GatewayServer;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.Opcodes;

namespace wFilterLib.Networking.PacketHandlers;

public static class RegisterGatewayHandlers
{
    public static void Setup(PacketManager packetManager)
    {
        // PacketManager packetManager = new(ServerType.Gateway);

        //Server -> Client handlers
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Gateway.Response.PATCH, Patch.HandleAck);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Gateway.Response.SERVERLIST, ServerList.HandleAck);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Gateway.Response.LOGIN_IBUV_CHALLENGE, CaptchaChallenge.HandleAck);
        packetManager.RegisterHandler(PacketMode.Server, (ushort)Gateway.Response.LOGIN, Login.HandleAck);


        //Client -> Server handlers
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Gateway.Request.PATCH, Patch.HandleReq);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Gateway.Request.SERVERLIST, ServerList.HandleReq);
        packetManager.RegisterHandler(PacketMode.Client, (ushort)Gateway.Request.LOGIN, Login.HandleReq);



        //custom


    }
}
