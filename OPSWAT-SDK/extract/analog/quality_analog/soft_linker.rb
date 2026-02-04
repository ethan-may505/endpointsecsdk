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

cves = parse_json(File.read("#{file_path}/server/cves.json"))['oesis'][1]
cve_ids = Set.new
cves.each_value do |cves_value|
  cve_ids.merge(cves_value.keys)
end
cves.clear

# check cves in patch_aggregations and cves
patch_aggre = parse_json(File.read("#{file_path}/server/patch_aggregation.json"))['oesis'][1]
patch_cves = Set.new
patch_aggre.each_value do |patch_aggre_value|
  patch_aggre_value.each_value do |value|
    patch_cves.merge(value['vulnerabilities'])
  end  
end
patch_aggre.clear

miss_cves = patch_cves - cve_ids
if miss_cves.size >= 1
  puts "following cves can be found in patch_aggregations.json but not in cve.json: #{miss_cves.to_a.join(', ')}"
  status = miss_cves.size > 20 ? 2 : 1
end

# check cves in patch_system_aggregation and cves
patch_sys_aggre = parse_json(File.read("#{file_path}/server/patch_system_aggregation.json"))['oesis'][1]
patch_sys_cves = Set.new
patch_sys_aggre.each_value do |patch_sys_aggre_value|
  patch_sys_aggre_value.each_value do |value|
    patch_sys_cves.merge(value['vulnerabilities'])
  end
end
patch_sys_aggre.clear

miss_sys_cves = patch_sys_cves - cve_ids
if miss_sys_cves.size >= 1
  puts "following cves can be found in patch_system_aggregation.json but not in cve.json: #{miss_sys_cves.to_a.join(', ')} "
  status = miss_sys_cves.size > 200 ? 2 : 1
end

puts 'Success' if status.zero?
exit status
