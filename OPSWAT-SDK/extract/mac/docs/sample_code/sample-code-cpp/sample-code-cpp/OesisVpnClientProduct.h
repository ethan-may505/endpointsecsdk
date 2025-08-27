#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisVpnClientProduct: public OesisGenericProduct, public Singleton <OesisVpnClientProduct >
{
public:
	OesisVpnClientProduct();
	~OesisVpnClientProduct();
};