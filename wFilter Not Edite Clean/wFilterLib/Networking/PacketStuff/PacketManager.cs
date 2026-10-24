using System.Collections;
using wFilterLib.Configs;
using wFilterLib.Networking.Session;
using wFilterLib.Opcodes;
using wFilterLib.SSA;

namespace wFilterLib.Networking.PacketStuff;

public delegate PacketResult PacketHandler(Packet packet, PlayerSession? session);

public class PacketManager
{
    private ServerType ServerType { get; set; }

    private readonly Hashtable _clientHandlers = new();
    private readonly Hashtable _serverHandlers = new();


    public PacketManager(ServerType serverType)
    {
        ServerType = serverType;
    }

    public void RegisterHandler(PacketMode packetMode, ushort opcode, PacketHandler session)
    {
        if (packetMode == PacketMode.Client)
            _clientHandlers.Add(opcode, session);
        else
            _serverHandlers.Add(opcode, session);
    }

    public PacketResult HandlePacket(PacketMode packetMode, Packet packet, PlayerSession? session)
    {
        if (packetMode == PacketMode.Client)
        {
            if (packet.Opcode == (ushort)Global.Request.MODULE_KEEP_ALIVE && packet.Length > 0)
            {
                //ToDo Log/output message
                return new PacketResult(PacketResultType.Block);
            }

            if (ServerType == ServerType.Download && Enum.IsDefined(typeof(Download.Request), packet.Opcode) || packet.Opcode == (ushort)Global.Request.MODULE_KEEP_ALIVE)
            {
                var cHandler = _clientHandlers[packet.Opcode] as PacketHandler;
                return cHandler?.Invoke(packet, session) ?? new PacketResult(PacketResultType.Nothing);
            }

            else if (ServerType == ServerType.Gateway && Enum.IsDefined(typeof(Gateway.Request), packet.Opcode)
                || Enum.IsDefined(typeof(Custom.Request), packet.Opcode) || packet.Opcode == (ushort)Global.Request.MODULE_KEEP_ALIVE)
            {
                var cHandler = _clientHandlers[packet.Opcode] as PacketHandler;
                return cHandler?.Invoke(packet, session) ?? new PacketResult(PacketResultType.Nothing);
            }

            else if (ServerType == ServerType.Agent && Enum.IsDefined(typeof(Agent.Request), packet.Opcode)
                || Enum.IsDefined(typeof(Custom.Request), packet.Opcode) || packet.Opcode == (ushort)Global.Request.MODULE_KEEP_ALIVE)
            {
                var cHandler = _clientHandlers[packet.Opcode] as PacketHandler;
                return cHandler?.Invoke(packet, session) ?? new PacketResult(PacketResultType.Nothing);
            }
            else if (Config.GetExtra.ExtraOpcodesWhiteList.Contains(packet.Opcode))
            {
                return new PacketResult(PacketResultType.Nothing);
            }
            else if (packet.Opcode == 0x2113 || packet.Opcode == 0x9000 || packet.Opcode == 0x9001) return new PacketResult(PacketResultType.Block); // xtrap shit

            else
            {
              //  Globals.Logger.Warn($"[{session.State.Ip}] has sent a wrong packet with opcode [{packet.HexOpcode}]\nif you think this is a mistake you can add it to whitelist in config/extra.json (on your own risk)");
                //ToDo Log/output message
                return new PacketResult(PacketResultType.Block);
            }



        }

        var sHandler = _serverHandlers[packet.Opcode] as PacketHandler;
        return sHandler?.Invoke(packet, session) ?? new PacketResult(PacketResultType.Nothing);
    }
}
