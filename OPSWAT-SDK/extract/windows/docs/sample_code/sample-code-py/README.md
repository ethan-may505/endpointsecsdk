# MDES SDK Sample Code Python for Windows

The purpose of the this initiative is to recreate all the sample code projects that we ship with each release. This is very important because the sample code, together with the MDES SDK Testing Harness, is one of the first parts of the framework that our potential customers are seeing.

The users use CLI to interact with the sample code.

----------------------------------------------------------------------------------------------------------------------------------------------------------

## Requirements

- python 3 (minimun version 3.5) 

----------------------------------------------------------------------------------------------------------------------------------------------------------

## Features

- Call a specific method.
- Get all antivirus products and their state.
- Get vulnerabilities of all products.
- Download and install the lastest product.
- Uninstall a product.
- Data Loss Protection.

----------------------------------------------------------------------------------------------------------------------------------------------------------

## Library

- Use builds released from MDES SDK V4:
	- OESIS_V4_4_3_2253_0r.zip
	- OESIS_V4_offline_resource_4_3_2253_0r.zip.
- Copy the library to the libs folder:
	+ commondb.db : located at "OESIS_V4_4_3_xxxx_0r\bin\infection\x64\release\"
	+ libwaaddon.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\detection\x64\release\"		
	+ libwaapi.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\detection\x64\release\"
	+ libwacollector.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\diagnostics\x64\release\"
	+ libwadeviceinfo.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\deviceinfo\x64\release\"
	+ libwadlp.dll : localed at "OESIS_V4_4_3_xxxx_0r\bin\dlp\x64\release\"
	+ libwadriver.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\wadriver\x64\release\"
	+ libwaheap.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\detection\x64\release\"
	+ libwainfection.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\infection\x64\release\"
	+ libwalocal.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\manageability\x64\release\"
	+ libwanetscan.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\netscan\x64\release\"
	+ libwaremoval.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\removal\x64\release\"
	+ libwaresource.dll : located at "OESIS_V4_offline_resource_4_3_xxxx_0r\bin\"
	+ libwautils.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\detection\x64\release\"
	+ libwavmodapi.dll : located at "OESIS_V4_4_3_xxxx_0r\bin\vulnerability\x64\"
	+ patch.dat : located at "OESIS_V4_offline_resource_4_3_xxxx_0r\bin\vulnerability\"
	+ scap-db-all.dat : located at "OESIS_V4_offline_resource_4_3_xxxx_0r\bin\vulnerability\"
	+ vhsh.dat : located at "OESIS_V4_offline_resource_4_3_xxxx_0r\bin\vulnerability\"		
	+ vmod.dat : located at "OESIS_V4_offline_resource_4_3_xxxx_0r\bin\vulnerability\"
	+ wa_3rd_party_host_32.exe : located at "OESIS_V4_4_3_xxxx_0r\bin\manageability\x64\release\"
	+ wa_3rd_party_host_64.exe : located at "OESIS_V4_4_3_xxxx_0r\bin\manageability\x64\release\"
	+ libwaapi.lib : located at "OESIS_V4_4_3_xxxx_0r\lib\x64\release\"		
	+ license.cfg --+ this file is provided to customers from MDES SDK.
	+ pass_key.txt --+ create this file and import pass_key provided from MDES SDK.

----------------------------------------------------------------------------------------------------------------------------------------------------------

## Usage

Go to source folder and run command: 
__python sample\_code.py COMMAND OPTIONS__

### COMMAND:

- call-method : call a specific method of MDES SDK.
- check-av : detect all antivirus products in machine and get some information: version, RTP state, defination state, last scan time, scan state...
- check-vuln : detect all products in machine and get some information: version, product patch level, product vulnerabilities, lastest installer url,..
- patch-product : download and install lastest version of a product.
- remove-product : uninstall a product.
- dlp : including anti keylogger and anti screen capture.

### OPTIONS:

Support for call a specific method with its param:
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
--source_file : input database if to be cosumed from a file location.
--checksum_file : input database if to be cosumed from a file location.
--timeout : a timeout value in seconds that can be set to this api call.
--os_id : MDES SDK identifier of the OS.
--tolerance : a tolerance factor that can be used to loosen the 'is_current' metric.
--online : a timeout value in seconds that can be set to this api call.
```
