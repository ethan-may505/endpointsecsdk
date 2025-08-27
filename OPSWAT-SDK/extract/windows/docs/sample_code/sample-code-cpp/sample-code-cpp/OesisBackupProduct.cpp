#include "OesisBackupProduct.h"

OesisBackupProduct::OesisBackupProduct()
{
    this->oesis = OesisFramework::instance();
}

OesisBackupProduct::~OesisBackupProduct(){}

int OesisBackupProduct::GetBackupState(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_GET_BACKUP_STATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}
