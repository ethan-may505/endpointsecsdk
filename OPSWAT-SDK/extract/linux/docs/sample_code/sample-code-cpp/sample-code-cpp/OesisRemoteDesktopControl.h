#pragma once

#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisRemoteDesktopControl : public OesisGenericProduct, public Singleton <OesisRemoteDesktopControl>
{
public:
	OesisRemoteDesktopControl();
	~OesisRemoteDesktopControl();
};