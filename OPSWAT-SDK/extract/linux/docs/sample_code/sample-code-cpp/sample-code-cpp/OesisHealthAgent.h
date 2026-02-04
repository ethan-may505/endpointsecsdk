#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisHealthAgent : public OesisGenericProduct, public Singleton <OesisHealthAgent>
{
public:
	OesisHealthAgent();
	int GetAgentState(string input, wstring& json_out);
	~OesisHealthAgent();
};
