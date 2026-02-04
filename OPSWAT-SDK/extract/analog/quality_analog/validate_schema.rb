#! /usr/bin/env ruby
# frozen_string_literal: true

require 'digest'
require_relative 'utility'

file_path = "#{__dir__}/.."

ARGV.each_index do |i|
  case ARGV[i]
  when '--data-source'
    file_path = ARGV[i + 1]
  end
end
status = 0

# get all file in server and validate schema
Dir["#{file_path}/server/*"].each do |file|
  file_js = parse_json(File.read(file))
  
  # Check schema for ap_support_chart file
  if file.include? 'ap_support_chart'
    schema = File.read("#{__dir__}/schema/support_chart_schema.json")
    rs = JSON::Validator.validate(schema, file_js)
    next if rs
    
    puts 'Failed validation for schema support_chart_schema.json'
    break
  end

  if file.include? 'patch_status'
    schema = File.read("#{__dir__}/schema/patch_status.json")
    rs = JSON::Validator.validate(schema, file_js)
    next if rs
    
    puts 'Failed validation for schema patch_status.json'
    break
  end

  if file.include? 'kb_info'
    schema = File.read("#{__dir__}/schema/kb_info.json")
    rs = JSON::Validator.validate(schema, file_js)
    next if rs

    puts 'Failed validation for schema kb_info.json'
    status = 1
    break
  end


  # Check schema for other json file
  file_js['oesis'][1].each do |key, value|
    file_schema = key
    file_schema = "#{key}-#{key.split('_')[-1]}" if key.split('_')[-1].match?(/\d+\.\d+/)
    schema = File.read("#{__dir__}/schema/#{file_schema}.json")
    value.each_value do |element|
      rs = JSON::Validator.validate(schema, element)
      next if rs

      puts "Failed validation for schema #{file_schema}.json "
      status = 1
      break
    end
  end
end

puts 'Success validate schema for each file' if status.zero?
exit status
