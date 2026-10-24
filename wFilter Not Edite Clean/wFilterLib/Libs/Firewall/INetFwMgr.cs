using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x0200000E RID: 14
    [Guid("F7898AF5-CAC4-4632-A2EC-DA06E5111AF2"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwMgr
    {
        // Token: 0x17000018 RID: 24
        [DispId(1)]
        INetFwPolicy LocalPolicy
        {
            // Token: 0x060000E3 RID: 227
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x17000019 RID: 25
        [DispId(2)]
        NetFwProfileType CurrentProfileType
        {
            // Token: 0x060000E4 RID: 228
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x060000E5 RID: 229
        [DispId(3)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void RestoreDefaults();

        // Token: 0x060000E6 RID: 230
        [DispId(4)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void IsPortAllowed([MarshalAs(UnmanagedType.BStr)][In] string imageFileName, [In] NetFwIpVersion ipVersion, [In] int portNumber, [MarshalAs(UnmanagedType.BStr)][In] string localAddress, [In] NetFwIpProtocol ipProtocol, [MarshalAs(UnmanagedType.Struct)] out object allowed, [MarshalAs(UnmanagedType.Struct)] out object restricted);

        // Token: 0x060000E7 RID: 231
        [DispId(5)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void IsIcmpTypeAllowed([In] NetFwIpVersion ipVersion, [MarshalAs(UnmanagedType.BStr)][In] string localAddress, [In] byte type, [MarshalAs(UnmanagedType.Struct)] out object allowed, [MarshalAs(UnmanagedType.Struct)] out object restricted);
    }
}
