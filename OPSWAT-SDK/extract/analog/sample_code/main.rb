#!/usr/bin/env ruby
# frozen_string_literal: true

require_relative 'get_latest_installer'
require_relative 'get_system_patches'
require_relative 'get_vuln'
require_relative 'data_reader'
require_relative 'get_system_vuln'

def show_help
  puts %(
Query client software's vulnerabilities and missing patches using Analog files and fake client data.
Usage: $ ruby main.rb [--get-patch | --get-system-patch | --get-vuln | --get-system-vuln] [--data-source analog_dir] --input-file input_file
Options:
  --get-patch
    Scan for 3rd-party software's patches.
      input_file format: {
        "os": {                     # from GetOSInfo
          "version": string,
          "architecture": string,
          "service_pack": string,
          "os_type": number,
          "os_id": number
          },
        "product": {
          "signature_id": number,   # from GetProductInfo
          "product_id": number,
          "vendor_id": number,
          "version": string,        # from GetVersion
          "architecture": string,   # architecture name from GetVersion
          "language": string        # language name from GetVersion
          }
        }

  --get-system-patch
    Show information about the system patches detected on client.
      input_file format: {
        "signature_id": number,   # OESIS signature identifier of the system software
        "patches": array<string>  # list analog_ids of missing system patches
      }

  --get-vuln
    Scan 3rd-party software's vulnerabilities.
      input_file format: {
        "os": {                      # from GetOSInfo
          "version": string,
          "architecture": string,
          "service_pack": string,
          "os_type": number,
          "os_id": number
          },
        "product": {
          "signature_id": number,    # from GetProductInfo
          "product_id": number,
          "vendor_id": number,
          "version": string,         # from GetVersion
          "channel_pattern": string, # channel pattern of the product
          "architecture": string,    # architecture name from GetVersion
          "language": string         # language name from GetVersion
          }
        }

  --get-system-vuln
    Scan system's vulnerablities.
        Windows system input_file format: {
          "os": {
            "kb_article_name": string,
            "os_type": number,
            "os_id": number
          }
        }
        Linux system input_file format: {
          "os": {
            "os_type": number,
            "os_name": string,
          },
          "package": {
            "package_name": string,
            "package_version": string
          }
        }
        macOS system input_file format: {
          "os": {
            "os_type": number,
            "os_id": number,
            "os_version": string
          }

  --data-source analog_dir
    Choose a directory to read Analog files from. By default, "./analog" directory is used.

  --input-file input_file
    Path to the JSON file containing data from client. If input_file is "-" then STDIN is used.
)
end

test_GetLatestInstaller = false
test_GetSystemPatches = false
test_GetVulnerability = false
test_GetSystemVulnerability = false
data_source = 'analog'
input_file = 'client_data.json'

if ARGV.empty?
  show_help
  exit
end

ARGV.each_index do |i|
  case ARGV[i]
  when /^--help$|^-h$/
    show_help
    exit
  when '--get-patch'
    test_GetLatestInstaller = true
  when '--get-system-patch'
    test_GetSystemPatches = true
  when /--get-vul/
    test_GetVulnerability = true
  when /--get-system-vul/
    test_GetSystemVulnerability = true
  when '--data-source'
    data_source = ARGV[i + 1]
  when '--input-file'
    input_file = ARGV[i + 1]
  end
end

if !test_GetLatestInstaller && !test_GetSystemPatches && !test_GetVulnerability && !test_GetSystemVulnerability
  puts 'Please choose an action'
  exit 1
elsif data_source.nil? || data_source.empty?
  puts 'Please input a valid data source'
  exit 1
elsif input_file.nil?
  puts 'Missing input file argument'
  exit 1
end

# load database
db = DataReader.instance
unless db.connect data_source
  puts 'Cannot read Analog files'
  exit 1
end

# load input
input = nil
begin
  input = JSON.parse(input_file == '-' ? $stdin.read : File.read(input_file))
rescue StandardError
  puts 'Cannot read input file'
  exit 1
end

if test_GetLatestInstaller
  # {
  #   "os": {                       # from GetOSInfo
  #     "version":  "10.0.19043",
  #     "architecture": '64-bit',
  #     "service_pack": "0.0",
  #     "os_type": 1,
  #     "os_id": 60
  #   },
  #   "product": {
  #    "signature_id": 813,         # from GetProductInfo
  #    "product_id": 804,
  #    "vendor_id": 41,
  #    "version": '91.77.89',       # from GetVersion
  #    "architecture": '32-bit',    # architecture name from GetVersion
  #    "language": 'fr'             # language name from GetVersion
  #   }
  # }
  print GetLatestInstaller.new(input).get_patch_info { |patch, link|
    puts %(Product: #{patch['product_name']}
    Patch id: #{patch['_id']}
    Latest version: #{patch['latest_version']}
    Download link: #{link}
    Release note: #{patch['release_note_link']}
    EULA: #{patch['eula_link']}
    Recently fixed vulnerabilities: #{patch['vulnerabilities'].empty? ? 'None' : patch['vulnerabilities'].join(',')})
  }
end

if test_GetSystemPatches
  # {
  #    "signature_id": 1103,
  #    "patches":[
  #        "f30ba29a-decf-4b18-a24e-8a63260618a1",
  #        "3a527e41-af25-42e7-8f5c-e239cb374a85"
  #    ]
  # }
  print GetSystemPatches.new(input).get_patches { |patch|
    puts %(Product: #{patch['product_name']}
    KB: #{patch['kb_id']}
    Download link: #{patch['download_link']['link']}
    Release note: #{patch['release_note_link']}
    Recently fixed vulnerabilities: #{patch['vulnerabilities'].empty? ? 'None' : patch['vulnerabilities'].join(', ')})
  }
end

if test_GetVulnerability
  # {
  #   "os": {                           # from GetOSInfo
  #     "version":  "10.0.19043",
  #     "architecture": '64-bit',
  #     "service_pack": "0.0",
  #     "os_type": 1,
  #     "os_id": 60
  #   },
  #   "product": {
  #     "signature_id": 813,            # from GetProductInfo
  #     "product_id": 804,
  #     "vendor_id": 41,
  #     "version": '91.77.89',          # from GetVersion
  #     "channel": 'Current',           # (Optional) channel of the product
  #     "architecture": '32-bit',       # architecture name from GetVersion
  #     "language": 'fr'                # language name from GetVersion
  #   }
  # }
  #
  print Scan3rdPartySoftwareVulnerability.new(input).get_list_cves { |asso|
    puts asso['cve']
  }
end

if test_GetSystemVulnerability
  GetSystemVulnerability.new(input).get_list_cves.each do |cve|
    puts cve
  end
end