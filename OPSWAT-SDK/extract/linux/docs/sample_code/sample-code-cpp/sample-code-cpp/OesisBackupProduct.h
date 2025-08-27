#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisBackupProduct : public OesisGenericProduct, public Singleton <OesisBackupProduct>
{
public:
	int GetBackupState(wstring& json_out);
	OesisBackupProduct();
	~OesisBackupProduct();
};
