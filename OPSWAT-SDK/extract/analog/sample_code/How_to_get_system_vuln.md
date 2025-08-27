# HOW TO GET SYSTEM VULNERABILITIES

## Requirements

- Ruby >= 2.6

## Usage

1. Extract the `analog.zip` file to a folder.
2. Go to the `sample_code` folder inside the extracted folder.
3. Create a file which holds the client system info. We have provided 3 example files:
   - `client_linux_system_info.json`
   - `client_macos_system_info.json`
   - `client_windows_system_info.json`
     <br>_Note_: Each OS system requires different fields.
4. Run the following command to perform a query with the specified client data:
   ```sh
   $ ruby main.rb --get-system-vuln --input-file /path/to/client_system_info.json --data-source /path/to/analog_folder/
   ```
   Running `main.rb` without any arguments will display the usage instructions.

### Required fields for each platform

#### **Linux**

Requires **5 fields**:

- `os_name`: obtain from GetOSInfo
- `os_version`: obtain from GetOSInfo
- `os_type`: `2`
- `package_name`
- `package_version`
  <br>Package name and version of upgradable packages can be retrieved using *GetMissingPatches*. To obtain those information of all installed packages, it is recommended to use `apt list --installed` or an equivalent command for the respective package manager. Please note that even an up-to-date package can still be vulnerable to a CVE.
 <br><br>Example file: `client_linux_system_info.json`

#### **macOS**

Requires **3 fields**:

- `os_type`
- `os_id`
- `os_version`
  <br>Example file: `client_macos_system_info.json`

#### **Windows (Not recommended approach)**

Requires **3 fields**:

- `kb_article_name`
- `os_type`
- `os_id`
  <br>Example file: `client_windows_system_info.json`

For Windows, we recommend using a more effective approach with WIV.dat (Windows Vulnerability) and WUO.dat (Windows Update Offline) to achieve the best results.

## Guide

The JSON files in the `analog` package act as a database. The main code file, `main.rb`, processes user input and delegates tasks to different components. Each query requires a specific data format, which is documented at the top of its respective code file.
