using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x0200000D RID: 13
    [Guid("A6207B2E-7CDD-426A-951E-5E1CBC5AFEAD"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwIcmpSettings
    {
        // Token: 0x1700000E RID: 14
        [DispId(1)]
        bool AllowOutboundDestinationUnreachable
        {
            // Token: 0x060000CF RID: 207
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000D0 RID: 208
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700000F RID: 15
        [DispId(2)]
        bool AllowRedirect
        {
            // Token: 0x060000D1 RID: 209
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000D2 RID: 210
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000010 RID: 16
        [DispId(3)]
        bool AllowInboundEchoRequest
        {
            // Token: 0x060000D3 RID: 211
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000D4 RID: 212
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000011 RID: 17
        [DispId(4)]
        bool AllowOutboundTimeExceeded
        {
            // Token: 0x060000D5 RID: 213
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000D6 RID: 214
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000012 RID: 18
        [DispId(5)]
        bool AllowOutboundParameterProblem
        {
            // Token: 0x060000D7 RID: 215
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000D8 RID: 216
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000013 RID: 19
        [DispId(6)]
        bool AllowOutboundSourceQuench
        {
            // Token: 0x060000D9 RID: 217
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000DA RID: 218
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000014 RID: 20
        [DispId(7)]
        bool AllowInboundRouterRequest
        {
            // Token: 0x060000DB RID: 219
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000DC RID: 220
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000015 RID: 21
        [DispId(8)]
        bool AllowInboundTimestampRequest
        {
            // Token: 0x060000DD RID: 221
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000DE RID: 222
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000016 RID: 22
        [DispId(9)]
        bool AllowInboundMaskRequest
        {
            // Token: 0x060000DF RID: 223
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000E0 RID: 224
            [DispId(9)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000017 RID: 23
        [DispId(10)]
        bool AllowOutboundPacketTooBig
        {
            // Token: 0x060000E1 RID: 225
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x060000E2 RID: 226
            [DispId(10)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
