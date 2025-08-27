using System.CommandLine;
using System.CommandLine.Parsing;
using System.CommandLine.Invocation;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.IO;
using System.Threading;

namespace sample_code_cs
{
    static class OesisCommand
    {
        public static string cliResult;
        public static bool wait = false;
        public static int ParseCommand(string[] args)
        {
            var call_method = new Command("call-method", "Call a specific method")
            {
                new Option<string>("--file")
                {
                    Description = "Call specific method from input file",
                    IsRequired = false
                },
                new Option<string>("--name")
                {
                    Description = "The method name of the product",
                    IsRequired = false
                },
                new Option<string>("--id")
                {
                    Description = "The method id of product",
                    IsRequired = false
                },
                new Option<string>("--sig")
                {
                    Description = "The signature of product",
                    IsRequired = false
                },
                new Option<string>("--category")
                {
                    Description = "The category id of the product",
                    IsRequired = false
                },
                new Option<string>("--scan_type")
                {
                    Description = "The type of Scan to get the time",
                    IsRequired = false
                },
                new Option<string>("--path")
                {
                    Description = "The full path to a file, or folder",
                    IsRequired = false
                },
                new Option<string>("--clean")
                {
                    Description = "Clean theats detected during the scan",
                    IsRequired = false
                },
                new Option<string>("--timeframe")
                {
                    Description = "The timefram in days used to determine if the update is recent",
                    IsRequired = false
                },
                new Option<string>("--operation")
                {
                    Description = "The operation to be perform",
                    IsRequired = false
                },
                new Option<string>("--password")
                {
                    Description = "The password required by the product to modify the application state",
                    IsRequired = false
                },
                new Option<string>("--user")
                {
                    Description = "The user required by the product to modify the application state",
                    IsRequired = false
                },
                new Option<string>("--vm_id")
                {
                    Description = "The identification of VM that was recieved from the call",
                    IsRequired = false
                },
                new Option<string>("--token")
                {
                    Description = "Token string to download files",
                    IsRequired = false
                },
                new Option<string>("--source_file")
                {
                    Description = "Input database if to be cosumed from a file location",
                    IsRequired = false
                },
                new Option<string>("--checksum_file")
                {
                    Description = "Input database if to be cosumed from a file location",
                    IsRequired = false
                },
                new Option<string>("--timeout")
                {
                    Description = "A timeout value in seconds that can be set to this api call",
                    IsRequired = false
                },
                new Option<string>("--os_id")
                {
                    Description = "MDES SDK identifier of the OS",
                    IsRequired = false
                },
                new Option<string>("--tolerance")
                {
                    Description = "A tolerance factor that can be used to loosen the 'is_current' metric",
                    IsRequired = false
                },
                new Option<string>("--online")
                {
                    Description = "A timeout value in seconds that can be set to this api call",
                    IsRequired = false
                }
            }.WithHandler(nameof(HandleCallMethodWithParam));
            call_method.AddValidator(options =>
            {
                int count = 0;
                List<string> arguments = new List<string> { "--file", "--id", "--name" };
                foreach (string argument in arguments)
                {
                    if (options.Children.Contains(argument))
                    {
                        count++;
                    }
                }
                if (count == 0)
                {
                    return "Input must contain one in three options ('--file' or '--id' or '--name').";
                }
                else if (count > 1)
                {
                    return "Input cannot contain more than one options in three options ('--file' or 'id' or '--name')";
                }
                return null;
            });

            var check_av = new Command("check-av", "Check Antivirus products").WithHandler(nameof(HandleCheckAV));
            var check_vul = new Command("check-vuln", "Check Vulnerability products").WithHandler(nameof(HandleCheckVUL));
            var patch_product = new Command("patch-product", "Download latest version and install product")
            {
                new Option<int>("--sig")
                {
                    Description = "The signature of product.",
                    IsRequired = true
                },
                new Option<string>("--location")
                {
                    Description = "The dicectory's path will save the installer.",
                    IsRequired = true
                },
                new Option<int>("--force_close")
                {
                    Description = "Force close running product or not before installing. Default is 0",
                    ArgumentHelpName = "0/1",
                    IsRequired = false
                }
            }.WithHandler(nameof(HandlePatchProduct));

            var remove_product = new Command("remove-product", "Uninstall a product")
            {
                new Option<int>("--sig")
                {
                    Description = "The signature id of the product",
                    IsRequired = true
                },
                new Option<string>("--type")
                {
                    Description = "Type remove product native/auto. Default is auto.",
                    ArgumentHelpName = "native/auto",
                    IsRequired = false
                }
            }.WithHandler(nameof(HandleRemoveProduct));

            var dlp = new Command("dlp", "DLP module for Antikeylogger and AntiScreenCapture")
            {
                new Option<string>("--asc")
                {
                    Description = "AntiScreenCapture",
                    ArgumentHelpName = "enable/disable",
                    IsRequired = false
                },
                new Option<string>("--akl")
                {
                    Description = "AntiKeylogger",
                    ArgumentHelpName = "enable/disable",
                    IsRequired = false
                },
                new Option<int>("--pid")
                {
                    Description = "PID will be show/hide in AntiScreenCapture.",
                    IsRequired = false
                }
            }.WithHandler(nameof(HandleDLP));
            dlp.AddValidator(dlp =>
            {
                if (dlp.Children.Contains("--asc") && dlp.Children.Contains("--akl"))
                {
                    return "Input cannot contain more than one in two options ('--asc'or '--akl')";
                }
                else if (!dlp.Children.Contains("--asc") && !dlp.Children.Contains("--akl"))
                {
                    return "Input must contain one in two options ('--asc' or '--akl')";
                }
                return null;
            });
            // Create a root command with some options
            var rootCommand = new RootCommand()
            {
                call_method,
                check_av,
                check_vul,
                patch_product,
                remove_product,
                dlp,
            };

            rootCommand.Description = "Sample Code with C#";
            int rc = rootCommand.Invoke(args);
            return rc;
        }

