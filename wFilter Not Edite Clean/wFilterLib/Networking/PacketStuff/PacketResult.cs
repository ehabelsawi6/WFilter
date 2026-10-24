using wFilterLib.SSA;

namespace wFilterLib.Networking.PacketStuff;

public readonly struct PacketResult
{
    private readonly List<Packet> _packets;
    public readonly PacketResultType PacketResultType;
    public readonly string? DisconnectReason = "";

    public int PacketCount => PacketResultType == PacketResultType.Override ? _packets.Count : 0;

    public PacketResult(Packet packet, PacketResultType packetResultType = PacketResultType.Nothing)
    {
        _packets = null;
        if (packetResultType == PacketResultType.Override)
            _packets = new List<Packet> { packet };

        PacketResultType = packetResultType;
    }

    public PacketResult(PacketResultType packetResultType = PacketResultType.Nothing)
    {
        _packets = null;
        if (packetResultType == PacketResultType.Override)
            _packets = new List<Packet>();

        PacketResultType = packetResultType;
    }

    public PacketResult(PacketResultType packetResultType = PacketResultType.Disconnect, string? disconnectReason = "")
    {
        _packets = null;
        if (packetResultType == PacketResultType.Override)
            _packets = new List<Packet>();

        PacketResultType = packetResultType;
        DisconnectReason = disconnectReason;
    }

    public Packet this[int index] => _packets[index];
}
