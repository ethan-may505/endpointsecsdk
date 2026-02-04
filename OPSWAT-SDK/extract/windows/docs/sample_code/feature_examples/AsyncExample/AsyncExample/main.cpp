#include "json.hpp"
#include "wstring_utils.h"
#include "debug_info.h"
#include "timing_monitor.h"

#include "wa_api.h"
#include "wa_api_data_types.h"
#include "wa_api_product_categories.h"

#include <thread>
#include <iostream>
#include <mutex>

using wa_json = nlohmann::json;

// TODO - put your passkey here
// TODO - after build, put the license file to output folder
constexpr wa_wchar k_passkey[] = L"";

// TODO - fill the target categories for DetectProducts
// this example will try to detect all installed products
const std::vector<wa_int> k_target_categories = { WAAPI_CATEGORY_ALL };

wa_int received_events = 0;
std::mutex mt;
std::condition_variable cv;

// callback function for asynchronous events
// we can register multiple callback functions and use it for diffrerent invoke request
// in this example, we use one for GetVersion and one for GetRunningState
// both of them print the received event to console
// details about json_event can be found at 
// https://software.opswat.com/OESIS_V4/html/c_guide_event_handling.html
void get_version_event_handler(wa_wchar* json_event)
{
	std::wcout << L"GetVersion event received: " << json_event << std::endl;

	// free memory allocated by SDK
	wa_api_free(json_event);
	{
		std::lock_guard<std::mutex> lock(mt);
		++received_events;
	}
	cv.notify_all();
}

void get_running_state_event_handler(wa_wchar* json_event)
{
	std::wcout << L"GetRunningState event received: " << json_event << std::endl;
	wa_api_free(json_event);

	{
		std::lock_guard<std::mutex> lock(mt);
		++received_events;
	}
	cv.notify_all();
}

wa_int register_event_handler(wa_event_handler callback, wa_int& handler_id)
{
	// details about json_in for wa_api_register_handler can be found at 
	// https://software.opswat.com/OESIS_V4/html/c_sdk.html#wa_api_register_handler
	wa_json json_in =
	{
		{STR(WAAPI_KEY_EVENT_TYPE), 0}
	};

	wa_int rc = wa_api_register_handler(WSTR(json_in.dump()).c_str(), callback, &handler_id);

	Debug::print_to_console(L"wa_api_register_handler() returned " + std::to_wstring(rc));
	Debug::print_to_console(L"Handler ID: " + std::to_wstring(handler_id));
	return rc;
}

wa_int init_sdk()
{
	Debug::print_to_console(L"Initializing SDK...");

	wa_json json_in =
	{
		{STR(WAAPI_KEY_CONFIGURATION),
			{
				{STR(WAAPI_CONFIG_PRETTY_PRINT), false},
				{STR(WAAPI_CONFIG_ONLINE_MODE), false},
				{STR(WAAPI_CONFIG_PASSKEY_KEY), STR(k_passkey)}
			}
		}
	};

	wa_wchar* json_out = nullptr;
	wa_int rc = wa_api_setup(WSTR(json_in.dump()).c_str(), &json_out);

	Debug::print_to_console(L"wa_api_setup() returned " + std::to_wstring(rc));
	Debug::print_to_console(L"JSON output: " + std::wstring(json_out));

	// don't forget to free memory allocated by SDK
	wa_api_free(json_out);
	return rc;
}

wa_int detect_products_with_multi_threaded(std::wstring& result)
{
	wa_json json_in =
	{
		{
			STR(WAAPI_KEY_INPUT),
			{
				{STR(WAAPI_KEY_METHOD), WAAPI_MID_DETECT_PRODUCTS},
				{STR(WAAPI_KEY_CATEGORIES), k_target_categories},
				// disable this flag to use multi-threaded mode for DetectProducts
				{STR(WAAPI_KEY_SINGLE_THREADED), false}
			}
		}
	};

	Debug::print_to_console(L"Detecting installed products...");
	Debug::print_to_console(L"JSON input: " + std::wstring(WSTR(json_in.dump())));

	wa_wchar* json_out = nullptr;
	wa_int rc = wa_api_invoke(WSTR(json_in.dump()).c_str(), &json_out);

	Debug::print_to_console(L"DetectProducts returned " + std::to_wstring(rc));
	if (WAAPI_SUCCESS(rc))
	{
		result = std::wstring(json_out);
		Debug::print_to_console(L"JSON output: " + result);
	}
	wa_api_free(json_out);

	return rc;
}

wa_int invoke_async_with_callback(wa_int signature, wa_int method, wa_int handler_id)
{
	wa_json json_in =
	{
		{STR(WAAPI_KEY_INPUT),
			{
				{STR(WAAPI_KEY_METHOD), method},
				{STR(WAAPI_KEY_SIGNATURE), signature},
				// this flag is required to invoke method asynchronously
				// details about async job can be found at
				// https://software.opswat.com/OESIS_V4/html/c_guide_async_api.html
				{STR(WAAPI_KEY_ASYNC_JOB), true}
			}
		},
		{STR(WAAPI_KEY_HANDLER_ID), handler_id}
	};

	Debug::print_to_console(L"Invoking method asynchronously with callback handler id: " + std::to_wstring(handler_id)
		+ L", signature id: " + std::to_wstring(signature) + L", method id: " + std::to_wstring(method));

	wa_wchar* json_out = nullptr;
	wa_int rc = wa_api_invoke(WSTR(json_in.dump()).c_str(), &json_out);

	Debug::print_to_console(L"wa_api_invoke() returned " + std::to_wstring(rc));
	Debug::print_to_console(L"JSON output: " + std::wstring(json_out));
	wa_api_free(json_out);

	return rc;
}