        private static void HandleCallMethodWithParam(
            string file, string name, string id, string sig, string category, string scan_type, string path,
            string clean, string timeframe, string operation, string password, string user, string vm_id, string token,
            string source_file, string checksum_file, string timeout, string os_id, string tolerance, string online,
            IConsole console)
        {
            var map_param = new Dictionary<string, string>();
            map_param["file"] = file;
            map_param["name"] = name;
            map_param["id"] = id;
            map_param["sig"] = sig;
            map_param["category"] = category;
            map_param["scan_type"] = scan_type;
            map_param["path"] = path;
            map_param["clean"] = clean;
            map_param["timeframe"] = timeframe;
            map_param["operation"] = operation;
            map_param["password"] = password;
            map_param["user"] = user;
            map_param["vm_id"] = vm_id;
            map_param["token"] = token;
            map_param["source_file"] = source_file;
            map_param["checksum_file"] = checksum_file;
            map_param["timeout"] = timeout;
            map_param["os_id"] = os_id;
            map_param["tolerance"] = tolerance;
            map_param["online"] = online;

            var mapMethod = new Dictionary<string, int>();
            //OESIS Core
            mapMethod["DetectProducts"] = 0;
            mapMethod["DiscoverProducts"] = 100001;
            mapMethod["GetOSInfo"] = 1;
            mapMethod["GetLicenseInfo"] = 2;
            mapMethod["UpdateLicenseInfo"] = 3;
            mapMethod["GetDeviceIdentity"] = 4;
            mapMethod["QueryAsyncResults"] = 5;
            mapMethod["GetActiveUserInfo"] = 6;
            mapMethod["GetVersion"] = 100;
            mapMethod["GetRunningState"] = 101;
            mapMethod["Run"] = 102;
            mapMethod["TerminateProcesses"] = 103;
            mapMethod["GetInstallationDirectories"] = 104;
            mapMethod["GetComponents"] = 105;
            mapMethod["GetUninstallString"] = 106;
            mapMethod["ManageLabels"] = 107;
            mapMethod["IsAuthentic"] = 108;
            mapMethod["GetProductInfo"] = 109;
            //Antimalware
            mapMethod["GetRealTimeProtectionState"] = 1000;
            mapMethod["EnableRTP"] = 1005;
            mapMethod["GetDefinitionState"] = 1001;
            mapMethod["UpdateDefinitions"] = 1003;
            mapMethod["GetThreats"] = 1002;
            mapMethod["GetLastScanTime"] = 1004;
            mapMethod["Scan"] = 1006;
            mapMethod["GetScanState"] = 1022;
            //Firewall
            mapMethod["GetFirewallState"] = 1007;
            mapMethod["SetFirewallState"] = 1015;
            //Antiphishing
            mapMethod["GetAntiphishingState"] = 1010;
            //DeviceInfo
            mapMethod["GetPCModel"] = 30001;
            mapMethod["GetCpuAndRamInfo"] = 30002;
            mapMethod["GetPCComponents"] = 30003;
            mapMethod["GetDiskSpace"] = 30004;
            mapMethod["GetDevicePasswordProtectionState"] = 30005;
            mapMethod["IsCurrentDeviceVirtual"] = 30006;
            mapMethod["IsCurrentDeviceVirtual"] = 30010;
            //Backup
            mapMethod["GetBackupState"] = 1008;
            //Encrypt
            mapMethod["GetEncryptionState"] = 1009;
            //VirtualMachine
            mapMethod["GetAvailableVMs"] = 1017;
            mapMethod["ListSnapshots"] = 1018;
            mapMethod["ManageVM"] = 1019;
            mapMethod["GetVMState"] = 1020;

            string json_out = "";
            if (file != "")
            {
                string input = "";
                try
                {
                    input = System.IO.File.ReadAllText(@file);
                }
                catch (Exception e) { }

                int rc = OesisFramework.instance.Invoke(input, out json_out);
                //Console.WriteLine(json_out);
            }
            else
            {
                string input = "{ \"input\": { ";
                bool isMethod = true;
                if (id != "")
                {
                    input = input + "\"method\": " + id;
                }
                else if (name != "")
                {
                    foreach (var pair in mapMethod)
                    {
                        if (pair.Key == name)
                        {
                            input = input + "\"method\": " + pair.Value;
                            break;
                        }
                    }
                }
                else
                {
                    input = input + "\"method\": -1";
                    isMethod = false;
                }

                if (isMethod)
                {
                    if (id == "50300" || id == "50301" || id == "50500" ||
                    id == "50501" || id == "50502" || id == "50503" ||
                    id == "50505" || id == "50509" || id == "50550")
                    {
                        OesisVulnerabilityAndPatch oesisVulnerabilityAndPatch = OesisVulnerabilityAndPatch.instance;
                        oesisVulnerabilityAndPatch.ConsumeOfflineVmodDatabase();
                        if(id == "50300" || id == "50301")
                            oesisVulnerabilityAndPatch.LoadPatchDatabase();
                    }

                    if (sig != "")
                    {
                        input += ",\"signature\" :" + sig;
                    }

                    foreach (var pair in map_param)
                    {
                        if (pair.Value != "" && (pair.Key != "sig" || pair.Key != "id" || pair.Key != "name"))
                        {
                            input += ", \"" + pair.Key + "\": \"" + pair.Value + "\"";
                        }
                    }
                    input += " } }";
                    int rc = OesisFramework.instance.Invoke(input, out json_out);
                }
            }
            cliResult = json_out;
            return;
        }
        private static void HandleCheckAV(IConsole console)
        {
            OesisAntimalware oesisAntimalware = OesisAntimalware.instance;
            string json_out;
            int rc = OesisFramework.instance.DetectAntimalwareProducts(out json_out);
            string output = "";
            if (rc >= 0)
            {
                dynamic jsonOut = JObject.Parse(json_out);
                var products = jsonOut.result.detected_products;
                JArray _products = new JArray();
                for (int i = 0; i < products.Count; i++)
                {
                    oesisAntimalware.signatureId = (int)products[i].signature;
                    JObject tmp = JObject.FromObject(new
                    {
                        signature = (int)products[i].signature,
                        sig_name = (string)products[i].sig_name,
                        version = oesisAntimalware.GetVersion(),
                        GetComponents = oesisAntimalware.GetComponents(),
                        IsAuthentic = oesisAntimalware.IsAuthentic(),
                        GetRealTimeProtectionState = oesisAntimalware.GetRealTimeProtectionState(),
                        GetDefinitionState = oesisAntimalware.GetDefinitionState(3),
                        GetLastScanTime = oesisAntimalware.GetLastScanTime("full"),
                        GetThreats = oesisAntimalware.GetThreats(),
                        GetScanState = oesisAntimalware.GetScanState()
                    });
                    _products.Add(tmp);
                }
                output = new JObject(new JProperty("Antimalware", _products)).ToString();
            }
            //Console.WriteLine(output);
            cliResult = output;
            return;
        }

