#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisVirtualMachine : public OesisGenericProduct, public Singleton <OesisVirtualMachine>
{
public:
	OesisVirtualMachine();
	int GetAvailableVMs(wstring& json_out);
	int ListSnapshots(string input, wstring& json_out);
	int ManageVM(string input, wstring& json_out);
	int GetVMState(string input, wstring& json_out);
	~OesisVirtualMachine();
};
