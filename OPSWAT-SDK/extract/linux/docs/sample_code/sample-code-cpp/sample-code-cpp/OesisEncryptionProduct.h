#pragma once

#include "wa_api.h"
#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisEncryptionProduct : public OesisGenericProduct, public Singleton <OesisEncryptionProduct>
{
public:
	int GetEncryptionState(wstring& json_out);
	OesisEncryptionProduct();
	~OesisEncryptionProduct();
};
