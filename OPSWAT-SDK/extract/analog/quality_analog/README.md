# Sample code

## Introduction
This sample project code helps customers to check/validate Analog files, helps to test common use cases, check references between files.
The sample code uses Ruby language.

## Requirement
Ruby >= 2.6

## Usage
1. Extract file analog.zip to the current folder
2. Run command: ```$ ruby main.rb  [--check-soft-linker | --check-hard-linker | --check-linker | --validate-schema | --validate] --data-source <analog_dir> ``` to check and validate data of Analog. Running main.rb without any argument shows usage instruction.

## Hacking guide
The main code file is main.rb, which receives input and delegates processing to other files.

File list:
- quality_analog
- |_main.rb                 main file
- |_validate_checksums.rb   validate sha256 of each file in server and client folder
- |_validate_schema.rb      validate schema of each file
- |_hard_linker.rb          check link must exist
- |_soft_linker.rb          check link should exist
- |_shema
-   |_cves.json
-   |_header.json
-   |_patch_aggregation.json
-   |_patch_associations.json
-   |_patch_associations_1.1-1.1.json 
-   |_patch_associations_1.2-1.2.json
-   |_patch_system_aggregation.json
-   |_products.json
-   |_vuln_associations.json

## Update news:
v1.0:
- First release.
