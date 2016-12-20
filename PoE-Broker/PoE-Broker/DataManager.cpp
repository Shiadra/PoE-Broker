#include "stdafx.h"

#include "DataManager.h"

using namespace web;

DataManager::DataManager()
{
	query = new DataQuery(this);
	query->GetStashTabs();
}

DataManager::~DataManager()
{
	delete query;
}

void DataManager::handleDataQuery(json::value v)
{
	std::wcout << v << std::endl;
}