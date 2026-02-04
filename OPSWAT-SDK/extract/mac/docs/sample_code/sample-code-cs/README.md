# MetaDefender Endpoint Security SDK Sample Code C# for macOS

The purpose of the this initiative is to recreate all the sample code projects that we ship with each release. This is very important because the sample code, together with the MetaDefender Endpoint Security SDK Testing Harness, is one of the first parts of the framework that our potential customers are seeing.

The users use CLI to interact with the sample code.

## Requirements

- .NET SDK 3.1
- Visual Studio Code

## Features

- Call a specific method.
- Get all antivirus products and their state.
- Uninstall a product.

## Library

- Use builds released from MetaDefender Endpoint Security SDK V4: 
    - OESIS_V4_mac_4_3_xxxx.zip 
    - OESIS_V4_mac_offline_resource_4_3_xxxx_0r.zip.
- Copy the files to a specific folder :
    - Library folder ".\libs":
        + libwaadbrowser.dylib 		: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\advancedbrowser\release\"
        + libwaapi.dylib 			: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\detection\release\"
		+ libwaaddon.dylib 			: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\detection\release\"
		+ libwautils.dylib			: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\detection\release\"
		+ libwadeviceinfo.dylib 	: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\deviceinfo\release\"
		+ libwacollector.dylib		: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\diagnostics\release\"
		+ libwainfection.dylib		: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\infection\release\"
		+ libwalocal.dylib 			: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\manageability\release\"
		+ libwaremoval.dylib		: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\removal\release\"
		+ libwavmodapi.dylib		: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\vulnerability\release\"
		+ libwadriver.dylib 		: located at "OESIS_V4_mac_4_3_xxxx_0r\bin\driver\release\"
		+ libwaresourece.dylib 		: located at "OESIS_V4_mac_offline_resource_4_3_xxxx_0r\bin\"
		+ patch_mac.dat 			: located at "OESIS_V4_mac_offline_resource_4_3_xxxx_0r\bin\vulnerability\"
		+ vhsh.dat					: located at "OESIS_V4_mac_offline_resource_4_3_xxxx_0r\bin\vulnerability\"
		+ vmod.dat					: located at "OESIS_V4_mac_offline_resource_4_3_xxxx_0r\bin\vulnerability\"

    - Header folder ".\inc" :
		+ wa_api.h 						: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_config_options.h 		: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_data_types.h 			: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_defs.h 				: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		- wa_api_error_codes.h 			: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_fnc_ptr.h 				: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_invoke_common.h 		: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_invoke_detect.h 		: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_invoke_method.h 		: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_jdylibn_keys.h 		: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"
		+ wa_api_product_categories.h 	: located at "OESIS_V4_mac_4_3_xxxx_0r\inc\"

    - Vunerability folder ".\inc\vmod" :
		+ wa_vmod_api.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"
		+ wa_vmod_api_config_options.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"
		+ wa_vmod_api_data_types.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"
		+ wa_vmod_api_defs.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"
		+ wa_vmod_api_error_codes.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"
		+ wa_vmod_api_fnc_ptr.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"
		+ wa_vmod_api_invoke_common.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"
		+ wa_vmod_api_invoke_query.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"
		+ wa_vmod_api_json_keys.h : located at "OESIS_V4_mac_4_3_xxxx_0r\inc\vmod\"

	- License folder ".\license" :
		+ license.cfg
		+ pass_key.txt with pass_key provided
        
- Open Project with Visual Studio Code and .NET.

- Build project with Visual Studio Code and .NET.

## Usage

__sample-code-cs COMMAND OPTIONS__

### COMMAND:

- call-method : call a specific method of MetaDefender Endpoint Security SDK.
- check-av : detect all antivirus products in machine and get some information: version, RTP state, defination state, last scan time, scan state...
- remove-product : uninstall a product.

### OPTION:  

Support for call a specific method with its param
```
--file : call method by using file.
--id : the method id of the product.
--name : the method name of the product.
--sig : the signature id of the product.
--category : the category id of the product.
--scan_type : the type of scan to get the time.
--path : the full path to a file, or folder.
--clean : clean threats detected during the scan.
--timeframe : the timeframe in days used to determine if the update is recent.
--operation : the operation to be perform.
--password : the password required by the product to modify the application state.
--user : the user required by the product to modify the application state.
--vm_id : the identification of VM that was recieved from the call.
--token : token string to download files.
--dyliburce_file : input database if to be cosumed from a file location.
--checksum_file : input database if to be cosumed from a file location.
--timeout : a timeout value in seconds that can be set to this api call.
--os_id : MetaDefender Endpoint Security SDK identifier of the OS.
--tolerance : a tolerance factor that can be used to loosen the 'is_current' metric.
--online : a timeout value in seconds that can be set to this api call.
```
