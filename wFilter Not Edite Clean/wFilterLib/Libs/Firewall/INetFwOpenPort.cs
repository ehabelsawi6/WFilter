using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x0200000F RID: 15
    [Guid("E0483BA0-47FF-4D9C-A6D6-7741D0B195F7"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwOpenPort
    {
        // Token: 0x1700001A RID: 26
        [DispId(1)]
        string Name
        {
            // Token: 0x060000E8 RID: 232
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060000E9 RID: 233
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x1700001B RID: 27
        [DispId(2)]
        NetFwIpVersion IpVersion
        {
            // Token: 0x060000EA RID: 234
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000EB RID: 235
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700001C RID: 28
        [DispId(3)]
        NetFwIpProtocol Protocol
        {
            // Token: 0x060000EC RID: 236
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000ED RID: 237
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700001D RID: 29
        [DispId(4)]
        int Port
        {
            // Token: 0x060000EE RID: 238
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000EF RID: 239
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700001E RID: 30
        [DispId(5)]
        NetFwScope Scope
        {
            // Token: 0x060000F0 RID: 240
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000F1 RID: 241
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700001F RID: 31
        [DispId(6)]
        string RemoteAddresses
        {
            // Token: 0x060000F2 RID: 242
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x060000F3 RID: 243
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000020 RID: 32
        [DispId(7)]
        bool Enabled
        {
            // Token: 0x060000F4 RID: 244
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000F5 RID: 245
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000021 RID: 33
        [DispId(8)]
        bool BuiltIn
        {
            // Token: 0x060000F6 RID: 246
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
    }
}
