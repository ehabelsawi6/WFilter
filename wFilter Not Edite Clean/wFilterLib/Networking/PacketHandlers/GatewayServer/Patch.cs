using wFilterLib.Networking.Session;
using wFilterLib.Networking.PacketHandlers.GatewayServer.PacketStructure;
using wFilterLib.Networking.PacketStuff;
using wFilterLib.SSA;

namespace wFilterLib.Networking.PacketHandlers.GatewayServer;

public class Patch /*: IPacketHandler*/
{
    public static PacketResult HandleAck(Packet packet, PlayerSession session)
    {
        var patchResponse = new PatchResponse();
        patchResponse.ReadPacket(packet);

        if (patchResponse.PatchResult != 0x02 || patchResponse.PatchErrorCode != PatchErrorCode.Update)
            return new PacketResult(patchResponse.WritePacket(), PacketResultType.Override);


        //Download server redirect
        patchResponse.DownloadServerIp = Configs.Config.GetModules.PublicIp;
        patchResponse.DownloadServerPort = Configs.Config.GetModules.DownloadServer.PublicPort;


        return new PacketResult(patchResponse.WritePacket(), PacketResultType.Override);
    }

    public static PacketResult HandleReq(Packet packet, PlayerSession session)
    {
        session.PatchSent = true;

        return new PacketResult(PacketResultType.Nothing);
    }
}
