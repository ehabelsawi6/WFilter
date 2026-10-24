using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x0200000B RID: 11
    [Guid("B5E64FFA-C2C5-444E-A301-FB5E00018050"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwAuthorizedApplication
    {
        // Token: 0x17000007 RID: 7
        [DispId(1)]
        string Name
        {
            // Token: 0x060000BE RID: 190
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060000BF RID: 191
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000008 RID: 8
        [DispId(2)]
        string ProcessImageFileName
        {
            // Token: 0x060000C0 RID: 192
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060000C1 RID: 193
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000009 RID: 9
        [DispId(3)]
        NetFwIpVersion IpVersion
        {
            // Token: 0x060000C2 RID: 194
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000C3 RID: 195
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700000A RID: 10
        [DispId(4)]
        NetFwScope Scope
        {
            // Token: 0x060000C4 RID: 196
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000C5 RID: 197
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700000B RID: 11
        [DispId(5)]
        string RemoteAddresses
        {
            // Token: 0x060000C6 RID: 198
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060000C7 RID: 199
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700000C RID: 12
        [DispId(6)]
        bool Enabled
        {
            // Token: 0x060000C8 RID: 200
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000C9 RID: 201
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
