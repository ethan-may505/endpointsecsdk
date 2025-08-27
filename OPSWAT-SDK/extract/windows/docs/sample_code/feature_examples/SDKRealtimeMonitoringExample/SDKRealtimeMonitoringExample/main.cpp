// This file contains the main function of the SDKRealtimeMonitoringExample project.
// Please check README.md for more information about this example.

#include <iostream>
#include <mutex>
#include <queue>

#include "wstring_utils.h"
#include "json.hpp"

#include "wa_api.h"
#include "wa_api_data_types.h"

using wa_json = nlohmann::json;

// TODO - put your passkey here
// TODO - after build, put the license file to output folder
constexpr wa_wchar k_passkey[] = L"";

// TODO - put your signature and method ID that you want to monitor here
// details about json_in for wa_api_register_handler can be found at 
// https://software.opswat.com/OESIS_V4/html/c_sdk.html#wa_api_register_handler
const wa_json monitor_json_in =
{
	{STR(WAAPI_KEY_EVENT_TYPE), 10},
	{STR(WAAPI_KEY_CONFIGURATION),
		{
			{STR(WAAPI_KEY_SIGNATURE), 477},
			{STR(WAAPI_KEY_METHOD), 1000}
		}
	}
};

// This JSON will be used to remediate the endpoint when the product state changes to under risk
const wa_json remediate_json_in = 
{
	{STR(WAAPI_KEY_INPUT),
		{
			{STR(WAAPI_KEY_SIGNATURE), 477},
			{STR(WAAPI_KEY_METHOD), 1005}
		}
	}
};

std::mutex mtx;
std::condition_variable cv;
std::queue<wa_json> event_queue;
std::atomic_bool stop_flag = false;

// Callback function that will be called when the product state changes
void callback(wa_wchar* json_data)
{
	std::wstring json_data_str(json_data);
	
	{
		std::lock_guard<std::mutex> lock(mtx);

		// It is recommended to handle the event quickly to avoid blocking the nofitication thread
		// In this example, we will push the event to a queue and process it in another thread
		event_queue.push(wa_json::parse(STR(json_data)));
	}

	// Don't forget to free memory allocated by SDK
	wa_api_free(json_data);
	cv.notify_one();
};

void process_event(const wa_json& event)
{
	std::wcout << "Event received: " << WSTR(event.dump()) << std::endl;

	if (!event.contains("result"))
	{
		std::wcout << "Something went wrong! The event doesn't contain 'result' key!" << std::endl;
		return;
	}

	if (!event.at("result").contains("enabled"))
	{
		std::wcout << "Something went wrong! The event doesn't contain 'result.enabled' key!" << std::endl;
		return;
	}

	if (!event.at("result").at("enabled").get<bool>())
	{
		std::wcout << "The endpoint is under risk! Remediating..." << std::endl;

		wa_wchar* json_out = nullptr;
		wa_int rc = wa_api_invoke(WSTR(remediate_json_in.dump()).c_str(), &json_out);

		std::wcout << L"wa_api_invoke() returned " << rc << std::endl;
		std::wcout << L"JSON output: " << json_out << std::endl;
		wa_api_free(json_out);

		std::wcout << (WAAPI_FAILED(rc) 
			? "Failed to remediate the endpoint!"
			: "The endpoint has been remediated!")
		<< std::endl;
	}
	else
	{
		std::wcout << L"Current state is safe!" << std::endl;
	}

	std::wcout << "-----------------------------------" << std::endl << std::endl;
}

void event_consumer_thread_func()
{
	while (!stop_flag)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [] { return !event_queue.empty() || stop_flag; });
		while (!event_queue.empty())
		{
			wa_json event = event_queue.front();
			event_queue.pop();
			
			lock.unlock();
			process_event(event);
			lock.lock();
		}
	}
}

wa_int init_sdk()
{
	std::wcout << "Initializing SDK ..." << std::endl;

	wa_json json_in =
	{
		{STR(WAAPI_KEY_CONFIGURATION),
			{
				{STR(WAAPI_CONFIG_PRETTY_PRINT), true},
				{STR(WAAPI_CONFIG_PASSKEY_KEY), STR(k_passkey)}
			}
		}
	};

	wa_wchar* json_out = nullptr;
	wa_int rc = wa_api_setup(WSTR(json_in.dump()).c_str(), &json_out);

	std::wcout << "wa_api_setup() returned " << rc << std::endl;
	std::wcout << "JSON output: " << json_out << std::endl;
	std::wcout << "-----------------------------------" << std::endl << std::endl;

	// don't forget to free memory allocated by SDK
	wa_api_free(json_out);
	return rc;
}

wa_int teardown_sdk()
{
	std::wcout << L"Starting to teardown SDK..." << std::endl;

	auto rc = wa_api_teardown();
	if (WAAPI_FAILED(rc))
	{
		// do something here, maybe warning or error message that SDK haven't been teared down properly
		std::wcout << L"wa_api_teardown() returned " << rc << std::endl;
	}

	return rc;
}

int main()
{
	if (WAAPI_FAILED(init_sdk()))
		return EXIT_FAILURE;

	do
	{
		std::wcout << L"Registering handler with input: " + WSTR(monitor_json_in.dump()) << std::endl;

		wa_int registered_id = 0;
		wa_int rc = wa_api_register_handler(WSTR(monitor_json_in.dump()).c_str(), callback, &registered_id);
		
		std::wcout << L"wa_api_register_handler() returned " << rc << std::endl;
		std::wcout << L"Event registered, ID: " << registered_id << std::endl;
		std::wcout << "-----------------------------------" << std::endl << std::endl;

		if (WAAPI_FAILED(rc))
			break;

		std::thread event_consumer_thread(event_consumer_thread_func);

		std::wcout << "Now monitoring for the product state changes" << std::endl;
		std::wcout << L"Press Enter to stop the program..." << std::endl;
		std::wcout << "-----------------------------------" << std::endl << std::endl;
		std::wcin.get();

		// by default, the monitor will be unregistered when the sdk is teared down
		// but you can also unregister it manually
		wa_api_unregister_handler(registered_id);

		stop_flag = true;
		cv.notify_all();
		if (event_consumer_thread.joinable())
			event_consumer_thread.join();
	} 
	while (false);
	
	if (WAAPI_FAILED(teardown_sdk()))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}