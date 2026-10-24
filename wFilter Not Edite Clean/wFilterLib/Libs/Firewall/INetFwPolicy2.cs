using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000012 RID: 18
    [Guid("98325047-C671-4174-8D81-DEFCD3F03186"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwPolicy2
    {
        // Token: 0x17000024 RID: 36
        [DispId(1)]
        int CurrentProfileTypes
        {
            // Token: 0x060000FE RID: 254
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x17000025 RID: 37
        [DispId(2)]
        bool FirewallEnabled
        {
            // Token: 0x060000FF RID: 255
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000100 RID: 256
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000026 RID: 38
        [DispId(3)]
        object ExcludedInterfaces
        {
            // Token: 0x06000101 RID: 257
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Struct)]
            get;
            // Token: 0x06000102 RID: 258
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.Struct)]
            set;
        }

        // Token: 0x17000027 RID: 39
        [DispId(4)]
        bool BlockAllInboundTraffic
        {
            // Token: 0x06000103 RID: 259
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000104 RID: 260
            [DispId(4)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000028 RID: 40
        [DispId(5)]
        bool NotificationsDisabled
        {
            // Token: 0x06000105 RID: 261
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000106 RID: 262
            [DispId(5)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x17000029 RID: 41
        [DispId(6)]
        bool UnicastResponsesToMulticastBroadcastDisabled
        {
            // Token: 0x06000107 RID: 263
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x06000108 RID: 264
            [DispId(6)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700002A RID: 42
        [DispId(7)]
        INetFwRules Rules
        {
            // Token: 0x06000109 RID: 265
            [DispId(7)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x1700002B RID: 43
        [DispId(8)]
        INetFwServiceRestriction ServiceRestriction
        {
            // Token: 0x0600010A RID: 266
            [DispId(8)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x1700002C RID: 44
        [DispId(12)]
        NetFwAction DefaultInboundAction
        {
            // Token: 0x0600010B RID: 267
            [DispId(12)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600010C RID: 268
            [DispId(12)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700002D RID: 45
        [DispId(13)]
        NetFwAction DefaultOutboundAction
        {
            // Token: 0x0600010D RID: 269
            [DispId(13)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            // Token: 0x0600010E RID: 270
            [DispId(13)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        // Token: 0x1700002E RID: 46
        [DispId(14)]
        bool IsRuleGroupCurrentlyEnabled
        {
            // Token: 0x0600010F RID: 271
            [DispId(14)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x1700002F RID: 47
        [DispId(15)]
        NetFwModifyState LocalPolicyModifyState
        {
            // Token: 0x06000110 RID: 272
            [DispId(15)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x06000111 RID: 273
        [DispId(9)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void EnableRuleGroup([In] int profileTypesBitmask, [MarshalAs(UnmanagedType.BStr)][In] string group, [In] bool enable);

        // Token: 0x06000112 RID: 274
        [DispId(10)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        bool IsRuleGroupEnabled([In] int profileTypesBitmask, [MarshalAs(UnmanagedType.BStr)][In] string group);

        // Token: 0x06000113 RID: 275
        [DispId(11)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void RestoreLocalFirewallDefaults();
    }
}
