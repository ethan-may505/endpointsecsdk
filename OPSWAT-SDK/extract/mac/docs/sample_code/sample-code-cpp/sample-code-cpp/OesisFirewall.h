#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisFirewall : public OesisGenericProduct, public Singleton <OesisFirewall>
{
public:
	int GetFirewallState(wstring& json_out);
	int SetFirewallState(wstring& json_out);
	OesisFirewall();
	~OesisFirewall();
};
