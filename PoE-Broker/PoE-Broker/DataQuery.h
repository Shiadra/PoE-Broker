#pragma once

#include <cpprest/http_client.h>

class DataManager;

class DataQuery
{
public:
	DataQuery(DataManager *m);
	pplx::task<void> GetStashTabs(utility::string_t id = U("0"), std::shared_ptr<std::chrono::steady_clock::time_point> pTime = nullptr);
private:
	DataManager *manager;
	pplx::task<void> MakeQuery(utility::string_t id);
	pplx::task<void> create_delayed_task(std::chrono::milliseconds delay);
};
