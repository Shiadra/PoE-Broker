#pragma once

#include "DataManager.h"

class BrokerModel
{
public:
	BrokerModel();
	~BrokerModel();
private:
	DataManager *manager;
};