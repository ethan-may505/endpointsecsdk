#include "OesisPatchManagement.h"


OesisPatchManagement::OesisPatchManagement()
{
    this->oesis = OesisFramework::instance();
}

OesisPatchManagement::~OesisPatchManagement(){}

int OesisPatchManagement::GetAgentState(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_GET_AGENT_STATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisPatchManagement::SetAgentState(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_SET_AGENT_STATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisPatchManagement::GetMissingPatches(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_GET_MISSING_PATCHES)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisPatchManagement::InstallMissingPatches(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_INSTALL_MISSING_PATCHES)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}

int OesisPatchManagement::GetInstalledPatches(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_GET_INSTALLED_PATCHES)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}
