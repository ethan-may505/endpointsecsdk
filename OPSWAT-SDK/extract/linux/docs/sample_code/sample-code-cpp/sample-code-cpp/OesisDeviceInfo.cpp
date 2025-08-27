#include "OesisDeviceInfo.h"

#include <iostream>
#include <sstream>

using namespace std;

OesisDeviceInfo::OesisDeviceInfo()
{
    this->oesis = OesisFramework::instance();
}

int OesisDeviceInfo::GetPCModel(wstring& json_out) 
{
	return oesis->Invoke({ {"method", to_string(WAAPI_MID_GET_PC_MODEL)} }, json_out);
}

int OesisDeviceInfo::GetCpuAndRamInfo(wstring& json_out)
{
	return oesis->Invoke({ {"method", to_string(WAAPI_MID_GET_PC_CPU_RAM)} }, json_out);
}

int OesisDeviceInfo::GetPCComponents(wstring& json_out)
{
	return oesis->Invoke({ {"method", to_string(WAAPI_MID_GET_PC_COMPONENTS)} }, json_out);
}

int OesisDeviceInfo::GetDiskSpace(wstring& json_out)
{
	return oesis->Invoke({ {"method", to_string(WAAPI_MID_GET_PC_DISK_SPACE)} }, json_out);
}

int OesisDeviceInfo::GetDevicePasswordProtectionState(wstring& json_out)
{
	return oesis->Invoke({ {"method", to_string(WAAPI_MID_GET_DEVICE_PASSWORD_PROTECTION_STATE)} }, json_out);
}

int OesisDeviceInfo::IsCurrentDeviceVirtual(wstring& json_out)
{
	return oesis->Invoke({ {"method", to_string(WAAPI_MID_IS_CURRENT_DEVICE_VIRTUAL)} }, json_out);
}

int OesisDeviceInfo::GetSystemVolume(wstring& json_out)
{
	return oesis->Invoke({ {"method", to_string(WAAPI_MID_GET_SYSTEM_VOLUME)} }, json_out);
}

OesisDeviceInfo::~OesisDeviceInfo(){}
