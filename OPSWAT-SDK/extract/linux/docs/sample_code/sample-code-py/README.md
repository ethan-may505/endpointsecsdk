# MetaDefender Endpoint Security SDK Sample Code Python for Linux

The purpose of the this initiative is to recreate all the sample code projects that we ship with each release. This is very important because the sample code, together with the MetaDefender Endpoint Security SDK Testing Harness, is one of the first parts of the framework that our potential customers are seeing.

The users use CLI to interact with the sample code.

## Requirements

- python 3 (minimum version 3.5) 

## Features

- Call a specific method.
- Get all antivirus products and their state.
- Uninstall a product.

## Library

- Use builds released from MetaDefender Endpoint Security SDK V4:
	- OESIS_V4_nix_4_3_xxxx_0r.tar
	- OESIS_V4_nix_offline_resource_4_3_xxxx_0r.tar.
- Copy the files to the library folder ".\libs":
	- libwaapi.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwaapi.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwaapi.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwacollector.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwacollector.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwacollector.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwadeviceinfo.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwadeviceinfo.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwadeviceinfo.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwaheap.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwaheap.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwalocal.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwalocal.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwalocal.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwaresource.so : located at "OESIS_V4_nix_offline_resource_4_3_xxxx_0r\bin\"
	- libwautils.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwautils.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- libwautils.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
	- license.cfg
	- pass_key.txt with pass_key provided

## Usage

Go to source folder and run command: 
__python3 sample-code.py COMMAND OPTIONS__

### COMMAND:

- call-method : call a specific method of MetaDefender Endpoint Security SDK.
- check-av : detect all antivirus products in machine and get some information: version, RTP state, defination state, last scan time, scan state...
- remove-product : uninstall a product.

### OPTIONS:

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

