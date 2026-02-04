# Async invoke with Event Callback example
### Project structure
Please extract the SDK engine to the **SDK** folder.  
And place **libwaresource.dll** in **SDK-Resource** folder.

    ├── AsyncExample/
    │   ├── SDK/
    │   │   ├── bin/
    │   │   │   ├── detection/
    │   │   │   │   ├── x64/
    │   │   │   │   │   └── release/
    │   │   │   │   │       ├── libwaapi.dll
    │   │   │   │   │       ├── libwautils.dll
    │   │   │   │   │       └── ...
    │   │   │   │   └── ...
    │   │   │   └── ...
    │   │   ├── inc/
    │   │   │   └── ...
    │   │   └── lib/
    │   │       └── ...
    │   ├── SDK-Resource/
    │   │   └── libwaresource.dll
    │   ├── debug_info.h
    │   ├── json.hpp
    │   ├── main.cpp
    │   ├── timing_monitor.h
    │   ├── wstring_utils.h
    │   └── ...
    ├── AsyncExample.sln
    └── README.md --> this file

### License file and passkey
Please put your passkey key in **Source.cpp**

    // put your passkey here
    constexpr wa_wchar k_passkey[] = L"";

And put your license file to the output folder.

### Notable configurations
Adjust target categories in **Source.cpp**
    
    // target categories for DetectProducts
    const std::vector<wa_int> k_target_categories = { WAAPI_CATEGORY_ALL };

Enable print debug info to console in **debug_info.h**

    // turn on this flag to enable debug output
    constexpr bool k_debug = false;

### How to build
1. You need to download **MetaDefender Endpoint Security SDK** (*OESIS_V4_4_3_xxxx_0r.zip*) and its **Resource** (*OESIS_V4_offline_resource_xxx.zip*).
2. Extract the content of the SDK zip file to the **SDK** folder. Please ensure it has the correct format with **Project Structure** above.
3. Extract **Resource** zip file and copy **libwaresource.dll** to **SDK-Resource** folder.
4. Update **passkey** with the above guideline.
5. Adjust any configurations (target categories, debug mode) if needed.
6. Build the project with **x64-Release** config.

### OSS License
This example used JSON for Mordern C++ (https://json.nlohmann.me/) under MIT License.
