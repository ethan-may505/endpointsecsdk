#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisUnclassified : public OesisGenericProduct, public Singleton <OesisUnclassified>
{
public:
	OesisUnclassified();
	~OesisUnclassified();
};
