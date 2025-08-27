#include "OesisHealthAgent.h"

OesisHealthAgent::OesisHealthAgent(){
    this->oesis = OesisFramework::instance();
}

int OesisHealthAgent::GetAgentState(string input, wstring& json_out)
{
    return oesis->Invoke(json_out, WAAPI_MID_GET_AGENT_STATE, to_string(this->signature_id));;
}

OesisHealthAgent::~OesisHealthAgent(){}
