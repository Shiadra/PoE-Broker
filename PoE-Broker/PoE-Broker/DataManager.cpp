#include "stdafx.h"

#include "DataManager.h"
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace web;

DataManager::DataManager()
{
	query = new DataQuery(this);
	query->GetStashTabs();
}

DataManager::~DataManager()
{
	std::wcout << "destroying Data Manager" << std::endl;
	delete query;
}

void DataManager::handleDataQuery(json::value v)
{
	utility::string_t next_change_id = DisplayJSONValue(v);
	std::wcout << DisplayJSONValue(v) << std::endl;
	query->GetStashTabs(next_change_id);
}

utility::string_t DataManager::DisplayJSONValue(web::json::value v)
{
	auto next_change_id = v.at(U("next_change_id"));
	auto stashes = v.at(U("stashes"));
	//std::wcout << stashes.serialize() << std::endl;
	return next_change_id.as_string();
}