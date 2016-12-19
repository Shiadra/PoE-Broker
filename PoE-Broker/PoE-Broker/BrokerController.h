#pragma once

#include "BrokerModel.h"

class BrokerView;

class BrokerController {
public:
	BrokerController(BrokerModel *model);
	void setView(BrokerView *view);
private:
	BrokerModel *model;
	BrokerView *view;
};