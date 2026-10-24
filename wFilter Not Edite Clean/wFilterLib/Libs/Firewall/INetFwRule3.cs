using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000018 RID: 24
    [Guid("B21563FF-D696-4222-AB46-4E89B73AB34A"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwRule3 : INetFwRule2, INetFwRule
    {
        // Token: 0x17000066 RID: 102
        [DispId(1)]
        string Name
        {
            // Token: 0x06000179 RID: 377
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600017A RID: 378
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000067 RID: 103
        [DispId(2)]
        string Description
        {
            // Token: 0x0600017B RID: 379
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600017C RID: 380
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000068 RID: 104
        [DispId(3)]
        string ApplicationName
        {
            // Token: 0x0600017D RID: 381
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600017E RID: 382
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000069 RID: 105
        [DispId(4)]
        string serviceName
        {
            // Token: 0x0600017F RID: 383
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000180 RID: 384
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700006A RID: 106
        [DispId(5)]
        int Protocol
        {
            // Token: 0x06000181 RID: 385
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000182 RID: 386
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700006B RID: 107
        [DispId(6)]
        string LocalPorts
        {
            // Token: 0x06000183 RID: 387
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000184 RID: 388
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700006C RID: 108
        [DispId(7)]
        string RemotePorts
        {
            // Token: 0x06000185 RID: 389
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000186 RID: 390
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700006D RID: 109
        [DispId(8)]
        string LocalAddresses
        {
            // Token: 0x06000187 RID: 391
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000188 RID: 392
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700006E RID: 110
        [DispId(9)]
        string RemoteAddresses
        {
            // Token: 0x06000189 RID: 393
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600018A RID: 394
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700006F RID: 111
        [DispId(10)]
        string IcmpTypesAndCodes
        {
            // Token: 0x0600018B RID: 395
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600018C RID: 396
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000070 RID: 112
        [DispId(11)]
        NetFwRuleDirection Direction
        {
            // Token: 0x0600018D RID: 397
            [DispId(11)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600018E RID: 398
            [DispId(11)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000071 RID: 113
        [DispId(12)]
        object Interfaces
        {
            // Token: 0x0600018F RID: 399
            [DispId(12)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Struct)]
            get;
            // Token: 0x06000190 RID: 400
            [DispId(12)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.Struct)]
            set;
        }

        // Token: 0x17000072 RID: 114
        [DispId(13)]
        string InterfaceTypes
        {
            // Token: 0x06000191 RID: 401
            [DispId(13)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000192 RID: 402
            [DispId(13)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000073 RID: 115
        [DispId(14)]
        bool Enabled
        {
            // Token: 0x06000193 RID: 403
            [DispId(14)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000194 RID: 404
            [DispId(14)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000074 RID: 116
        [DispId(15)]
        string Grouping
        {
            // Token: 0x06000195 RID: 405
            [DispId(15)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000196 RID: 406
            [DispId(15)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000075 RID: 117
        [DispId(16)]
        int Profiles
        {
            // Token: 0x06000197 RID: 407
            [DispId(16)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000198 RID: 408
            [DispId(16)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000076 RID: 118
        [DispId(17)]
        bool EdgeTraversal
        {
            // Token: 0x06000199 RID: 409
            [DispId(17)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600019A RID: 410
            [DispId(17)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000077 RID: 119
        [DispId(18)]
        NetFwAction Action
        {
            // Token: 0x0600019B RID: 411
            [DispId(18)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600019C RID: 412
            [DispId(18)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000078 RID: 120
        [DispId(19)]
        int EdgeTraversalOptions
        {
            // Token: 0x0600019D RID: 413
            [DispId(19)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600019E RID: 414
            [DispId(19)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000079 RID: 121
        [DispId(20)]
        string LocalAppPackageId
        {
            // Token: 0x0600019F RID: 415
            [DispId(20)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060001A0 RID: 416
            [DispId(20)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700007A RID: 122
        [DispId(21)]
        string LocalUserOwner
        {
            // Token: 0x060001A1 RID: 417
            [DispId(21)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060001A2 RID: 418
            [DispId(21)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700007B RID: 123
        [DispId(22)]
        string LocalUserAuthorizedList
        {
            // Token: 0x060001A3 RID: 419
            [DispId(22)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060001A4 RID: 420
            [DispId(22)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700007C RID: 124
        [DispId(23)]
        string RemoteUserAuthorizedList
        {
            // Token: 0x060001A5 RID: 421
            [DispId(23)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060001A6 RID: 422
            [DispId(23)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700007D RID: 125
        [DispId(24)]
        string RemoteMachineAuthorizedList
        {
            // Token: 0x060001A7 RID: 423
            [DispId(24)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060001A8 RID: 424
            [DispId(24)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700007E RID: 126
        [DispId(25)]
        int SecureFlags
        {
            // Token: 0x060001A9 RID: 425
            [DispId(25)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060001AA RID: 426
            [DispId(25)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
