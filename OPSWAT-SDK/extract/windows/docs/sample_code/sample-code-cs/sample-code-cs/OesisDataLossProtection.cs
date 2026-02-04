using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace sample_code_cs
{
    class OesisDataLossProtection : OesisGenericProduct
    {
        private static readonly OesisDataLossProtection m_instance = new OesisDataLossProtection();

        public OesisDataLossProtection() { }

        public static OesisDataLossProtection instance
        {
            get
            {
                return m_instance;
            }
        }

        public int InstallDLPModule(int methodId, ref JObject result)
        {
            string json_in = "";
            Dictionary<string, object> input = new Dictionary<string, object>()
            {
                { "method", methodId },
            };
            OesisUtils.CreateJsonIn(ref json_in, input);
            string json_out;
            int rc = this.oesis.Invoke(json_in, out json_out);
            OesisUtils.GetJsonValues(ref result, rc, json_out, new List<string> { });

            return rc;
        }

        public int UninstallDLPModule(int methodId, ref JObject result)
        {
            string json_in = "";
            Dictionary<string, object> input = new Dictionary<string, object>()
            {
                { "method", methodId },
            };
            OesisUtils.CreateJsonIn(ref json_in, input);
            string json_out;
            int rc = this.oesis.Invoke(json_in, out json_out);
            OesisUtils.GetJsonValues(ref result, rc, json_out, new List<string> { });
            return rc;
        }

        public int ManageDLPModule(ref JObject result, int methodId, string operation = "")
        {
            string json_in = "";
            Dictionary<string, object> input = new Dictionary<string, object>()
            {
                { "method", methodId }
            };
            if(operation != "")
            {
                input.Add("operation", operation);
            }
            OesisUtils.CreateJsonIn(ref json_in, input);
            string json_out;
            int rc = this.oesis.Invoke(json_in, out json_out);
            OesisUtils.GetJsonValues(ref result, rc, json_out, new List<string> { });
            return rc;
        }

        public int GetDLPState(int methodId, ref JObject result)
        {
            string json_in = "";
            Dictionary<string, object> input = new Dictionary<string, object>()
            {
                { "method", methodId }
            };
            OesisUtils.CreateJsonIn(ref json_in, input);
            string json_out;
            int rc = this.oesis.Invoke(json_in, out json_out);
            OesisUtils.GetJsonValues(ref result, rc, json_out, new List<string> { "state", "enabled" });
            return rc;
        }
    }
}
