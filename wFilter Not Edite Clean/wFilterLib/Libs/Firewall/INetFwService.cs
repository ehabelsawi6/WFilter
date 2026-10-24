using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x0200001A RID: 26
    [Guid("79FD57C8-908E-4A36-9888-D5B3F0A444CF"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwService
    {
        // Token: 0x17000080 RID: 128
        [DispId(1)]
        string Name
        {
            // Token: 0x060001B0 RID: 432
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
        }

        // Token: 0x17000081 RID: 129
        [DispId(2)]
        NetFwServiceType Type
        {
            // Token: 0x060001B1 RID: 433
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x17000082 RID: 130
        [DispId(3)]
        bool Customized
        {
            // Token: 0x060001B2 RID: 434
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x17000083 RID: 131
        [DispId(4)]
        NetFwIpVersion IpVersion
        {
            // Token: 0x060001B3 RID: 435
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060001B4 RID: 436
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000084 RID: 132
        [DispId(5)]
        NetFwScope Scope
        {
            // Token: 0x060001B5 RID: 437
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060001B6 RID: 438
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000085 RID: 133
        [DispId(6)]
        string RemoteAddresses
        {
            // Token: 0x060001B7 RID: 439
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060001B8 RID: 440
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000086 RID: 134
        [DispId(7)]
        bool Enabled
        {
            // Token: 0x060001B9 RID: 441
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060001BA RID: 442
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000087 RID: 135
        [DispId(8)]
        INetFwOpenPorts GloballyOpenPorts
        {
            // Token: 0x060001BB RID: 443
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }
    }
}
