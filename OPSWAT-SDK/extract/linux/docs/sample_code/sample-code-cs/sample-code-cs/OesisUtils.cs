using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace sample_code_cs
{
    class OesisUtils
    {
        // Create json_in from key - value for invoke - support for types: int, string, bool
        public static int CreateJsonIn(ref string json_in, Dictionary<string, object> input)
        {
            if(!input.ContainsKey("method"))
            {
                json_in = "{ \"input\": { \"method\": -1 } }";
                return -1;
            }
            json_in = "{\"input\": { \"method\": " + input["method"];
            input.Remove("method");
            foreach (var item in input)
            {
                json_in = json_in + ", \"" + item.Key + "\": ";
                Type type = item.Value.GetType();
                if (type.Equals(typeof(string)))
                {
                    json_in = json_in + "\""  + item.Value + "\"";
                }
                else
                {
                    json_in += item.Value.ToString().ToLower();
                }
            }
            json_in += " } }";
            return 0;   
        }

        public static int GetJsonValues(ref JObject result, int rc, string json_out, List<string> keys)
        {
            dynamic jsonOut = JObject.Parse(json_out);
            if (rc < 0)
            {
                result = new JObject(jsonOut.error);
                return -1;
            }
            jsonOut = new JObject(jsonOut.result);
            if (keys.Capacity > 0)
            {
                foreach (var key in keys)
                {
                    if (jsonOut.ContainsKey(key))
                    {
                        result[key] = jsonOut[key];
                    }
                }
            }
            else 
            {
                result = jsonOut;
            }
            return 0;

        }
    }
}
