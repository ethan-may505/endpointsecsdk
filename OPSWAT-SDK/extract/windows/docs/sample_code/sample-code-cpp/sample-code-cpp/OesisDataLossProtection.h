#pragma once

#include "OesisUtils.h"
#include "OesisFramework.h"
#include "OesisGenericProduct.h"
#include "OesisUtils.h"

#define WAAPI_MID_SET_ANTI_KEYLOGGER_STATE 120001
#define WAAPI_MID_INSTALL_ANTI_KEYLOGGER 120002
#define WAAPI_MID_UNINSTALL_ANTI_KEYLOGGER 120003
#define WAAPI_MID_GET_ANTI_KEYLOGGER_STATE 120004
#define WAAPI_MID_MANAGE_ANTI_KEYLOGGER_PROCESS 120005
#define WAAPI_MID_INSTALL_ANTI_SCREENCAPTURE 120010
#define WAAPI_MID_UNINSTALL_ANTI_SCREENCAPTURE 120011
#define WAAPI_MID_GET_ANTI_SCREENCAPTURE_STATE 120012
#define WAAPI_MID_MANAGE_ANTI_SCREENCAPTURE_PROCESS 120013

class OesisDataLossProtection : public Singleton<OesisDataLossProtection>
{

public:
	OesisDataLossProtection();
	static int SetAntiKeyloggerState(wstring input, wstring& json_out);
	static int InstallAntiKeylogger(wstring& json_out);
	static int UninstallAntiKeylogger(wstring& json_out);
	static int GetAntiKeyloggerState(wstring& json_out);
	static int ManageAntiKeyloggerProcess(wstring input, wstring& json_out);
	static int InstallAntiScreenCapture(wstring& json_out);
	static int UninstallAntiScreenCapture(wstring& json_out);
	static int GetAntiScreenCaptureState(wstring& json_out);
	static int ManageAntiScreenCaptureProcess(wstring input, wstring& json_out);
	static int ManageDLPModule(wstring& json_out, string methodId, string operation = "");
	~OesisDataLossProtection();
};
