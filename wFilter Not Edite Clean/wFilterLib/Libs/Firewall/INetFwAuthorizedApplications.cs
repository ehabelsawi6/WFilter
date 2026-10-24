using System.Collections;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.CustomMarshalers;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x0200000C RID: 12
    [Guid("644EFD52-CCF9-486C-97A2-39F352570B30"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwAuthorizedApplications : IEnumerable
    {
        // Token: 0x1700000D RID: 13
        [DispId(1)]
        int Count
        {
            // Token: 0x060000CA RID: 202
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x060000CB RID: 203
        [DispId(2)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void Add([MarshalAs(UnmanagedType.Interface)][In] INetFwAuthorizedApplication app);

        // Token: 0x060000CC RID: 204
        [DispId(3)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void Remove([MarshalAs(UnmanagedType.BStr)][In] string imageFileName);

        // Token: 0x060000CD RID: 205
        [DispId(4)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.Interface)]
        INetFwAuthorizedApplication Item([MarshalAs(UnmanagedType.BStr)][In] string imageFileName);

        // Token: 0x060000CE RID: 206
        [DispId(-4), TypeLibFunc(1)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(EnumeratorToEnumVariantMarshaler))]
        IEnumerator GetEnumerator();
    }
}
