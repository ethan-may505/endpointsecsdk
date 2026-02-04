using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json.Linq;

namespace sample_code_cs
{
    public class OesisGenericProduct
    {
		public int signatureId { get; set; }
        public OesisFramework oesis { get; set; }

		public OesisGenericProduct()
		{
			signatureId = 0;
			oesis = OesisFramework.instance;
		}

		public string GetVersion()
		{
			string json_in = "{\"input\": { \"method\": 100, \"signature\": " + this.signatureId + " } }";
			string json_out;
			string result = "";
			int rc = oesis.Invoke(json_in, out json_out);
			if (rc >= 0)
			{
				dynamic jsonOut = JObject.Parse(json_out);
				result = jsonOut.result.version;
			}
			return result;
		}

		public JObject IsAuthentic()
		{
			string json_in = "{\"input\": { \"method\": 108, \"signature\": " + this.signatureId + " } }";
			string json_out;
			JObject result = new JObject();
			int rc = oesis.Invoke(json_in, out json_out);
			if (rc >= 0)
			{
				dynamic jsonOut = JObject.Parse(json_out);
				result = JObject.FromObject(new
				{
					authentic = jsonOut.result.authentic,
					details = jsonOut.result.details
				});
			}
			return result;
		}

		public JObject GetComponents()
		{
			string json_in = "{\"input\": { \"method\": 105, \"signature\": " + this.signatureId + " } }";
			string json_out;
			JObject result = new JObject();
			int rc = oesis.Invoke(json_in, out json_out);
			if (rc >= 0)
			{
				dynamic jsonOut = JObject.Parse(json_out);
				result = JObject.FromObject(new
				{
					components = jsonOut.result.components
				});
			}
			return result;
		}

	}
}
