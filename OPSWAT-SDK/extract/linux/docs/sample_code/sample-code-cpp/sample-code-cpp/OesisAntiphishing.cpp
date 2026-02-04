#include "OesisAntiphishing.h"

OesisAntiphishing::OesisAntiphishing()
{
    this->oesis = OesisFramework::instance();
}

OesisAntiphishing::~OesisAntiphishing() {}

int OesisAntiphishing::GetAntiphishingState(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_GET_ANTIPHISHING_STATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}


