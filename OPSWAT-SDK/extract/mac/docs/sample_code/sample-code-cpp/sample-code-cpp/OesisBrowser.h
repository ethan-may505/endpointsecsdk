#pragma once

#include "wa_api.h"
#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisBrowser : public OesisGenericProduct, public Singleton <OesisBrowser>
{
public:
	int GetCookies(wstring& json_out);
	int SetCookies(wstring& json_out);
	int DeleteCookies(wstring& json_out);
	int DeleteCache(wstring& json_out);
	int DeleteBrowsingHistory(wstring& json_out);
	int DeleteDownloadHistory(wstring& json_out);
	int DeleteFormAndPasswordData(wstring& json_out);
	int ManageSyncProfile(wstring& json_out);
	int DeleteLastSession(wstring& json_out);
	OesisBrowser();
	~OesisBrowser();
};
