#include "OesisGenericProduct.h"

#include <iostream>
#include <sstream>

OesisGenericProduct::OesisGenericProduct()
{
    signature_id = 0;
    product_id = 0;
    vendor_id = 0;
    memset(categories, 0, 20 * sizeof(int));
    signature_name = "";
    product_name = "";
    vendor_name = "";
    oesis = OesisFramework::instance();
}

void OesisGenericProduct::SetSignatureId(int sig)
{
    this->signature_id = sig;
}

int OesisGenericProduct::GetVersion(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_GET_VERSION)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::GetRunningState(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_GET_RUNNING_STATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::Run(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_RUN)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::TerminateProcesses(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_TERMINATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::GetInstallationDirectories(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_GET_INSTALL_DIR)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::GetComponents(wstring& json_out, bool include_services)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_GET_COMPONENTS)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::GetUninstallString(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_GET_UNINSTALL_STRING)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::ManageLabels(wstring& json_out, int labels[10], bool reset)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_MANAGE_LABELS)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::IsAuthentic(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_IS_AUTHENTIC)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisGenericProduct::GetProductInfo(wstring& json_out, bool run_detection)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_GET_PRODUCT_INFO)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

string OesisGenericProduct::GetVersion()
{
    wstring json_out;
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_GET_VERSION)},
        {"signature", to_string(this->signature_id)}
    };
    int rc = oesis->Invoke(param, json_out);
    string version = "";
    if (WAAPI_SUCCESS(rc))
    {
        string str = OesisUtils::utf8_encode(json_out);
        auto obj = json::parse(str);
        if (OesisUtils::CheckJsonKey(obj, "result") && OesisUtils::CheckJsonKey(obj["result"], "version"))
        {
            version = obj["result"]["version"];
        }
    }
    return version;
}

json OesisGenericProduct::IsAuthentic()
{
    wstring json_out;
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_IS_AUTHENTIC)},
        {"signature", to_string(this->signature_id)}
    };
    int rc =  oesis->Invoke(param, json_out);
    json js;
    if (WAAPI_SUCCESS(rc))
    {
        string str = OesisUtils::utf8_encode(json_out);
        auto obj = json::parse(str);
        if (OesisUtils::CheckJsonKey(obj, "result") && OesisUtils::CheckJsonKey(obj["result"], "authentic"))
        {
            js["authentic"] = obj["result"]["authentic"];
            js["details"] = obj["result"]["details"];
        }
    }
    return js;
}

json OesisGenericProduct::GetComponents()
{
    wstring json_out;
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_COMMON_GET_COMPONENTS)},
        {"signature", to_string(this->signature_id)}
    };
    int rc = oesis->Invoke(param, json_out);
    json js;
    if (WAAPI_SUCCESS(rc))
    {
        string str = OesisUtils::utf8_encode(json_out);
        auto obj = json::parse(str);
        if (OesisUtils::CheckJsonKey(obj, "result") && OesisUtils::CheckJsonKey(obj["result"], "components"))
        {
            js["components"] = obj["result"]["components"];
        }
    }
    return js;
}	
