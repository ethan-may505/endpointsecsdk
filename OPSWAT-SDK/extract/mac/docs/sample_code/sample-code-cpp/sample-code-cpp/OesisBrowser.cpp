#include "OesisBrowser.h"

OesisBrowser::OesisBrowser()
{
    this->oesis = OesisFramework::instance();
}

OesisBrowser::~OesisBrowser(){}

int OesisBrowser::GetCookies(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_GET_COOKIE)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}

int OesisBrowser::SetCookies(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_SET_COOKIE)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}

int OesisBrowser::DeleteCookies(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_DELETE_COOKIE)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}

int OesisBrowser::DeleteCache(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_DELETE_CACHE)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}

int OesisBrowser::DeleteBrowsingHistory(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_DELETE_BROWSING_HISTORY)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}

int OesisBrowser::DeleteDownloadHistory(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_DELETE_DOWNLOAD_HISTORY)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}

int OesisBrowser::DeleteFormAndPasswordData(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_DELETE_FORM_PASSWORD)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}

int OesisBrowser::ManageSyncProfile(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_MANAGE_SYNC_PROFILE)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}

int OesisBrowser::DeleteLastSession(wstring& json_out)
{
	map<string, string> param = {
		{"method", to_string(WAAPI_MID_DELETE_LAST_SESSION)},
		{"signature", to_string(this->signature_id)}
	};
	return oesis->Invoke(param, json_out);
}