        private static void HandleCheckVUL(IConsole console)
        {
            OesisVulnerabilityAndPatch oesisVulnerabilityAndPatch = OesisVulnerabilityAndPatch.instance;
            oesisVulnerabilityAndPatch.ConsumeOfflineVmodDatabase();
            oesisVulnerabilityAndPatch.LoadPatchDatabase();
            string json_out;
            int rc = OesisFramework.instance.DetectAllProducts(out json_out);
            string output = "";
            if (rc >= 0)
            {
                dynamic jsonOut = JObject.Parse(json_out);
                var products = jsonOut.result.detected_products;
                JArray _products = new JArray();
                for (int i = 0; i < products.Count; i++)
                {
                    oesisVulnerabilityAndPatch.signatureId = (int)products[i].signature;
                    JObject tmp = JObject.FromObject(new
                    {
                        signature = (int)products[i].signature,
                        sig_name = (string)products[i].sig_name,
                        version = oesisVulnerabilityAndPatch.GetVersion(),
                        GetProductPatchLevel = oesisVulnerabilityAndPatch.GetProductPatchLevel(),
                        GetProductVulnerability = oesisVulnerabilityAndPatch.GetProductVulnerability(),
                        GetRemediations = oesisVulnerabilityAndPatch.GetRemediations(),
                        GetLatestInstaller = oesisVulnerabilityAndPatch.GetLatestInstaller(),
                    });
                    _products.Add(tmp);
                }
                output = new JObject(new JProperty("VulnerabilityAndPatch", _products)).ToString();

            }
            //Console.WriteLine(output);
            cliResult = output;
            return;
        }

