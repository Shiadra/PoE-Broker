#include "stdafx.h"

#include <cpprest/http_client.h>
#include "DataQuery.h"
#include "DataManager.h"

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

pplx::task<void> DataQuery::GetStashTabs(std::string id)
{
	http_client client(L"http://api.pathofexile.com/public-stash-tabs");

	// Make the request and asynchronously process the response. 
	return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
			//std::wcout << response.extract_json().get() << std::endl;
			return response.extract_json();
		}
		// Handle error cases, for now return empty json value... 
		return pplx::task_from_result(json::value());
	})
		.then([this](pplx::task<json::value> previousTask)
	{
		try
		{
			const json::value& v = previousTask.get();
			manager->handleDataQuery(v);
		}
		catch (const http_exception& e)
		{
			// Error.
		}
	});

	/* Sample output:
	Server returned returned status code 200.
	Content length is 63803 bytes.
	*/
}