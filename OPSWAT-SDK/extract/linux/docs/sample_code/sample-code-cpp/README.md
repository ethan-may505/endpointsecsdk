# MetaDefender Endpoint Security SDK Sample Code CPP for Linux

The purpose of the this initiative is to recreate all the sample code projects that we ship with each release. This is very important because the sample code, together with the MetaDefender Endpoint Security SDK Testing Harness, is one of the first parts of the framework that our potential customers are seeing.

## Features

- Call a specific method.
- Get all antivirus products and their state.
- Uninstall a product.

## Library

- Use builds released from MetaDefender Endpoint Security SDK V4.
	- OESIS_V4_nix_4_3_xxxx_0r.tar 
	-  OESIS_V4_nix_offline_resource_4_3_xxxx_0r.tar.

- Copy the library to a specific folder :
	- Library folder ".\libs" :
		+ libwaapi.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwaapi.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwaapi.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwacollector.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwacollector.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwacollector.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwadeviceinfo.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwadeviceinfo.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwadeviceinfo.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwaheap.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwaheap.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwalocal.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwalocal.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwalocal.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwaresource.so : located at "OESIS_V4_nix_offline_resource_4_3_xxxx_0r\bin\"
		+ libwautils.so : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwautils.so.4 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ libwautils.so.4.3.xxxx.0 : located at "OESIS_V4_nix_4_3_xxxx_0r\bin\detection\x64\release\"
		+ license.cfg
		+ pass_key.txt
		
	- Header folder ".\inc" :
		+ wa_api.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_config_options.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_data_types.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_defs.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_error_codes.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_fnc_ptr.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_invoke_common.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_invoke_detect.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_invoke_method.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_json_keys.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"
		+ wa_api_product_categories.h : located at "OESIS_V4_nix_4_3_xxxx_0r\inc\"


## Build
The users use CLI to interact with the sample code.

### Toolchain
The solution is typically built with GCC-5.3. We know this toolchain works, and want to continue using it. Newer toolchains may cause problematic
symbol resolution, older toolchains may not support sufficient C++ features.

### Troubleshooting
If you see an error during build that says something like Critical Error: signing verification is disabled - you may ignore it on your build system; This
is done in order to fail TC builds which attempt to build release binaries that are not doing signature verification.

Most of the build errors that you may see would come from using a different toolchain than the ones used to build. Our aim is to ensure that MetaDefender Endpoint Security SDK V4 linux
can be compatible with as many distros as possible, while remaining closed source. Therefore, any issues should be remediated by ensuring the correct toolchain is used.

Standard build configuration during development was:
OS: CentOS7 64bit
Tools: tmux/vim/cmake/make/gcc
Utils (things to install):
- scl
- devtoolset-4 (to use GCC 5.3, because CentOS7 by default comes with GCC 4.8)
- cmake3

Devtoolset-4 can be activated in bash by doing this:
scl enable devtoolset-4 bash

The above command opens bash in bash (like any other program) - but it targets GCC 5.3.

Note: building 32-bit on CentOS7 64bit requires that you have the libstdc++ for i686. This is not in default yum repositories. This can be done by installing 4.8 version
of libstdc++ for i686, and then installing devtoolset-4-libstdc++-devel-5.3.1-6.1.el7.i686.rpm (which can be acquired online, like here: https://casa.nrao.edu/download/repo/el7/x86_64/devtoolset-4-libstdc++-devel-5.3.1-6.1.el7.i686.rpm, or here: http://public-yum.oracle.com/repo/OracleLinux/OL7/SoftwareCollections/x86_64/getPackage/devtoolset-4-libstdc++-devel-5.3.1-6.1.el7.i686.rpm, or from RHN - but that requires RedHat subscription).

## Below are instructions on how to build different configurations:

--------------------
### Release 64-bit
--------------------
```
cd sample-code-cpp
mkdir build
cmake3 -DCMAKE_BUILD_TYPE=Release ..
make
```
--------------------
### Release 32-bit
--------------------
```
cd sample-code-cpp
mkdir build
cmake3 -DCMAKE_BUILD_TYPE=Release -DARCHITECTURE_32=ON ..
make
```

## Usage
Noted: The first need to set file pass_key.txt same folder with sample-code-cpp.

Go to the build folder and run command: 
__./sample-code-cpp COMMAND OPTIONS__

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
--timeframe : the timeframe in days used to determine if the update is recent
--operation : the operation to be perform.
--password : the password required by the product to modify the application state.
--user : the user required by the product to modify the application state.
--vm_id : the identification of VM that was recieved from the call.
--token : token string to download files.
--source_file : input database if to be cosumed from a file location.
--checksum_file : input database if to be cosumed from a file location.
--timeout : a timeout value in seconds that can be set to this api call.
--os_id : MetaDefender Endpoint Security SDK identifier of the OS.
--tolerance : a tolerance factor that can be used to loosen the 'is_current' metric.
--online : a timeout value in seconds that can be set to this api call.
```