#include "OesisFramework.h"
#include "OesisAntimalwareProduct.h"
#include "OesisDataLossProtection.h"
#include "OesisDeviceInfo.h"
#include "OesisGenericProduct.h"
#include "OesisVulnerabilityAndPatch.h"
#include "OesisUtils.h"
#include "args.hxx"

#include <clocale>
#include <locale>
#include <future>

namespace
{
    namespace OesisCommand
    {
        class Event
        {
        public:
            Event(): is_set{ false }
            {
            }

            void set()
            {
                unique_lock<std::mutex> lock(mutex);
                is_set = true;
                cond_var.notify_all();
            }

            void wait()
            {
                unique_lock<std::mutex> lock(mutex);
                cond_var.wait(lock, [this]() { return is_set; });
            }

        private:
            bool is_set;
            std::mutex mutex;
            std::condition_variable cond_var;
        };

        bool wait = false;
        Event variable_initialized;
        bool g_autoExit;

        template <typename T>
        struct Param
        {
            typedef map<string, args::ValueFlag<T>*> map_flag;
        };

        void CreateMap(map<string, int>& mapMethod)
        {
            //OESIS Core
            mapMethod["DetectProducts"] = WAAPI_MID_DETECT_PRODUCTS;
            mapMethod["DiscoverProducts"] = WAAPI_MID_DISCOVER_PRODUCTS;
            mapMethod["GetOSInfo"] = WAAPI_MID_GET_OS_INFO;
            mapMethod["GetLicenseInfo"] = WAAPI_MID_GET_LICENSE_INFO;
            mapMethod["UpdateLicenseInfo"] = WAAPI_MID_UPDATE_LICENSE_INFO;
            mapMethod["GetDeviceIdentity"] = WAAPI_MID_GET_DEVICE_IDENTITY;
            mapMethod["QueryAsyncResults"] = WAAPI_MID_QUERY_ASYNC_RESULTS;
            mapMethod["GetActiveUserInfo"] = WAAPI_MID_GET_ACTIVE_USER_INFO;
            mapMethod["GetVersion"] = WAAPI_MID_COMMON_GET_VERSION;
            mapMethod["GetRunningState"] = WAAPI_MID_GET_RUNNING_STATE;
            mapMethod["Run"] = WAAPI_MID_COMMON_RUN;
            mapMethod["TerminateProcesses"] = WAAPI_MID_COMMON_TERMINATE;
            mapMethod["GetInstallationDirectories"] = WAAPI_MID_COMMON_GET_INSTALL_DIR;
            mapMethod["GetComponents"] = WAAPI_MID_COMMON_GET_COMPONENTS;
            mapMethod["GetUninstallString"] = WAAPI_MID_COMMON_GET_UNINSTALL_STRING;
            mapMethod["ManageLabels"] = WAAPI_MID_COMMON_MANAGE_LABELS;
            mapMethod["IsAuthentic"] = WAAPI_MID_COMMON_IS_AUTHENTIC;
            mapMethod["GetProductInfo"] = WAAPI_MID_COMMON_GET_PRODUCT_INFO;
            //Antimalware
            mapMethod["GetRealTimeProtectionState"] = WAAPI_MID_GET_RTP_STATE;
            mapMethod["EnableRTP"] = WAAPI_MID_ENABLE_RTP;
            mapMethod["GetDefinitionState"] = WAAPI_MID_GET_DEF_STATE;
            mapMethod["UpdateDefinitions"] = WAAPI_MID_UPDATE_DEFINITIONS;
            mapMethod["GetThreats"] = WAAPI_MID_GET_THREATS;
            mapMethod["GetLastScanTime"] = WAAPI_MID_GET_LAST_SCAN_TIME;
            mapMethod["Scan"] = WAAPI_MID_SCAN;
            mapMethod["GetScanState"] = WAAPI_MID_GET_SCAN_STATE;
            //Firewall
            mapMethod["GetFirewallState"] = WAAPI_MID_GET_FIREWALL_STATE;
            mapMethod["SetFirewallState"] = WAAPI_MID_SET_FIREWALL_STATE;
            //Antiphishing
            mapMethod["GetAntiphishingState"] = WAAPI_MID_GET_ANTIPHISHING_STATE;
            //DeviceInfo
            mapMethod["GetPCModel"] = WAAPI_MID_GET_PC_MODEL;
            mapMethod["GetCpuAndRamInfo"] = WAAPI_MID_GET_PC_CPU_RAM;
            mapMethod["GetPCComponents"] = WAAPI_MID_GET_PC_COMPONENTS;
            mapMethod["GetDiskSpace"] = WAAPI_MID_GET_PC_DISK_SPACE;
            mapMethod["GetDevicePasswordProtectionState"] = WAAPI_MID_GET_DEVICE_PASSWORD_PROTECTION_STATE;
            mapMethod["IsCurrentDeviceVirtual"] = WAAPI_MID_IS_CURRENT_DEVICE_VIRTUAL;
            mapMethod["IsCurrentDeviceVirtual"] = WAAPI_MID_GET_SYSTEM_VOLUME;
            //Backup
            mapMethod["GetBackupState"] = WAAPI_MID_GET_BACKUP_STATE;
            //Encrypt
            mapMethod["GetEncryptionState"] = WAAPI_MID_GET_ENCRYPTION_STATE;
            //VirtualMachine
            mapMethod["GetAvailableVMs"] = WAAPI_MID_GET_AVAILABLE_VMS;
            mapMethod["ListSnapshots"] = WAAPI_MID_LIST_SNAPSHOTS;
            mapMethod["ManageVM"] = WAAPI_MID_MANAGE_VM;
            mapMethod["GetVMState"] = WAAPI_MID_GET_VM_STATE;

        }

