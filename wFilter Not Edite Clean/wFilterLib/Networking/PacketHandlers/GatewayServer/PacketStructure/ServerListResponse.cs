using wFilterLib.SSA;

namespace wFilterLib.Networking.PacketHandlers.GatewayServer.PacketStructure;

public class Farm
{
    public byte Id { get; set; }
    public string Name { get; set; }
}

public class Shard
{
    public ushort Id { get; set; }
    public string Name { get; set; }
    public ushort OnlineCount { get; set; }
    public ushort Capacity { get; set; }
    public bool IsOperating { get; set; }
    public byte FarmId { get; set; }
}

/// <summary>
/// 0xA101 - SERVER_GATEWAY_SHARD_LIST_RESPONSE
/// </summary>
public sealed class ServerListResponse
{

    public List<Farm> Farms = new();
    public List<Shard> Shards = new();


    /// <summary>
    /// ReadPacket
    /// </summary>
    /// <param name="packet"></param>
    public void ReadPacket(Packet packet)
    {
        while (true)
        {
            var hasEntries = packet.ReadBool();
            if (!hasEntries)
                break;

            var farm = new Farm();
            farm.Id = packet.ReadByte();
            farm.Name = packet.ReadAscii();

            Farms.Add(farm);
        }

        while (true)
        {
            var hasEntries = packet.ReadBool();
            if (!hasEntries)
                break;

            var shard = new Shard();
            shard.Id = packet.ReadUShort();
            shard.Name = packet.ReadAscii();
            shard.OnlineCount = packet.ReadUShort();
            shard.Capacity = packet.ReadUShort();
            shard.IsOperating = packet.ReadBool();
            shard.FarmId = packet.ReadByte();

            Shards.Add(shard);
        }
    }

    /// <summary>
    /// WritePacket
    /// </summary>
    /// <returns>Packet</returns>
    public Packet WritePacket()
    {
        var packet = new Packet((ushort)Opcodes.Gateway.Response.SERVERLIST);
        foreach (var farm in Farms)
        {
            packet.WriteBool(true);
            packet.WriteByte(farm.Id);
            packet.WriteAscii(farm.Name);
        }
        packet.WriteBool(false);

        foreach (var shard in Shards)
        {
            packet.WriteBool(true);
            packet.WriteUShort(shard.Id);
            packet.WriteAscii(shard.Name);
            packet.WriteUShort(shard.OnlineCount);
            packet.WriteUShort(shard.Capacity);
            packet.WriteBool(shard.IsOperating);
            packet.WriteByte(shard.FarmId);
        }
        packet.WriteBool(false);

        return packet;
    }

}
