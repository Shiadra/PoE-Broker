#include "stdafx.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <iostream>
#include <sstream>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

pplx::task<void> HTTPStreamingAsync()
{
	http_client client(L"http://api.pathofexile.com/public-stash-tabs");

	// Make the request and asynchronously process the response. 
	return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
			std::wcout << response.extract_string().get() << std::endl;
			return response.extract_json();
		}
		std::wcout << L"Error1" << std::endl;
		// Handle error cases, for now return empty json value... 
		return pplx::task_from_result(json::value());
	})
		.then([](json::value previousTask)
	{
		try
		{
			std::wcout << L"Parse" << std::endl;
			const json::value& v = previousTask;
			std::wcout << L"Value:" << v.serialize() << std::endl;
		}
		catch (const http_exception& e)
		{
			std::wcout << L"Error2" << std::endl;
			// Print error.
			std::wostringstream ss;
			ss << e.what() << std::endl;
			std::wcout << ss.str();
		}
	});

	/* Sample output:
	Server returned returned status code 200.
	Content length is 63803 bytes.
	*/
}