using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000014 RID: 20
    [Guid("174A0DDA-E9F9-449D-993B-21AB667CA456"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwProfile
    {
        // Token: 0x17000033 RID: 51
        [DispId(1)]
        NetFwProfileType Type
        {
            // Token: 0x06000119 RID: 281
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x17000034 RID: 52
        [DispId(2)]
        bool FirewallEnabled
        {
            // Token: 0x0600011A RID: 282
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600011B RID: 283
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000035 RID: 53
        [DispId(3)]
        bool ExceptionsNotAllowed
        {
            // Token: 0x0600011C RID: 284
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600011D RID: 285
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000036 RID: 54
        [DispId(4)]
        bool NotificationsDisabled
        {
            // Token: 0x0600011E RID: 286
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600011F RID: 287
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000037 RID: 55
        [DispId(5)]
        bool UnicastResponsesToMulticastBroadcastDisabled
        {
            // Token: 0x06000120 RID: 288
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000121 RID: 289
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000038 RID: 56
        [DispId(6)]
        INetFwRemoteAdminSettings RemoteAdminSettings
        {
            // Token: 0x06000122 RID: 290
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x17000039 RID: 57
        [DispId(7)]
        INetFwIcmpSettings IcmpSettings
        {
            // Token: 0x06000123 RID: 291
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x1700003A RID: 58
        [DispId(8)]
        INetFwOpenPorts GloballyOpenPorts
        {
            // Token: 0x06000124 RID: 292
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x1700003B RID: 59
        [DispId(9)]
        INetFwServices Services
        {
            // Token: 0x06000125 RID: 293
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x1700003C RID: 60
        [DispId(10)]
        INetFwAuthorizedApplications AuthorizedApplications
        {
            // Token: 0x06000126 RID: 294
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }
    }
}
