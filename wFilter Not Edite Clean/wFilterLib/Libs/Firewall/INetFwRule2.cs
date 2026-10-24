using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000017 RID: 23
    [Guid("9C27C8DA-189B-4DDE-89F7-8B39A316782C"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwRule2 : INetFwRule
    {
        // Token: 0x17000053 RID: 83
        [DispId(1)]
        string Name
        {
            // Token: 0x06000153 RID: 339
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000154 RID: 340
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000054 RID: 84
        [DispId(2)]
        string Description
        {
            // Token: 0x06000155 RID: 341
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000156 RID: 342
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000055 RID: 85
        [DispId(3)]
        string ApplicationName
        {
            // Token: 0x06000157 RID: 343
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000158 RID: 344
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000056 RID: 86
        [DispId(4)]
        string serviceName
        {
            // Token: 0x06000159 RID: 345
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600015A RID: 346
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000057 RID: 87
        [DispId(5)]
        int Protocol
        {
            // Token: 0x0600015B RID: 347
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600015C RID: 348
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000058 RID: 88
        [DispId(6)]
        string LocalPorts
        {
            // Token: 0x0600015D RID: 349
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600015E RID: 350
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000059 RID: 89
        [DispId(7)]
        string RemotePorts
        {
            // Token: 0x0600015F RID: 351
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000160 RID: 352
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700005A RID: 90
        [DispId(8)]
        string LocalAddresses
        {
            // Token: 0x06000161 RID: 353
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000162 RID: 354
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700005B RID: 91
        [DispId(9)]
        string RemoteAddresses
        {
            // Token: 0x06000163 RID: 355
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000164 RID: 356
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700005C RID: 92
        [DispId(10)]
        string IcmpTypesAndCodes
        {
            // Token: 0x06000165 RID: 357
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000166 RID: 358
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700005D RID: 93
        [DispId(11)]
        NetFwRuleDirection Direction
        {
            // Token: 0x06000167 RID: 359
            [DispId(11)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000168 RID: 360
            [DispId(11)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700005E RID: 94
        [DispId(12)]
        object Interfaces
        {
            // Token: 0x06000169 RID: 361
            [DispId(12)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Struct)]
            get;
            // Token: 0x0600016A RID: 362
            [DispId(12)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.Struct)]
            set;
        }

        // Token: 0x1700005F RID: 95
        [DispId(13)]
        string InterfaceTypes
        {
            // Token: 0x0600016B RID: 363
            [DispId(13)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600016C RID: 364
            [DispId(13)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000060 RID: 96
        [DispId(14)]
        bool Enabled
        {
            // Token: 0x0600016D RID: 365
            [DispId(14)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600016E RID: 366
            [DispId(14)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000061 RID: 97
        [DispId(15)]
        string Grouping
        {
            // Token: 0x0600016F RID: 367
            [DispId(15)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000170 RID: 368
            [DispId(15)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000062 RID: 98
        [DispId(16)]
        int Profiles
        {
            // Token: 0x06000171 RID: 369
            [DispId(16)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000172 RID: 370
            [DispId(16)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000063 RID: 99
        [DispId(17)]
        bool EdgeTraversal
        {
            // Token: 0x06000173 RID: 371
            [DispId(17)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000174 RID: 372
            [DispId(17)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000064 RID: 100
        [DispId(18)]
        NetFwAction Action
        {
            // Token: 0x06000175 RID: 373
            [DispId(18)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000176 RID: 374
            [DispId(18)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000065 RID: 101
        [DispId(19)]
        int EdgeTraversalOptions
        {
            // Token: 0x06000177 RID: 375
            [DispId(19)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000178 RID: 376
            [DispId(19)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