        int CallMethodWithParam(OesisFramework* oesis, vector<args::Base*> children, Param<string>::map_flag stringFlags, Param<int>::map_flag intFlags, Param<bool>::map_flag boolFlags, wstring& json_out)
        {
            string id;
            map<string, int> mapMethod;
            CreateMap(mapMethod);
            string input = "{ \"input\": { ";
            bool isMethod = false;
            if (intFlags.find("methodId")->second->Matched())
            {
                id = std::to_string(intFlags.find("methodId")->second->Get());
                input = input + "\"method\": " + id;
                isMethod = true;
            }
            else
            {
                string methodName = stringFlags.find("methodName")->second->Get();
                if (mapMethod.find(methodName) != mapMethod.end()) {
                    id = std::to_string(mapMethod[methodName]);
                    input = input + "\"method\": " + id;
                    isMethod = true;
                }
            }
            if (isMethod)
            {
                if (id == "50300" || id == "50301" || id == "50500" ||
                    id == "50501" || id == "50502" || id == "50503" ||
                    id == "50505" || id == "50509" || id == "50550")
                {
                    OesisVulnerabilityAndPatch* oesisVulnerabilityAndPatch = OesisVulnerabilityAndPatch::instance();
                    oesisVulnerabilityAndPatch->ConsumeOfflineVmodDatabase(json_out);
                    oesisVulnerabilityAndPatch->LoadPatchDatabase(json_out);
                }
                //auto children = params.Children();
                for (int i = 0; i < children.size(); i++)
                {
                    if (children[i]->Matched())
                    {
                        string key = children[i]->GetKey();
                        if (stringFlags.count(key))
                        {
                            auto value = stringFlags.find(key)->second;
                            input += ", \"" + key + "\": \"" + value->Get() + "\"";
                        }
                        else
                        {
                            auto value = intFlags.find(key)->second;
                            input += ", \"" + key + "\": " + to_string(value->Get());
                        }
                    }
                }
                input += " } }";
                wstring json_in = OesisUtils::utf8_decode(input);
                oesis->Invoke(json_in, json_out);
                return 0;
            }
            return -1;
        }

