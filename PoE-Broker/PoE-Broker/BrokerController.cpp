#include "stdafx.h"
#include "BrokerController.h"

BrokerController::BrokerController(BrokerModel *m)
{
	model = m;
}

void BrokerController::setView(BrokerView *v)
{
	view = v;
}