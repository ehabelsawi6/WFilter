using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000015 RID: 21
    [Guid("D4BECDDF-6F73-4A83-B832-9C66874CD20E"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwRemoteAdminSettings
    {
        // Token: 0x1700003D RID: 61
        [DispId(1)]
        NetFwIpVersion IpVersion
        {
            // Token: 0x06000127 RID: 295
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000128 RID: 296
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700003E RID: 62
        [DispId(2)]
        NetFwScope Scope
        {
            // Token: 0x06000129 RID: 297
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600012A RID: 298
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700003F RID: 63
        [DispId(3)]
        string RemoteAddresses
        {
            // Token: 0x0600012B RID: 299
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600012C RID: 300
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000040 RID: 64
        [DispId(4)]
        bool Enabled
        {
            // Token: 0x0600012D RID: 301
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600012E RID: 302
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