        int CheckAVCLI(OesisFramework* oesis, wstring& json_out)
        {
            OesisAntimalwareProduct* oesisAntimalware = OesisAntimalwareProduct::instance();
            string output;
            int rc = oesis->DetectProducts(json_out, 5);
            json jsonOut;
            json tmp;
            if (WAAPI_SUCCESS(OesisUtils::GetJsonValues(tmp, rc, json_out, { "detected_products" })))
            {
                tmp = tmp["detected_products"];
                if (tmp.size() > 0)
                {
                    for (json::iterator it = tmp.begin(); it != tmp.end(); ++it)
                    {
                        json js;
                        auto sigId = it.value()["signature"].get<int>();
                        auto sigName = it.value()["sig_name"].get<string>();
                        string sigIdStr = to_string(sigId);
                        oesisAntimalware->SetSignatureId(sigId);
                        js["sigId"] = sigId;
                        js["sigName"] = sigName;
                        js["version"] = oesisAntimalware->GetVersion();
                        js["GetComponents"] = oesisAntimalware->GetComponents();
                        js["IsAuthentic"] = oesisAntimalware->IsAuthentic();
                        js["GetRealTimeProtectionState"] = oesisAntimalware->GetRealTimeProtectionState();
                        js["GetDefinitionState"] = oesisAntimalware->GetDefinitionState();
                        js["GetLastScanTime"] = oesisAntimalware->GetLastScanTime();
                        js["GetThreats"] = oesisAntimalware->GetThreats();
                        js["GetScanState"] = oesisAntimalware->GetScanState();
                        jsonOut.push_back(js);
                    }
                }
            }
            output = jsonOut.dump(4);
            json_out = OesisUtils::utf8_decode(output);
            return 0;
        }

        int CheckVULCLI(OesisFramework* oesis, wstring& json_out)
        {
            string output;
            json jsonOut;
            OesisVulnerabilityAndPatch* oesisVulnerabilityAndPatch = OesisVulnerabilityAndPatch::instance();

            do
            {
                int rc = oesisVulnerabilityAndPatch->ConsumeOfflineVmodDatabase(json_out);
                if (WAAPI_SUCCESS(rc))
                {
                    rc = oesisVulnerabilityAndPatch->LoadPatchDatabase(json_out);
                }
                if (WAAPI_FAILED(rc))
                {
                    jsonOut = json::parse(OesisUtils::utf8_encode(json_out));
                    jsonOut = jsonOut["error"];
                    break;
                }
                rc = oesis->DetectProducts(json_out);
                json tmp;
                if (WAAPI_SUCCESS(OesisUtils::GetJsonValues(tmp, rc, json_out, { "detected_products" })))
                {
                    tmp = tmp["detected_products"];
                    if (tmp.size() > 0)
                    {
                        for (json::iterator it = tmp.begin(); it != tmp.end(); ++it)
                        {
                            json js;
                            auto sigId = it.value()["signature"].get<int>();
                            auto sigName = it.value()["sig_name"].get<string>();
                            string sigIdStr = to_string(sigId);
                            oesisVulnerabilityAndPatch->SetSignatureId(sigId);
                            js["sigId"] = sigId;
                            js["sigName"] = sigName;
                            js["version"] = oesisVulnerabilityAndPatch->GetVersion();
                            js["GetProductPatchLevel"] = oesisVulnerabilityAndPatch->GetProductPatchLevel();
                            js["GetProductVulnerability"] = oesisVulnerabilityAndPatch->GetProductVulnerability();
                            js["GetRemediations"] = oesisVulnerabilityAndPatch->GetRemediations();
                            js["GetLatestInstaller"] = oesisVulnerabilityAndPatch->GetLatestInstaller();
                            jsonOut.push_back(js);
                        }
                    }
                }
            } while (false);
            output = jsonOut.dump(4);
            json_out = OesisUtils::utf8_decode(output);
            return 0;
        }

