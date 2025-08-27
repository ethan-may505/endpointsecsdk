#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisPublicFileSharingProduct : public OesisGenericProduct, public Singleton <OesisPublicFileSharingProduct>
{
	public:
		OesisPublicFileSharingProduct();
		~OesisPublicFileSharingProduct();
};