using System;
using System.Collections;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;

namespace sample_code_cs
{
    class Program
    {

        static void ShowRunningStatus()
        {
            string tmp = "RUNNING";
            Console.Write(tmp + "\r");
            for (int i = 0; i < 5; ++i) {
                Thread.Sleep(1000);
                tmp += ".";
                Console.Write(tmp + "\r");
            }
            ClearRunningStatus();
        }
        static void ClearRunningStatus()
        {
            Console.Write("\r            \r");
        }

        static int LoadParseCommand(Object obj)
        {
            string[] args = ((IEnumerable)obj).Cast<Object>()
                                 .Select(x => x.ToString())
                                 .ToArray();
            if (args.Length > 0 && (args[0] == "call-method" || args[0] == "check-av" || args[0] == "check-vuln" || args[0] == "patch-product" || args[0] == "remove-product" || args[0] == "dlp"))
            {
                OesisFramework oesis = new OesisFramework();
                string path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
                string passkey = File.ReadAllText(path + "/pass_key.txt").Replace("\n", "").Replace("\r", "");
                oesis.Set(passkey);
                string json_config = oesis.Get();
                string json_out;
                if (oesis.Setup(json_config, out json_out) < 0)
                {
                    Console.WriteLine(json_out);
                    return -1;
                }
            }
            return OesisCommand.ParseCommand(args);
        }

        static void Main(string[] args)
        {
            
            Task<int> task = new Task<int>(LoadParseCommand, args);
            task.Start();
            // https://docs.microsoft.com/en-us/dotnet/api/system.threading.tasks.taskstatus?view=net-5.0
            while ((int)task.Status != 5)
            {
                if(!OesisCommand.wait)
                {
                    ShowRunningStatus();
                }

            }
            //ClearRunningStatus();
            int rc = task.Result;
            string output = OesisCommand.cliResult;
            Console.WriteLine(output);
        }
    }
}
