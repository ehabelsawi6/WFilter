using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000016 RID: 22
    [Guid("AF230D27-BABA-4E42-ACED-F524F22CFCE2"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwRule
    {
        // Token: 0x17000041 RID: 65
        [DispId(1)]
        string Name
        {
            // Token: 0x0600012F RID: 303
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000130 RID: 304
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000042 RID: 66
        [DispId(2)]
        string? Description
        {
            // Token: 0x06000131 RID: 305
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000132 RID: 306
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000043 RID: 67
        [DispId(3)]
        string ApplicationName
        {
            // Token: 0x06000133 RID: 307
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000134 RID: 308
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000044 RID: 68
        [DispId(4)]
        string serviceName
        {
            // Token: 0x06000135 RID: 309
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000136 RID: 310
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000045 RID: 69
        [DispId(5)]
        int Protocol
        {
            // Token: 0x06000137 RID: 311
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000138 RID: 312
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000046 RID: 70
        [DispId(6)]
        string LocalPorts
        {
            // Token: 0x06000139 RID: 313
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600013A RID: 314
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000047 RID: 71
        [DispId(7)]
        string RemotePorts
        {
            // Token: 0x0600013B RID: 315
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600013C RID: 316
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000048 RID: 72
        [DispId(8)]
        string LocalAddresses
        {
            // Token: 0x0600013D RID: 317
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600013E RID: 318
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000049 RID: 73
        [DispId(9)]
        string? RemoteAddresses
        {
            // Token: 0x0600013F RID: 319
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000140 RID: 320
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700004A RID: 74
        [DispId(10)]
        string IcmpTypesAndCodes
        {
            // Token: 0x06000141 RID: 321
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000142 RID: 322
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700004B RID: 75
        [DispId(11)]
        NetFwRuleDirection Direction
        {
            // Token: 0x06000143 RID: 323
            [DispId(11)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000144 RID: 324
            [DispId(11)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700004C RID: 76
        [DispId(12)]
        object Interfaces
        {
            // Token: 0x06000145 RID: 325
            [DispId(12)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Struct)]
            get;
            // Token: 0x06000146 RID: 326
            [DispId(12)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.Struct)]
            set;
        }

        // Token: 0x1700004D RID: 77
        [DispId(13)]
        string InterfaceTypes
        {
            // Token: 0x06000147 RID: 327
            [DispId(13)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000148 RID: 328
            [DispId(13)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700004E RID: 78
        [DispId(14)]
        bool Enabled
        {
            // Token: 0x06000149 RID: 329
            [DispId(14)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600014A RID: 330
            [DispId(14)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700004F RID: 79
        [DispId(15)]
        string Grouping
        {
            // Token: 0x0600014B RID: 331
            [DispId(15)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x0600014C RID: 332
            [DispId(15)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000050 RID: 80
        [DispId(16)]
        int Profiles
        {
            // Token: 0x0600014D RID: 333
            [DispId(16)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600014E RID: 334
            [DispId(16)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000051 RID: 81
        [DispId(17)]
        bool EdgeTraversal
        {
            // Token: 0x0600014F RID: 335
            [DispId(17)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000150 RID: 336
            [DispId(17)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000052 RID: 82
        [DispId(18)]
        NetFwAction Action
        {
            // Token: 0x06000151 RID: 337
            [DispId(18)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000152 RID: 338
            [DispId(18)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
