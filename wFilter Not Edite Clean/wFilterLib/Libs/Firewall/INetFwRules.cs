using System.Collections;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.CustomMarshalers;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000019 RID: 25
    [Guid("9C4C6277-5027-441E-AFAE-CA1F542DA009"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwRules : IEnumerable
    {
        // Token: 0x1700007F RID: 127
        [DispId(1)]
        int Count
        {
            // Token: 0x060001AB RID: 427
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x060001AC RID: 428
        [DispId(2)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void Add([MarshalAs(UnmanagedType.Interface)][In] INetFwRule rule);

        // Token: 0x060001AD RID: 429
        [DispId(3)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void Remove([MarshalAs(UnmanagedType.BStr)][In] string name);

        // Token: 0x060001AE RID: 430
        [DispId(4)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.Interface)]
        INetFwRule Item([MarshalAs(UnmanagedType.BStr)][In] string name);

        // Token: 0x060001AF RID: 431
        [DispId(-4), TypeLibFunc(1)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(EnumeratorToEnumVariantMarshaler))]
        IEnumerator GetEnumerator();
    }
}
