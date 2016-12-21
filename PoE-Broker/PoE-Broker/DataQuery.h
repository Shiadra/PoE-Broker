#pragma once

#include <cpprest/http_client.h>

class DataManager;

class DataQuery
{
public:
	DataQuery(DataManager *m);
	pplx::task<void> GetStashTabs(utility::string_t id = U("0"));
private:
	DataManager *manager;

};
