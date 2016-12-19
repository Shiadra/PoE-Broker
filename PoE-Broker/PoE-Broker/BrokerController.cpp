#include "stdafx.h"
#include "BrokerController.h"
#include "BrokerView.h"

BrokerController::BrokerController(BrokerModel *m)
{
	model = m;
}

void BrokerController::setView(BrokerView *v)
{
	view = v;
}