#include "OesisVirtualMachine.h"

OesisVirtualMachine::OesisVirtualMachine()
{
    this->oesis = OesisFramework::instance();
}

int OesisVirtualMachine::GetAvailableVMs(wstring& json_out)
{
	return oesis->Invoke(json_out, WAAPI_MID_GET_FIREWALL_STATE, to_string(this->signature_id));
}

int OesisVirtualMachine::ListSnapshots(string input, wstring& json_out)
{
	return oesis->Invoke(json_out, WAAPI_MID_LIST_SNAPSHOTS, to_string(this->signature_id));
}

int OesisVirtualMachine::ManageVM(string input, wstring& json_out)
{
	return oesis->Invoke(json_out, WAAPI_MID_MANAGE_VM, to_string(this->signature_id));
}

int OesisVirtualMachine::GetVMState(string input, wstring& json_out)
{
	return oesis->Invoke(json_out, WAAPI_MID_GET_VM_STATE, to_string(this->signature_id));
}


OesisVirtualMachine::~OesisVirtualMachine()
{

}
