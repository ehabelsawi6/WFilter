using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x0200001B RID: 27
    [Guid("8267BBE3-F890-491C-B7B6-2DB1EF0E5D2B"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwServiceRestriction
    {
        // Token: 0x17000088 RID: 136
        [DispId(3)]
        INetFwRules Rules
        {
            // Token: 0x060001BC RID: 444
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x060001BD RID: 445
        [DispId(1)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void RestrictService([MarshalAs(UnmanagedType.BStr)][In] string serviceName, [MarshalAs(UnmanagedType.BStr)][In] string appName, [In] bool restrictService, [In] bool serviceSidRestricted);

        // Token: 0x060001BE RID: 446
        [DispId(2)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        bool ServiceRestricted([MarshalAs(UnmanagedType.BStr)][In] string serviceName, [MarshalAs(UnmanagedType.BStr)][In] string appName);
    }
}