        private static void HandlePatchProduct(int sig, string location, int force_close, IConsole console)
        {
            if (!Directory.Exists(location))
            {
                Directory.CreateDirectory(location);
            }
            OesisVulnerabilityAndPatch oesisVulnerabilityAndPatch = OesisVulnerabilityAndPatch.instance;
            oesisVulnerabilityAndPatch.ConsumeOfflineVmodDatabase();
            oesisVulnerabilityAndPatch.LoadPatchDatabase();
            string json_out;

            location = oesisVulnerabilityAndPatch.FixPath(location);
            //string get_install_input = "{\"input\" : {\"method\" : 50300, \"signature\" : " + sig + ",\"path\" :" + "\"" + location + "\", \"download\": 1 }}";
            string json_in = "";
            Dictionary<string, object> input = new Dictionary<string, object>()
            {
                { "method", 50300 },
                { "signature", sig },
                { "path", location },
                { "download", 1 }
            };
            OesisUtils.CreateJsonIn(ref json_in, input);
            int rc = OesisFramework.instance.Invoke(json_in, out json_out);
            JObject result;
            dynamic jsonOut = JObject.Parse(json_out);
            if (rc < 0)
            {

                result = new JObject(jsonOut.error);
            }
            else
            {
                string path = jsonOut.result.path;
                oesisVulnerabilityAndPatch.signatureId = sig;

                result = JObject.FromObject(new
                {
                    sigID = sig,
                    results = oesisVulnerabilityAndPatch.InstallFromFiles(force_close, path),
                });

            }
            string output = new JObject(new JProperty("PathProduct", result)).ToString();
            //Console.WriteLine(output);
            cliResult = output;
            return;
        }

        private static void HandleDLP(string asc, string akl, int pid)
        {
            int setupMethodId;
            int manageMethodId;
            int getStateMethodId;
            string operation;
            string message;
            string confirm = "";
            
            string output = "";
            if (asc != "")
            {
                setupMethodId = 120010;
                manageMethodId = 120013;
                getStateMethodId = 120012;
                operation = asc;
                message = "A service will be installed and running processes will be injected with a DLL. Please confirm Yes/No [Y/N]? ";
                
            }
            else
            {
                setupMethodId = 120002;
                manageMethodId = 120001;
                getStateMethodId = 120004;
                operation = akl;
                message = "A service and driver will be installed. Please confirm Yes/No [Y/N]? ";
            }
            OesisDataLossProtection oesisDataLossProtection = OesisDataLossProtection.instance;
            JObject result = new JObject();
            if (operation.CompareTo("enable") == 0)
            {
                wait = true;
                Thread.Sleep(1000);
                Console.Write(message);
                confirm = Console.ReadLine();
                wait = false;
                if (confirm.ToLower().CompareTo("yes") != 0 && confirm.ToLower().CompareTo("y") != 0)
                {
                    return;
                }
            }
            else if (operation.CompareTo("disable") == 0)
            {
                manageMethodId = -1;
                operation = "";
                if (asc != "")
                {
                    setupMethodId = 120011;

                }
                else
                {
                    setupMethodId = 120003;
                }

            }
            else
            {
                return;
            }
            int rc = oesisDataLossProtection.ManageDLPModule(ref result, setupMethodId);
            if(rc >= 0 && manageMethodId > 0)
            {
                oesisDataLossProtection.ManageDLPModule(ref result, manageMethodId, operation);
                oesisDataLossProtection.GetDLPState(getStateMethodId, ref result);
            }
            output = result.ToString();
            cliResult = output;
            return;
        }

        private static void HandleRemoveProduct(int sig, string type)
        {
            //string json_in = "{\"input\": {\"signature\":" + sig + ", \"method\" :" + 40000 + ", \"type\": \"" + type + "\"} }";
            if (type == "")
            {
                type = "native";
            }

            string json_in = "";
            Dictionary<string, object> input = new Dictionary<string, object>()
            {
                { "signature", sig },
                { "method", 40000 },
                { "type", type }
            };
            OesisUtils.CreateJsonIn(ref json_in, input);
            string json_out;
            int rc = OesisFramework.instance.Invoke(json_in, out json_out);
            //Console.WriteLine(output);
            cliResult = json_out;
            return;
        }

        // helpers

        private static Command WithHandler(this Command command, string methodName)
        {
            var method = typeof(OesisCommand).GetMethod(methodName, BindingFlags.NonPublic | BindingFlags.Static);
            var handler = CommandHandler.Create(method!);
            command.Handler = handler;
            return command;
        }
    }
}
