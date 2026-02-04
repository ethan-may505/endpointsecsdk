#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisAntiphishing : public OesisGenericProduct, public Singleton <OesisAntiphishing>
{
public:
	int GetAntiphishingState(wstring& json_out);
	OesisAntiphishing();
	~OesisAntiphishing();
};
