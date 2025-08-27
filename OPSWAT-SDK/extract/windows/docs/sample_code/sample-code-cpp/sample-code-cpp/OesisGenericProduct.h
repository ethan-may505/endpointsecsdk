#pragma once

#include "wa_api.h"
#include "OesisFramework.h"
#include "OesisUtils.h"

class OesisGenericProduct
{
protected:
    int signature_id;
    int product_id;
    int vendor_id;
    int categories[20];
    string signature_name;
    string product_name;
    string vendor_name;
    OesisFramework* oesis;
public:
    OesisGenericProduct* GetGenericProduct() { return this; }
    OesisGenericProduct();
    void SetSignatureId(int sig);
    int GetVersion(wstring& json_out);
    int Run(wstring& json_out);
    int GetRunningState(wstring& json_out);
    int TerminateProcesses(wstring& json_out);
    int GetInstallationDirectories(wstring& json_out);
    int GetComponents(wstring& json_out, bool include_services);
    int GetUninstallString(wstring& json_out);
    int ManageLabels(wstring& json_out, int labels[10], bool reset);
    int IsAuthentic(wstring& json_out);
    int GetProductInfo(wstring& json_out, bool run_detection);
    string GetVersion();
    json IsAuthentic();
    json GetComponents();
};

