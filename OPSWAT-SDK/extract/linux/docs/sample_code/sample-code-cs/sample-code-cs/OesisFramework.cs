using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace sample_code_cs
{
    public class OesisFramework : OesisSingleton<OesisFramework>
    {
        string passkey;
        public void Set(string license)
        {
            passkey = license;
        }
        public string Get()
        {
            string config = "{ \"config\" : { \"passkey_string\": \"" + passkey + "\", \"enable_pretty_print\": true, \"silent_mode\": true } }";
            return config;
        }

        public enum PLATFORM{
            NONE,
            WINDOWS,
            LINUX,
            MAXOS
        }
        private static PLATFORM os_type = PLATFORM.NONE;
        public static PLATFORM GetOSType()
        {
            return os_type;
        }
        
        const string LIB_WAAPI = "libwaapi";
        [DllImport(LIB_WAAPI, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Auto)]
        private static extern int wa_api_setup([MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(XStringMarshaler))] string json_config,
                                                out IntPtr json_out);

        [DllImport(LIB_WAAPI, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Auto)]
        private static extern int wa_api_invoke([MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(XStringMarshaler))] string json_config,
                                                out IntPtr json_out);

        [DllImport(LIB_WAAPI, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Auto)]
        private static extern int wa_api_teardown();

        [DllImport(LIB_WAAPI, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Auto)]
        private static extern int wa_api_free(IntPtr json_data);

        public int Setup(string json_config, out string json_out)
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
                os_type = PLATFORM.LINUX;
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
                os_type = PLATFORM.MAXOS;
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
                os_type = PLATFORM.WINDOWS;

            IntPtr outPtr = IntPtr.Zero;
            int rc = wa_api_setup(json_config, out outPtr);
            json_out = "{ }";
            if (outPtr != IntPtr.Zero)
            {
                json_out = XStringMarshaler.PtrToString(outPtr);
                wa_api_free(outPtr);
            }
            return rc;
        }

        public int Invoke(string json_config, out string json_out)
        {
            IntPtr outPtr = IntPtr.Zero;
            int rc = wa_api_invoke(json_config, out outPtr);
            json_out = "{ }";
            if (outPtr != IntPtr.Zero)
            {
                json_out = XStringMarshaler.PtrToString(outPtr);
                wa_api_free(outPtr);
            }
            return rc;
        }

        public int DetectAllProducts(out string json_out)
        {
            string json_in = "{\"input\": { \"method\": 0 } }";
            return Invoke(json_in, out json_out);
        }

        public int DetectAntimalwareProducts(out string json_out)
        {
            string json_in = "{\"input\": { \"method\": 0, \"category\": 5 } }";
            return Invoke(json_in, out json_out);
        }

        public static int teardown() => wa_api_teardown();
    }
}
