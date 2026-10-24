using wFilterLib.SSA;
using wFilterLib.Opcodes;

namespace wFilterLib.Networking.PacketHandlers.GatewayServer.PacketStructure
{
    public class PathFile
    {
        public uint FileId { get; set; }
        public string FileName { get; set; }
        public string FilePath { get; set; }
        public uint FileLength { get; set; }
        public bool FileToBePacked { get; set; }
    }

    /// <summary>
    /// 0xA100 - SERVER_GATEWAY_PATCH_RESPONSE
    /// Massive
    /// </summary>
    public sealed class PatchResponse
    {
        public byte PatchResult { get; set; }
        public PatchErrorCode PatchErrorCode { get; set; }

        public string DownloadServerIp { get; set; }
        public ushort DownloadServerPort { get; set; }
        public uint DownloadServerVersion { get; set; }

        public bool HasEntries { get; set; }

        public List<PathFile> PathFiles = new();

        /// <summary>
        /// ReadPacket
        /// </summary>
        /// <param name="packet"></param>
        public void ReadPacket(Packet packet)
        {
            PatchResult = packet.ReadByte();
            if (PatchResult != 0x02) return;

            PatchErrorCode = (PatchErrorCode)packet.ReadByte();
            if (PatchErrorCode != PatchErrorCode.Update) return;

            DownloadServerIp = packet.ReadAscii();
            DownloadServerPort = packet.ReadUShort();
            DownloadServerVersion = packet.ReadUInt();

            while (true)
            {
                HasEntries = packet.ReadBool();
                if (!HasEntries)
                    break;

                var pathFile = new PathFile();
                pathFile.FileId = packet.ReadUInt();
                pathFile.FileName = packet.ReadAscii();
                pathFile.FilePath = packet.ReadAscii();
                pathFile.FileLength = packet.ReadUInt();
                pathFile.FileToBePacked = packet.ReadBool();
                PathFiles.Add(pathFile);
            }
        }

        /// <summary>
        /// WritePacket
        /// </summary>
        /// <returns>Packet</returns>
        public Packet WritePacket()
        {
            var packet = new Packet((ushort)Gateway.Response.PATCH, false, true);

            packet.WriteByte(PatchResult);

            if (PatchResult != 0x02) return packet;

            packet.WriteByte((byte)PatchErrorCode);

            if (PatchErrorCode != PatchErrorCode.Update) return packet;

            packet.WriteAscii(DownloadServerIp);
            packet.WriteUShort(DownloadServerPort);
            packet.WriteUInt(DownloadServerVersion);

            foreach (var file in PathFiles)
            {
                packet.WriteBool(true);
                packet.WriteUInt(file.FileId);
                packet.WriteAscii(file.FileName);
                packet.WriteAscii(file.FilePath);
                packet.WriteUInt(file.FileLength);
                packet.WriteBool(file.FileToBePacked);
            }

            packet.WriteBool(false);

            return packet;
        }
    }


    public enum PatchErrorCode : byte
    {
        /// <summary>
        /// UILM_MSG_DETECTED_ABNORMAL_MODULE
        /// <para>Invalid client. Program will be terminated.</para>
        /// </summary>
        InvalidVersion = 1,

        /// <summary>
        /// BSObj Plugin: can't create file transfer manager! Maybe pack file corrupted or someone is already accessing it now... try a few minutes later"
        /// </summary>
        Update = 2,

        /// <summary>
        /// UILM_MSG_GATEWAY_NOT_IN_SERVICE
        /// <para>The server is undergoing inspection or updates. Connect to %swww.silkroadonline.net for more information.</para>
        /// </summary>
        NotInService = 4,

        /// <summary>
        /// UILM_MSG_DETECTED_ABNORMAL_MODULE
        /// <para>Invalid client. Program will be terminated.</para>
        /// </summary>
        AbnormalModule = 3,

        /// <summary>
        /// UILM_MSG_DETECTED_PATCH_DIABLE
        /// <para>You have to install the full version. Move to official website to dowload the full version?</para>
        /// </summary>
        PatchDisabled = 5,
    }
}
