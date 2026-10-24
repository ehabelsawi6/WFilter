using System.Collections;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.CustomMarshalers;

namespace wFilterLib.Libs.Firewall
{
    // Token: 0x02000010 RID: 16
    [Guid("C0E9D7FA-E07E-430A-B19A-090CE82D92E2"), TypeLibType(4160)]
    [ComImport]
    public interface INetFwOpenPorts : IEnumerable
    {
        // Token: 0x17000022 RID: 34
        [DispId(1)]
        int Count
        {
            // Token: 0x060000F7 RID: 247
            [DispId(1)]
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        // Token: 0x060000F8 RID: 248
        [DispId(2)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void Add([MarshalAs(UnmanagedType.Interface)][In] INetFwOpenPort port);

        // Token: 0x060000F9 RID: 249
        [DispId(3)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        void Remove([In] int portNumber, [In] NetFwIpProtocol ipProtocol);

        // Token: 0x060000FA RID: 250
        [DispId(4)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.Interface)]
        INetFwOpenPort Item([In] int portNumber, [In] NetFwIpProtocol ipProtocol);

        // Token: 0x060000FB RID: 251
        [DispId(-4), TypeLibFunc(1)]
        [MethodImpl(MethodImplOptions.InternalCall)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(EnumeratorToEnumVariantMarshaler))]
        IEnumerator GetEnumerator();
    }
}
