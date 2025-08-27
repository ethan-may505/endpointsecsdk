#pragma once
#include "OesisUtils.h"
#include "OesisFramework.h"

using namespace std;

class OesisDeviceInfo
{
private:
	OesisFramework* oesis;
public:
	OesisDeviceInfo();
	int GetPCModel(wstring& json_out);
	int GetCpuAndRamInfo(wstring& json_out);
	int GetPCComponents(wstring& json_out);
	int GetDiskSpace(wstring& json_out);
	int GetDevicePasswordProtectionState(wstring& json_out);
	int IsCurrentDeviceVirtual(wstring& json_out);
	int GetSystemVolume(wstring& json_out);
	~OesisDeviceInfo();
};
