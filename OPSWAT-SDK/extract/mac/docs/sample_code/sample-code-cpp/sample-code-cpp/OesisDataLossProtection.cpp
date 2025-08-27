#pragma once

#include "OesisDataLossProtection.h"

OesisDataLossProtection::OesisDataLossProtection(){}

OesisDataLossProtection::~OesisDataLossProtection(){}

wa_int OesisDataLossProtection::SetAntiKeyloggerState(wstring input, wstring& json_out) {
	wstring json_in = input;//OesisUtils::CreateJsonIn();
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}wa_int OesisDataLossProtection::InstallAntiKeylogger(wstring& json_out) {
	wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_INSTALL_ANTI_KEYLOGGER);
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}

wa_int OesisDataLossProtection::UninstallAntiKeylogger(wstring& json_out) {
	wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_UNINSTALL_ANTI_KEYLOGGER);
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}

wa_int OesisDataLossProtection::GetAntiKeyloggerState(wstring& json_out) {
	wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_GET_ANTI_KEYLOGGER_STATE);
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}

wa_int OesisDataLossProtection::ManageAntiKeyloggerProcess(wstring input, wstring& json_out) {
	wstring json_in = input;//OesisUtils::CreateJsonIn(120005);
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}

wa_int OesisDataLossProtection::InstallAntiScreenCapture(wstring& json_out) {
	wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_INSTALL_ANTI_SCREENCAPTURE);
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}

wa_int OesisDataLossProtection::UninstallAntiScreenCapture(wstring& json_out) {
	wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_UNINSTALL_ANTI_SCREENCAPTURE);
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}

wa_int OesisDataLossProtection::GetAntiScreenCaptureState(wstring& json_out) {
	wstring json_in = OesisUtils::CreateJsonIn(WAAPI_MID_GET_ANTI_SCREENCAPTURE_STATE);
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}

wa_int OesisDataLossProtection::ManageAntiScreenCaptureProcess(wstring input, wstring& json_out) {
	wstring json_in = input;//OesisUtils::CreateJsonIn(120013);
	wa_int rc = OesisFramework::instance()->Invoke(json_in.c_str(), json_out);
	return rc;
}


int OesisDataLossProtection::ManageDLPModule(wstring& json_out, string methodId, string operation)
{
	map<string, string> param = {
		{"method", methodId}
	};
	if (operation != "")
	{
		param["operation"] = operation;
	}
    return OesisFramework::instance()->Invoke(param, json_out);
}

int GetDLPState(wstring& json_out, string methodId)
{
	map<string, string> param = {
		{"method", methodId}
	};
	return OesisFramework::instance()->Invoke({ { "method", methodId} }, json_out);

}