        int PatchProductCLI(OesisFramework* oesis, int sigId, string location, int force_close, wstring& json_out)
        {
#ifdef _WIN32
            string output;
            json jsonOut;
            OesisVulnerabilityAndPatch* oesisVulnerabilityAndPatch = OesisVulnerabilityAndPatch::instance();
            do
            {
                int rc = oesisVulnerabilityAndPatch->ConsumeOfflineVmodDatabase(json_out);
                if (WAAPI_SUCCESS(rc))
                {
                    rc = oesisVulnerabilityAndPatch->LoadPatchDatabase(json_out);
                }
                if (WAAPI_FAILED(rc))
                {
                    jsonOut = json::parse(OesisUtils::utf8_encode(json_out));
                    jsonOut = jsonOut["error"];
                    break;
                }
                oesisVulnerabilityAndPatch->SetSignatureId(sigId);
                if (CreateDirectory(OesisUtils::utf8_decode(location).c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
                {
                    std::replace(location.begin(), location.end(), '\\', '/');
                    rc = oesisVulnerabilityAndPatch->GetLatestInstaller(json_out, 1, location);
                    jsonOut = json::parse(OesisUtils::utf8_encode(json_out));
                    if (WAAPI_FAILED(rc))
                    {
                        jsonOut = jsonOut["error"];
                        break;
                    }
                    location = jsonOut["result"]["path"];
                    replace(location.begin(), location.end(), '\\', '/');
                    jsonOut = oesisVulnerabilityAndPatch->InstallFromFile(location, force_close);
                }
                else {
                    //Get error when using CreateDirectory API
                    LPSTR messageBuffer = nullptr;
                    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
                    std::string message(messageBuffer, size);
                    LocalFree(messageBuffer);
                    json_out = OesisUtils::utf8_decode(message);
                    return -1;
                }
            } while (false);
            output = jsonOut.dump(4);
            json_out = OesisUtils::utf8_decode(output);
#else
            json_out = L"This module don't support on this OS.";
#endif
            return 0;
        }

        int RemoveProductCLI(OesisFramework* oesis, int sigId, string type, wstring& json_out) {
            wstring json_in = L"";
            map<string, string> param = {
                {"method", to_string(WAAPI_MID_COMMON_UNINSTALL)},
                {"signature", to_string(sigId)},
                {"type", type}
            };
            int rc = oesis->instance()->Invoke(param, json_out);
            return rc;
        }

        int DLPModuleCLI(OesisFramework* oesis, string module, string opeation, wstring& json_out)
        {
#ifdef _WIN32
            string setupMethodId;
            string manageMethodId;
            string getStateMethodId;
            string operation = operation;
            string message;
            string confirm = "";

            string output = "";
            if (module == "asc")
            {
                setupMethodId = "120010";
                manageMethodId = "120013";
                getStateMethodId = "120012";
                message = "A service will be installed and running processes will be injected with a DLL. Please confirm Yes/No [Y/N]? ";

            }
            else
            {
                setupMethodId = "120002";
                manageMethodId = "120001";
                getStateMethodId = "120004";
                message = "A service and driver will be installed. Please confirm Yes/No [Y/N]? ";
            }
            OesisDataLossProtection* oesisDataLossProtection = OesisDataLossProtection::instance();
            if (operation.compare("disable") == 0)
            {
                manageMethodId = "";
                operation = "";
                if (module == "asc")
                {
                    setupMethodId = "120011";

                }
                else
                {
                    setupMethodId = "120003";
                }
            }
            int rc = oesisDataLossProtection->ManageDLPModule(json_out, setupMethodId);
            if (rc >= 0 && manageMethodId != "")
            {
                if (oesisDataLossProtection->ManageDLPModule(json_out, manageMethodId, opeation))
                {
                    if (oesisDataLossProtection->ManageDLPModule(json_out, getStateMethodId))
                    {
                        json jsonOut;
                        OesisUtils::GetJsonValues(jsonOut, rc, json_out, { "state", "enabled" });
                        output = jsonOut.dump(4);
                        json_out = OesisUtils::utf8_decode(output);
                    }
                }
            }
#else
            json_out = L"This module not support on this OS";
#endif
            return 0;
        }

        int ParseCommand(int argc, char** argv, wstring& json_out)
        {
            string input;
            args::ArgumentParser parser("This is a CLI for sample code.");
            args::Group group(parser, "All command used by sample code", args::Group::Validators::Xor);
            args::Command CallMethod(group, "call-method", "Call specific method");
            args::Group method(CallMethod, "Name/ID of method", args::Group::Validators::Xor);
            args::ValueFlag<string> methodInput(method, "", "Call specific method from input file", "file", { "file" }, args::Options::Global);
            args::ValueFlag<string> methodName(method, "", "The method name of the product", "method", { "name" }, args::Options::Global);
            args::ValueFlag<int> methodId(method, "", "The method id of the product", "method", { "id" }, args::Options::Global);
            args::Group params(CallMethod, "Param for method", args::Group::Validators::DontCare);
            args::ValueFlag<int> sig(params, "", "The signature id of the product", "signature", { "sig" }, args::Options::Global);
            args::ValueFlag<int> category(params, "", "The category id of the product", "category", { "category" }, args::Options::Global);
            args::ValueFlag<string> scanType(params, "", "The type of scan to get the time", "scan_type", { "scan_type" }, args::Options::Global);
            args::ValueFlag<string> path(params, "", "The full path to a file, or folder", "path", { "path" }, args::Options::Global);
            args::ValueFlag<string> clean(params, "", "Clean threats detected during the scan", "clean", { "clean" }, args::Options::Global);
            args::ValueFlag<int> timeFrame(params, "", "The timeframe in days used to determine if the update is recent", "timeframe", { "timeframe" }, args::Options::Global);
            args::ValueFlag<string> operation(params, "", "The operation to be perform", "operation", { "operation" }, args::Options::Global);
            args::ValueFlag<string> password(params, "", "The password required by the product to modify the application state", "password", { "password" }, args::Options::Global);
            args::ValueFlag<string> user(params, "", "The user required by the product to modify the application state", "user", { "user" }, args::Options::Global);
            args::ValueFlag<string> vm_id(params, "", "The identification of VM that was recieved from the call.", "vm_id", { "vm_id" }, args::Options::Global);
            args::ValueFlag<string> token(params, "", "Token string to download files..", "token", { "token" }, args::Options::Global);
            args::ValueFlag<string> source_file(params, "", "Input database if to be cosumed from a file location..", "dat_input_source_file", { "source_file" }, args::Options::Global);
            args::ValueFlag<string> checksum_file(params, "", "Input database if to be cosumed from a file location..", "dat_input_checksum_file", { "checksum_file" }, args::Options::Global);
            args::ValueFlag<int> timeout(params, "", "A timeout value in seconds that can be set to this api call.", "timeout", { "timeout" }, args::Options::Global);
            args::ValueFlag<int> os_id(params, "", "MDES SDK identifier of the OS.", "os_id", { "os_id" }, args::Options::Global);
            args::ValueFlag<int> tolerance(params, "", "A tolerance factor that can be used to loosen the 'is_current' metric.", "tolerance", { "tolerance" }, args::Options::Global);
            args::ValueFlag<int> online(params, "", "A timeout value in seconds that can be set to this api call.", "online", { "online" }, args::Options::Global);
            args::ValueFlag<string> type(params, "auto/native", "Type remove product native/auto", "type", { "type" }, args::Options::Global);
            args::ValueFlag<int> pid(params, "", "PID will be show/hide in AntiScreenCapture", "pid", { "pid" }, args::Options::Global);
            //CheckAV
            args::Command CheckAV(group, "check-av", "Check Antivirus products");
            //CheckVUL
            args::Command CheckVUL(group, "check-vuln", "Check Vulnerability products");
            //PatchProduct
            args::Command PatchProduct(group, "patch-product", "Download latest version and install product");
            args::ValueFlag<string> location(PatchProduct, "", "The location to download installer", "path", { "installer_download_location" }, args::Options::Global);
            args::ValueFlag<int> force_close(PatchProduct, "", "Whether to close running product or not before installing. Value 0 will not close blocking processes, 1 will try to close blocking processes.", "force_close", { "force_close" }, args::Options::Global);
            PatchProduct.Add(sig);
            //RemoveProduct
            args::Command RemoveProduct(group, "remove-product", "Unistall product");
            RemoveProduct.Add(sig);
            RemoveProduct.Add(type);
            //DLP
            args::Command DLP(group, "dlp", "DLP module");
            args::ValueFlag<string> akl(DLP, "enable/disable", "enable/disable AntiKeylogger", "akl", { "akl" }, args::Options::Global);
            args::ValueFlag<string> asc(DLP, "enable/disable/show/hide", "enable/disable/show/hide AntiScreenCapture", "asc", { "asc" }, args::Options::Global);
            DLP.Add(pid);
            args::HelpFlag help(parser, "help", "Display this help menu", { 'h', "help" });

            Param<string>::map_flag  stringFlags = {
                {"methodName", &methodName},
                { "scan_type", &scanType},
                { "path", &path},
                { "clean", &clean},
                { "operation", &operation},
                { "password", &password},
                { "user", &user}
            };

            Param<int>::map_flag intFlags = {
                {"methodId", &methodId},
                { "signature", &sig},
                { "category", &category},
                { "timeFrame", &timeFrame}
            };

            Param<bool>::map_flag boolFlags = {

            };

            try
            {
                parser.ParseCLI(argc, argv);
                string output;
                wstring pass_key = L"";
                pass_key = OesisUtils::ReadFileContentIntoWString(OesisUtils::GetCurrentFolderPath() + L"/pass_key.txt");
                OesisFramework* oesis = OesisFramework::instance();
                int rc = oesis->Setup(pass_key, json_out);
                if (WAAPI_SUCCESS(rc))
                {
                    json_out = L"";
                    if (CallMethod)
                    {
                        map<string, int> mapMethod;
                            string id;
                            string input = "";
                            wstring json_in = L"";
                            if (methodInput)
                            {
                                if (params.MatchedChildren())
                                {
                                    cout << "Using input file - do not input param" << endl;
                                    cout << parser;
                                }
                                else
                                {
                                    wstring filePath = OesisUtils::utf8_decode(args::get(methodInput));
                                    json_in = OesisUtils::ReadFileContentIntoWString(filePath);
                                    oesis->Invoke(json_in, json_out);
                                }
                            }
                            else {
                                if (WAAPI_FAILED(CallMethodWithParam(oesis, params.Children(), stringFlags, intFlags, boolFlags, json_out)))
                                {
                                    oesis->Teardown();
                                    return -1;
                                }
                            }
                    }
                    if (CheckAV)
                    {
                        CheckAVCLI(oesis, json_out);
                    }
                    if (CheckVUL)
                    {
                        CheckVULCLI(oesis, json_out);
                    }
                    if (PatchProduct) {
#ifdef _WIN32
                        if (sig && location) {
                            int sigId = args::get(sig);
                            string download_location = args::get(location);
                            int force = 0;
                            if (force_close)
                            {
                                force = args::get(force_close);
                            }
                            PatchProductCLI(oesis, sigId, download_location, force, json_out);
                        }
                        else {
                            std::cerr << parser;
                            return -1;
                        }
#else
                        json_out = L"This module don't support on this OS";
#endif
                    }
                    if (RemoveProduct)
                    {
                        if (sig)
                        {
                            int sigId = args::get(sig);
                            string strType = "native";
                            if (type)
                            {
                                strType = args::get(type);
                            }
                            RemoveProductCLI(oesis, sigId, strType, json_out);
                        }
                        else
                        {
                            std::cerr << parser;
                            return -1;
                        }
                    }
                    if (DLP)
                    {
#ifdef _WIN32                      
                        if (asc || akl)
                        {
                            string operation;
                            string module;
                            if (asc)
                            {
                                module = "asc";
                                operation = args::get(asc);
                            }
                            else if (akl)
                            {
                                module = "akl";
                                operation = args::get(akl);
                            }
                            std::transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
                            if (operation.compare("enable") == 0) 
                            {
                                OesisCommand::wait = true;
                                variable_initialized.set();
                                string confirm;
                                cout << "A service and driver will be installed, please confirm yes/no [Y/N]? ";
                                if (cin >> confirm) 
                                {
                                    OesisCommand::wait = false;
                                    variable_initialized.set();
                                    std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
                                    if (confirm.compare("y") == 0 || confirm.compare("yes") == 0)
                                    {
                                        DLPModuleCLI(oesis, module, operation, json_out);
                                    }
                                    else
                                    {
                                        return -1;
                                    }
                                }
                            }
                            else
                            {
                                DLPModuleCLI(oesis, module, operation, json_out);
                            }
                        }
                        else
                        {
                            std::cerr << parser;
                            return -1;
                        }
#else
                        json_out = L"This module don't support on this OS";
#endif
                    }
                    oesis->Teardown();
                }
            }
            catch (args::Help)
            {
                std::cout << parser;
                return -1;
            }
            catch (args::Error e)
            {
                std::cerr << e.what() << std::endl;
                std::cerr << parser;
                return -1;
            }

            return 0;
        }

        bool getWaitVariable()
        {
            variable_initialized.wait();
            return wait;
        }

//        int filter(unsigned int code, struct _EXCEPTION_POINTERS* ep)
//        {
//            std::wcout << L"\nError during setup. Did you include your license file in the package?";
//            if (code == EXCEPTION_ACCESS_VIOLATION) {
//                return EXCEPTION_EXECUTE_HANDLER;
//            }
//            else {
//                return EXCEPTION_CONTINUE_SEARCH;
//            };
//        }

        void showRunningStatus(unsigned int count)
        {
            std::wstring temp = L"RUNNING";
            for (unsigned int i = 0; i < 5; ++i)
                temp += (i < (count % 5)) ? L'.' : L' ';
            std::wcout << temp << L"\r" << std::flush;
        }
        void clearRunningStatus()
        {
            std::wcout << L"\r            \r" << std::flush;
        }

        int main(int argc, char** argv)
        {
            OesisCommand::variable_initialized.set();
            // show help in case of failure because someone might not know what they are doing
            int ret = 0;
            wstring output;
            std::future<wstring> f = std::async(std::launch::async, [&ret, &argc, argv, &output]()
            {
                if (WAAPI_FAILED(OesisCommand::ParseCommand(argc, argv, output)))
                {
                    ret = 1;
                    return wstring(L"\nRun failed\n");
                }
                else
                {
                    ret = 0;
                    return output;
                    //return wstring(L"\nDiagnose complete, check results file for details.\n");
                }
            });

            int dotCount = 0;
            std::future_status fstatus;
            do
            {
                fstatus = f.wait_for(std::chrono::seconds(1));
                if (fstatus == std::future_status::deferred || fstatus == std::future_status::timeout)
                {
                    if (!OesisCommand::getWaitVariable())
                    {
                        OesisCommand::showRunningStatus(dotCount++);
                    }
                }
                else if (fstatus == std::future_status::ready)
                {
                    OesisCommand::clearRunningStatus();
                    cout << OesisUtils::utf8_encode(output);

                }
            } while (fstatus != std::future_status::ready);

            return ret;
        }
    }
}
