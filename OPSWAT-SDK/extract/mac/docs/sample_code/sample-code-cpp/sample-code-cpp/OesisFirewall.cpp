#include "OesisFirewall.h"


OesisFirewall::OesisFirewall()
{
    this->oesis = OesisFramework::instance();
}

OesisFirewall::~OesisFirewall(){}

int OesisFirewall::GetFirewallState(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_GET_FIREWALL_STATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}


int OesisFirewall::SetFirewallState(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_SET_FIREWALL_STATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}
