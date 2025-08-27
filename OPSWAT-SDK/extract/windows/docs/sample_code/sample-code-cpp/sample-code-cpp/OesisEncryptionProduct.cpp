#include "OesisEncryptionProduct.h"

OesisEncryptionProduct::OesisEncryptionProduct()
{
    this->oesis = OesisFramework::instance();
}

OesisEncryptionProduct::~OesisEncryptionProduct(){}

int OesisEncryptionProduct::GetEncryptionState(wstring& json_out)
{
    map<string, string> param = {
        {"method", to_string(WAAPI_MID_GET_ENCRYPTION_STATE)},
        {"signature", to_string(this->signature_id)}
    };
    return oesis->Invoke(param, json_out);
}
