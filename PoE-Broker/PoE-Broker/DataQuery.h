#pragma once

#include <cpprest/http_client.h>

class DataManager;

class DataQuery
{
public:
	DataQuery(DataManager *m);
	pplx::task<void> GetStashTabs(std::string id = "0");
private:
	DataManager *manager;

};
