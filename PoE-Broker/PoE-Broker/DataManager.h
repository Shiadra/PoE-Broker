#pragma once

#include "DataQuery.h"
#include <cpprest/json.h>

class DataManager
{
public:
	DataManager();
	~DataManager();
	void handleDataQuery(web::json::value v);
	utility::string_t DisplayJSONValue(web::json::value v);
private:
	DataQuery *query;
};
