namespace wFilterLib.Networking.PacketStuff;

public enum PacketResultType
{
    Disconnect,
    Override,
    Block,
    Nothing
}

public enum ServerType
{
    Download,
    Gateway,
    Agent
}

public enum PacketMode
{
    Client,
    Server
}
