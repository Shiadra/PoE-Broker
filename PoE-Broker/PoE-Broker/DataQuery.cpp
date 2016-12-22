#include "stdafx.h"

#include <cpprest/http_client.h>
#include "DataQuery.h"
#include "DataManager.h"

#include <agents.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

DataQuery::DataQuery(DataManager *m)
{
	manager = m;
}

pplx::task<void> DataQuery::GetStashTabs(utility::string_t id, std::shared_ptr<std::chrono::steady_clock::time_point> pTime)
{
	
	// Make the request and asynchronously process the response.
	if (pTime == nullptr)
	{
		return MakeQuery(id);
	}
	else
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		auto pTimeDiff = std::chrono::milliseconds(std::chrono::duration_cast<std::chrono::milliseconds>(*pTime - now));
		std::cout << pTimeDiff.count() << std::endl;
		if (pTimeDiff > std::chrono::milliseconds(0))
		{
			std::cout << "Delay for " << pTimeDiff.count() << std::endl;
			return create_delayed_task(pTimeDiff).then([this, id]()
			{
				MakeQuery(id);
			});
		}
		else
		{
			return MakeQuery(id);
		}
	}
}

pplx::task<void> DataQuery::create_delayed_task(std::chrono::milliseconds delay)
{
	concurrency::task_completion_event<void> tce;

	auto pTimer = new concurrency::timer<int>(static_cast<int>(delay.count()), 0, NULL, false);
	auto pCallback = new concurrency::call<int>([tce](int) {
		tce.set();
	});

	pTimer->link_target(pCallback);
	pTimer->start();

	pplx::task<void> event_set(tce);

	return event_set.then([pCallback, pTimer]()
	{
		delete pCallback;
		delete pTimer;
	});
}

pplx::task<void> DataQuery::MakeQuery(utility::string_t id)
{
	http_client client(U("http://api.pathofexile.com/public-stash-tabs/"));

	uri_builder builder(U(""));
	builder.append_query(U("id"), id);
	auto pTime = std::make_shared<std::chrono::steady_clock::time_point>(std::chrono::steady_clock::now());
	return client.request(methods::GET, builder.to_string()).then([pTime](http_response response) -> pplx::task<json::value>
	{
		status_code status = response.status_code();
		if (status == status_codes::OK)
		{
			std::cout << "Received" << std::endl;
			*pTime += std::chrono::seconds(1);
			return response.extract_json();
		}
		else if (status == status_codes::BadRequest) {
			std::cout << "Bad Request" << std::endl;
			return pplx::task_from_result(json::value());
		}
		else if (status == status_codes::NotFound) {
			std::cout << "Not Found" << std::endl;
			*pTime += std::chrono::seconds(120);
			return pplx::task_from_result(json::value());
		}
		else if (status == 429U) {
			std::cout << "Rate Limited" << std::endl;
			*pTime += std::chrono::seconds(2);
			return response.extract_json();
		}
		else if (status == status_codes::InternalError) {
			std::cout << "Internal Error" << std::endl;
			*pTime += std::chrono::seconds(120);
			return pplx::task_from_result(json::value());
		}
		// Handle error cases, for now return empty json value... 
		std::cout << "Unknown Error: " << response.status_code() << std::endl;
		return pplx::task_from_result(json::value());
	})
		.then([this, id, pTime](pplx::task<json::value> previousTask)
	{
		try
		{
			std::cout << "Extracted" << std::endl;
			const json::value& v = previousTask.get();
			if (v.is_null())
			{
				std::cout << "No Data: Retrying..." << std::endl;
				GetStashTabs(id, pTime);
			}
			else {
				manager->handleDataQuery(v, pTime);
			}	
		}
		catch (const http_exception& e)
		{
			// Error.
			std::wcout << e.what() << std::endl;
		}
	});
}