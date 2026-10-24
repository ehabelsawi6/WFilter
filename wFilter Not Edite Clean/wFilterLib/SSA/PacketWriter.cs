namespace wFilterLib.SSA
{
    internal class PacketWriter : BinaryWriter
    {
        MemoryStream m_ms;

        public PacketWriter()
        {
            m_ms = new MemoryStream();
            OutStream = m_ms;
        }

        public byte[] GetBytes()
        {
            return m_ms.ToArray();
        }
    }
}
