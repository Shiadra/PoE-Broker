#include "stdafx.h"
#include "BrokerModel.h"

#include "DataManager.h"

BrokerModel::BrokerModel(void)
{
	manager = new DataManager();
}

BrokerModel::~BrokerModel(void)
{
	delete manager;
}