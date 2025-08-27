#pragma once

#include "wa_api.h"
#include "OesisUtils.h"
#include "oesis_utils_singleton.h"

class OesisFramework : public Singleton<OesisFramework>
{
public:
    OesisFramework();
    int Setup(wstring passkey_string, wstring& config);
    void Teardown();
    int Invoke(wstring json_in, wstring& json_out);
    int Invoke(wstring& json_out, int methodId, string signature = "");
    int Invoke(map<string, string> param, wstring& json_out);
    int DetectProducts(wstring& json_out, int category = 0, int* categories = {});
    int GetOSInfo(string input, wstring& json_out);
    int GetLicenseInfo(string input, wstring& json_out);
    int UpdateLicenseInfo(string input, wstring& json_out);
    int GetDeviceIdentity(string input, wstring& json_out);
    int QueryAsyncResults(string input, wstring& json_out);
    int GetActiveUserInfo(string input, wstring& json_out);
    ~OesisFramework();
protected:
    bool m_Initialized;

};
