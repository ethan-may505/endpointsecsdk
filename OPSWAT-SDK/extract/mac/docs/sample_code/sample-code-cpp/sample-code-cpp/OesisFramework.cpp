#define _CRT_SECURE_NO_WARNINGS
#include "OesisFramework.h"

OesisFramework::OesisFramework()
{
}

int OesisFramework::Setup(wstring passkey_string, wstring& config)
{
    const wstring json_config = L"{ \"config\" : { \"passkey_string\": \"" + passkey_string + L"\", \"enable_pretty_print\": true, \"silent_mode\": true } }";

    wa_wchar* json_out = NULL;
    int rc = wa_api_setup(json_config.c_str(), &json_out);

    if (WAAPI_SUCCESS(rc))
    {
        config = wstring(json_out);
    }
    else
    {
        if (json_out != NULL)
        {
            config = wstring(json_out);
        }
        else
        {
            config = L"Error on setup. Return code: " + to_wstring(rc);
        }
    }
    
    return rc;
}

void OesisFramework::Teardown()
{
    wa_api_teardown();
}

int OesisFramework::Invoke(wstring json_in, wstring& json_out)
{
    wa_wchar* json_out_tmp = NULL;
    int rc = wa_api_invoke(json_in.c_str(), &json_out_tmp);
    json_out = json_out_tmp;

    return rc;
}

int OesisFramework::Invoke(wstring& json_out, int methodId, string signature)
{
    wa_wchar* json_out_tmp = NULL;
    wstring json_in = OesisUtils::CreateJsonIn(methodId, signature);
    int rc = wa_api_invoke(json_in.c_str(), &json_out_tmp);
    json_out = json_out_tmp;
    return rc;
}

int OesisFramework::Invoke(map<string, string> param, wstring& json_out)
{
    wstring json_in = L"";
    wa_wchar* json_out_tmp = NULL;
    OesisUtils::CreateJsonIn(json_in, param);
    int rc = wa_api_invoke(json_in.c_str(), &json_out_tmp);
    json_out = json_out_tmp;
    return rc;
}

int OesisFramework::DetectProducts(wstring& json_out, int category, int* categories)
{
    wstring json_in = L"";
    map<string, string> input = {
        {"method", to_string(WAAPI_MID_DETECT_PRODUCTS)}
    };
    int arrSize = 0;
    if (categories != NULL) {
        arrSize = sizeof(categories)/sizeof(*categories);
    }
    if (arrSize > 0)
    {
        input["categories"] += to_string(categories[0]);
        for (int i = 1; i < arrSize; ++i)
        {
            input["categories"] += ", " + to_string(categories[i]);
        }
    }
    else if (category > 0)
    {
        input["category"] = to_string(category);
    }
    OesisUtils::CreateJsonIn(json_in, input);
    int rc = Invoke(json_in, json_out);
    return rc;
}

int OesisFramework::GetOSInfo(string input, wstring& json_out)
{
    wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_GET_OS_INFO, input);
    int rc = Invoke(json_in, json_out);
    return rc;
}

int OesisFramework::GetLicenseInfo(string input, wstring& json_out)
{
    wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_GET_LICENSE_INFO, input);
    int rc = Invoke(json_in, json_out);
    return rc;
}

int OesisFramework::UpdateLicenseInfo(string input, wstring& json_out)
{
    wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_UPDATE_LICENSE_INFO, input);
    int rc = Invoke(json_in, json_out);
    return rc;
}

int OesisFramework::GetDeviceIdentity(string input, wstring& json_out)
{
    wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_GET_DEVICE_IDENTITY, input);
    int rc = Invoke(json_in, json_out);
    return rc;
}

int OesisFramework::QueryAsyncResults(string input, wstring& json_out)
{
    wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_QUERY_ASYNC_RESULTS, input);
    int rc = Invoke(json_in, json_out);
    return rc;
}

int OesisFramework::GetActiveUserInfo(string input, wstring& json_out)
{
    wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_GET_ACTIVE_USER_INFO, input);
    int rc = Invoke(json_in, json_out);
    return rc;
}


OesisFramework::~OesisFramework()
{

}
