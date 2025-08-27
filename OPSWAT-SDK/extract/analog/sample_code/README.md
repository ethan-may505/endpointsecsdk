# Sample code

## Introduction

This sample code project helps users understand the components of Analog (database files for server and client) and how to use them together with OESIS to satisfy a common use case of detecting vulnerabilities on clients and deploying patches to fix them, all triggered from a central server.
The sample code uses Ruby language.

## Requirement

Ruby >= 2.6

## Usage

1. Extract file analog.zip to the current folder
2. Create file client-data.json as fake client data.
3. Run command: ```$ ruby main.rb  [--get-patch|--get-system-patch|--get-vuln] --data-source analog_dir --input-file client_data.json``` to perform a query with the specified client data. Running main.rb without any argument shows usage instruction.

## Hacking guide

The main code file is main.rb, which receives input and delegates processing to other files. The most important input is sample data from a client (client_data.json). Different queries require different data; for example: --get-patch and --get-vuln require OS and product information, --get-system-patch requires analog_ids from GetLatestInstaller when using Windows Update Offline (WUO) feature. The specific data format required for each query is documented at the top of the corresponding code file.
The JSON files in Analog package serve as a database. File data_reader.rb implements the readerfor them.

Files list:

- main.rb                               main file
- data_reader.rb                        database reader
- get_vuln.rb                           perform vulnerability query
- get_latest_installer.rb               perform patch query for 3rd-party products
- get_system_patches.rb                 perform patch query for system products
- client_data.json                      sample client data for --get-patch and --get-vuln
- client_data_channel.json              sample client data for --get-vuln with 'channel' field exists
- client_system_data.json               sample client data for --get-system-patch
- utils
- |_version.rb                          parse version string and compare versions
- |_range.rb                            process version range

Update news:

v1.1:
- Use the new field "arch" in the schema "patch_associaiton" version 1.1 to select patch_aggregation.
- Use the new field "channel_pattern" in the schema "patch_association" version 1.2 to select patch_aggregation.

v1.2:
- Use the new field "channel_pattern" in the schema "vuln_association" version 1.1 to select channel_pattern
