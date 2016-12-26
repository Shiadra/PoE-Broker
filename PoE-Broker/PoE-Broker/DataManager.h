#pragma once

#include "DataQuery.h"
#include <cpprest/json.h>

class DataManager
{
public:
	DataManager();
	~DataManager();
	void handleDataQuery(web::json::value v, std::shared_ptr<std::chrono::steady_clock::time_point> pTime);
	utility::string_t ParseJSON(web::json::value v);
private:
	DataQuery *query;
	utility::string_t river;
	void DataManager::ParseStash(web::json::array *a, size_t lo, size_t hi);
};
