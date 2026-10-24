using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000011 RID: 17
    [Guid("D46D2478-9AC9-4008-9DC7-5563CE5536CC"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwPolicy
    {
        // Token: 0x17000023 RID: 35
        [DispId(1)]
        INetFwProfile CurrentProfile
        {
            // Token: 0x060000FC RID: 252
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Interface)]
            get;
        }

        // Token: 0x060000FD RID: 253
        [DispId(2)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.Interface)]
        INetFwProfile GetProfileByType([In] NetFwProfileType profileType);
    }
}
