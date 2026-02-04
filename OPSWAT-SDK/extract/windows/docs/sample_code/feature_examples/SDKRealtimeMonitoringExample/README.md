# SDK Realtime Monitoring Feature Example
### Project structure
Please place the SDK files in the following folders:
* DLL libraries to **sdk/bin/\<platform\>** folder. At a minimum, include the following:
  * libwaapi.dll
  * libwaheap.dll
  * libwalocal.dll
  * libwaresource.dll
  * libwautils.dll
  * wa_3rd_party_host_*.exe
* SDK headers to **sdk/headers** folder.
* SDK static lib (libwaapi.lib) to **sdk/lib/\<platform\>** folder

The overall structure should look like this:

    ├── SDKRealtimeMonitoringExample/
    │   ├── sdk/
    │   │   ├── bin/
    │   │   │   ├── x64/
    │   │   │   │   ├── libwaapi.dll
    │   │   │   │   ├── libwaresource.dll
    │   │   │   │   ├── ...
    │   │   │   └── ...
    │   │   ├── headers/
    │   │   │   └── ...
    │   │   └── lib/
    │   │       └── ...
    │   ├── utils/
    │   │   ├── json.hpp
    │   │   ├── wstring_utils.h
    │   ├── main.cpp
    |   └── ...
    ├── SDKRealtimeMonitoringExample.sln
    └── README.md --> this file

### License file and passkey
Please add your passkey in **main.cpp**

    // put your passkey here
    constexpr wa_wchar k_passkey[] = L"";

Also, place your license file in the build output folder.

### Notable configurations
Modify the target monitoring method/signature in **main.cpp** as needed.
    
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

Update the **json_in** of the method that the SDK should trigger when the monitoring method enters a negative state in **main.cpp**.

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

In this example, the default configuration monitors **GetRTPState** of **Windows Defender**. The SDK will attempt to enable it as soon as it detects that the state is false.

### How to build
1. You need to download **MetaDefender Endpoint Security SDK** and put the files correctly like this guidance.
2. Update **passkey** with the above guideline.
3. Adjust any configurations if needed.
4. Build the project with **x64-Release** config.

### OSS License
This example uses JSON for Mordern C++ (https://json.nlohmann.me/) under MIT License.
