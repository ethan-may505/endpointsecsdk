#! /usr/bin/env ruby
# frozen_string_literal: true

require 'digest'
require_relative 'utility'

file_path = "#{__dir__}/.."
compliance_files = ["windows/bin/libwaresource.dll", "mac/bin/libwaresource.dylib", "linux/bin/arm64/libwaresource.so", "linux/bin/x64/libwaresource.so", "linux/bin/x86/libwaresource.so"]
ARGV.each_index do |i|
  case ARGV[i]
  when '--data-source'
    file_path = ARGV[i + 1]
  end
end

header_js = parse_json(File.read("#{file_path}/header.json"))
file_checksums = {}
header_js['oesis'][1]['files'].each do |key, value|
  file_checksums[key] = value
end

status = 0
files = []

# get all files from compliance package
compliance_files.each do |file|
  full_path = "#{file_path}/client/compliance/#{file}"
  if File.exist?(full_path)
    sha256 = Digest::SHA256.file full_path
    file_name = File.basename(full_path)
    files << file_name

    # Get the checksum from header for linux compliance
    if file.include?"linux"
      arch = file.split('/')[2]
      if file_checksums[file_name][arch]['sha256'] != sha256.to_s
        puts "File #{file_name} invalid checksum"
        status = 1
      end
    else
      if file_checksums[file_name]['sha256'] != sha256.to_s
        puts "File #{file_name} invalid checksum"
        status = 1
      end
    end
  else
    puts "File #{file_path}/client/compliance/#{file} not exist from compliance package"
    status = 1
  end
end

# get all file in client and server
Dir["#{file_path}/server/*", "#{file_path}/client/*"].reject { |file| file.include?("#{file_path}/client/compliance") }.each do |file|
  sha256 = Digest::SHA256.file file
  file_name = File.basename(file)
  files << file_name
  if file_checksums[file_name]['sha256'] != sha256.to_s
    puts "File #{file} invalid checksum"
    status = 1
  end
end

if file_checksums.keys.sort != files.sort.uniq
  common = file_checksums.keys && files
  all_diff = (file_checksums.keys - common) | (files - common)
  puts "Missing server or client file(s): #{all_diff.to_a.join(', ')}"
  status = 1
end
puts 'Success validate checksum files' if status.zero?
exit status
