# Async invoke with Event Callback example
### Project structure
Please extract the SDK engine to the **SDK** folder.  
And place **libwaresource.dylib** in **SDK-Resource** folder.

    ├── AsyncExample/
    │   ├── SDK/
    │   │   ├── bin/
    │   │   │   ├── detection/
    │   │   │   │   └── release/
    │   │   │   │           ├── libwaapi.dylib
    │   │   │   │           ├── libwautils.dylib
    │   │   │   │           └── ... 
    │   │   │   └── manageability/
    │   │   │       └── release/
    │   │   │               ├── libwalocal.dylib
    │   │   │               └── ... 
    │   │   └── inc/
    │   │       ├── wa_api.h
    |   |       └── ...
    │   ├── SDK-Resource/
    │   │   └── libwaresource.dylib
    │   ├── debug_info.h
    │   ├── json.hpp
    │   ├── main.cpp
    │   ├── timing_monitor.h
    │   ├── wstring_utils.h
    │   └── ...
    ├── AsyncExample.xcodeproj
    └── README.md --> this file

### License file and passkey
Please put your passkey key in **main.cpp**

    // put your passkey here
    constexpr wa_wchar k_passkey[] = L"";

And put your license file to the output folder.
Example: <project directory>/build/Debug

### Notable configurations
Adjust target categories in **main.cpp**
    
    // target categories for DetectProducts
    const std::vector<wa_int> k_target_categories = { WAAPI_CATEGORY_ALL };

Enable print debug info to console in **debug_info.h**

    // turn on this flag to enable debug output
    constexpr bool k_debug = false;

### How to build
1. You need to download **MetaDefender Endpoint Security SDK** (*OESIS_V4_mac_4_3_xxxx_0r.zip*) and its **Resource** (*OESIS_V4_mac_offline_resource_xxx.zip*).
2. Extract the content of the SDK zip file to the **SDK** folder. Please ensure it has the correct format with **Project Structure** above.
3. Extract **Resource** zip file and copy **libwaresource.dylib** to **SDK-Resource** folder.
4. Update **passkey** with the above guideline.
5. Adjust any configurations (target categories, debug mode) if needed.
6. Build the project with your configuration (**Debug** or **Release**).

### OSS License
This example used JSON for Mordern C++ (https://json.nlohmann.me/) under MIT License.
