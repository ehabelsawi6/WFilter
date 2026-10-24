using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000013 RID: 19
    [Guid("71881699-18F4-458B-B892-3FFCE5E07F75"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwProduct
    {
        // Token: 0x17000030 RID: 48
        [DispId(1)]
        object RuleCategories
        {
            // Token: 0x06000114 RID: 276
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.Struct)]
            get;
            // Token: 0x06000115 RID: 277
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.Struct)]
            set;
        }

        // Token: 0x17000031 RID: 49
        [DispId(2)]
        string DisplayName
        {
            // Token: 0x06000116 RID: 278
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
            // Token: 0x06000117 RID: 279
            [DispId(2)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [param: MarshalAs(UnmanagedType.BStr)]
            set;
        }

        // Token: 0x17000032 RID: 50
        [DispId(3)]
        string PathToSignedProductExe
        {
            // Token: 0x06000118 RID: 280
            [DispId(3)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            [return: MarshalAs(UnmanagedType.BStr)]
            get;
        }
    }
}
