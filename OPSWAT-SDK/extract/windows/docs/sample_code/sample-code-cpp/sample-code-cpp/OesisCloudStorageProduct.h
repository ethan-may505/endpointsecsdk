#pragma once
#include "OesisUtils.h"
#include "OesisGenericProduct.h"

class OesisCloudStorageProduct : public OesisGenericProduct, public Singleton <OesisCloudStorageProduct >
{
public:
	OesisCloudStorageProduct();
	~OesisCloudStorageProduct();
};