int main()
{
	Debug::print_debug_info();
	Debug::pause_if_debug();

	// at first, initialize SDK
	if (WAAPI_FAILED(init_sdk()))
		return EXIT_FAILURE;

	Debug::pause_if_debug();

	// detect installed products for k_target_categories in multi-threaded mode
	std::wstring result;
	if (WAAPI_FAILED(detect_products_with_multi_threaded(result)) || result.empty())
	{
		// remember to teardown SDK to free memory and clean up resources
		wa_api_teardown();
		return EXIT_FAILURE;
	}

	// parse JSON output from DetectProducts
	wa_json detect_products_json_out = wa_json::parse(STR(result), nullptr, false);
	if (detect_products_json_out.is_discarded())
	{
		Debug::print_to_console(L"Can not parse JSON from DetectProducts!");
		wa_api_teardown();
		return EXIT_FAILURE;
	}

	// get elapsed time for DetectProducts
	unsigned long long detect_products_elapsed_time = 0;
	if (detect_products_json_out.contains(STR(WAAPI_KEY_RESULT)) &&
		detect_products_json_out[STR(WAAPI_KEY_RESULT)].contains(STR(WAAPI_KEY_TIMING)))
	{
		detect_products_elapsed_time = detect_products_json_out[STR(WAAPI_KEY_RESULT)][STR(WAAPI_KEY_TIMING)];
	}

	Debug::pause_if_debug();

	// register event handler for GetVersion and GetRunningState asynchronous invoke
	wa_int get_version_handler_id = 0;
	wa_int get_running_state_handler_id = 0;
	if (WAAPI_FAILED(register_event_handler(get_version_event_handler, get_version_handler_id)) || 
		WAAPI_FAILED(register_event_handler(get_running_state_event_handler, get_running_state_handler_id)))
	{
		wa_api_teardown();
		return EXIT_FAILURE;
	}

	Debug::pause_if_debug();

	unsigned long long invoke_elapsed_time = 0;
	{
		TimingMonitor tm(&invoke_elapsed_time);

		wa_int sent_events = 0;
		if (detect_products_json_out.contains(STR(WAAPI_KEY_RESULT)) &&
			detect_products_json_out[STR(WAAPI_KEY_RESULT)].contains(STR(WAAPI_KEY_DETECTED_PRODUCTS)))
		{
			wa_json products = detect_products_json_out[STR(WAAPI_KEY_RESULT)][STR(WAAPI_KEY_DETECTED_PRODUCTS)];
			for (const auto& product : products)
			{
				wa_int signature = product[STR(WAAPI_KEY_SIGNATURE)];
				std::wstring product_name = WSTR(product[STR(WAAPI_KEY_SIGNATURE_NAME)]);

				Debug::print_to_console(L"Product name: " + product_name);
				Debug::print_to_console(L"Signature ID: " + std::to_wstring(signature));

				// invoke GetVersion asynchronously with callback registered above (handler id: get_version_handler_id)
				invoke_async_with_callback(signature, WAAPI_MID_COMMON_GET_VERSION, get_version_handler_id);

				// invoke GetRunningState asynchronously with callback registered above (handler id: get_running_state_handler_id)
				invoke_async_with_callback(signature, WAAPI_MID_GET_RUNNING_STATE, get_running_state_handler_id);

				sent_events += 2;
			}
		}

		// wait for all events to be received
		std::unique_lock<std::mutex> lock(mt);
		cv.wait(lock, [sent_events]() { return (received_events == sent_events) || sent_events == 0; });
	}

	if (received_events != 0)
	{
		std::wcout << L"DetectProducts (multi threaded) elapsed time: " << detect_products_elapsed_time << L" ms" << std::endl;
		std::wcout << L"Total elapsed time for " << received_events << L" async requests: " << invoke_elapsed_time << L" ms" << std::endl;
	}
	else
	{
		std::wcout << L"An error occured!" << std::endl;
	}

	Debug::pause_if_debug();
	Debug::print_to_console(L"Unregistering event handlers and tearing down SDK...");

	// these callbacks will be unregister automatically when SDK is teared down
	// but in case you want to unregister them manually, use wa_api_unregister_handler
	wa_api_unregister_handler(get_version_handler_id);
	wa_api_unregister_handler(get_running_state_handler_id);

	wa_int rc = wa_api_teardown();
	if (WAAPI_FAILED(rc))
	{
		// do something here, maybe warning or error message that SDK haven't been teared down properly
		Debug::print_to_console(L"wa_api_teardown() returned " + std::to_wstring(rc));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}