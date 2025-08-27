#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisMessengerProduct : public OesisGenericProduct, public Singleton <OesisMessengerProduct>
{
public:
	OesisMessengerProduct();
	~OesisMessengerProduct();
};