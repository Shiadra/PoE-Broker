#include "stdafx.h"

#include "DataManager.h"
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <ppl.h>
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

void DataManager::handleDataQuery(json::value v, std::shared_ptr<std::chrono::steady_clock::time_point> pTime)
{
	utility::string_t next_change_id = ParseJSON(v);
	query->GetStashTabs(next_change_id, pTime);
}

utility::string_t DataManager::ParseJSON(web::json::value v)
{
	auto next_change_id = v.at(U("next_change_id"));
	auto stashes = v.at(U("stashes")).as_array();
	const size_t aStash = stashes.size();
	std::cout << "Parsing " << aStash << " stashes" << std::endl;
	if (aStash > 2100)
	{
		const size_t blockSize = aStash / 4;
		concurrency::parallel_invoke(
			[this, &stashes, blockSize] { ParseStash(&stashes, 0, blockSize); },
			[this, &stashes, blockSize] { ParseStash(&stashes, blockSize, blockSize * 2); },
			[this, &stashes, blockSize] { ParseStash(&stashes, blockSize * 2, blockSize * 3); },
			[this, &stashes, blockSize, aStash] { ParseStash(&stashes, blockSize * 3, aStash); }
		);
	}
	else
	{
		ParseStash(&stashes, 0, aStash);
	}
	//std::wcout << stashes.serialize() << std::endl;
	return next_change_id.as_string();
}

void DataManager::ParseStash(web::json::array *a, const size_t lo, const size_t hi)
{
	for (size_t i = lo; i < hi; i++)
	{
		auto stash = (*a)[i];
		auto accountName = stash.at(U("accountName"));
		auto lastCharacterName = stash.at(U("lastCharacterName"));
		auto id = stash.at(U("id"));
		auto stashName = stash.at(U("stash"));
		auto stashType = stash.at(U("stashType"));
		auto items = stash.at(U("items")).as_array();
		for (size_t i = 0; i < items.size(); i++)
		{
			auto item = items[i];
			auto name = item.at(U("name"));
			std::wcout << name << std::endl;
		}
		auto isPublic = stash.at(U("public"));
	}
}