#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisPatchManagement : public OesisGenericProduct, public Singleton <OesisPatchManagement>
{
public:
	int GetAgentState(wstring& json_out);
	int SetAgentState(wstring& json_out);
	int GetMissingPatches(wstring& json_out);
	int InstallMissingPatches(wstring& json_out);
	int GetInstalledPatches(wstring& json_out);
	OesisPatchManagement();
	~OesisPatchManagement();
};
