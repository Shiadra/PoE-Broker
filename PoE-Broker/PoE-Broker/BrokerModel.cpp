#include "stdafx.h"
#include "BrokerModel.h"

#include "DataQuery.h"

BrokerModel::BrokerModel(void)
{
	HTTPStreamingAsync().wait();
	HTTPStreamingAsync().wait();
	HTTPStreamingAsync().wait();
	HTTPStreamingAsync().wait();
	HTTPStreamingAsync().wait();
}