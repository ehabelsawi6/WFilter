using System.Collections;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.CustomMarshalers;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x0200001C RID: 28
    [Guid("79649BB4-903E-421B-94C9-79848E79F6EE"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwServices : IEnumerable
    {
        // Token: 0x17000089 RID: 137
        [DispId(1)]
        int Count
        {
            // Token: 0x060001BF RID: 447
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x060001C0 RID: 448
        [DispId(2)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.Interface)]
        INetFwService Item([In] NetFwServiceType svcType);

        // Token: 0x060001C1 RID: 449
        [DispId(-4), TypeLibFunc(1)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(EnumeratorToEnumVariantMarshaler))]
        IEnumerator GetEnumerator();
    }
}
