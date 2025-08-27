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

# check file products and vuln_associations
products_data = parse_json(File.read("#{file_path}/server/products.json"))['oesis'][1]
v4_pids = Set.new
v4_signatures = Set.new
products_data['products'].each_value do |value|
  v4_pids << value["product"]["id"]
  value["signatures"].each {|sig|
    v4_signatures << sig['id']
  }
end

vuln_associations = parse_json(File.read("#{file_path}/server/vuln_associations.json"))['oesis'][1]
vuln_asso_v4_pids = Set.new
vuln_asso_v4_signatures = Set.new
vuln_asso_cves = Set.new
vuln_associations.each_value do |vuln_associations_value|
  vuln_associations_value.each_value do |value|
    vuln_asso_v4_pids.merge(value['v4_pids'])
    vuln_asso_cves << value['cve']
    vuln_asso_v4_signatures.merge(value['v4_signatures']) if value['v4_signatures']
  end
end

miss_v4pid = vuln_asso_v4_pids - v4_pids
vuln_asso_v4_pids.clear
v4_pids.clear
if miss_v4pid.size > 0
  puts "products missing list v4_pids: #{miss_v4pid.to_a.join(', ')}"
  status = 1
end

miss_v4sid = vuln_asso_v4_signatures - v4_signatures
vuln_asso_v4_signatures.clear
v4_signatures.clear
if miss_v4sid.size > 0
  puts "products missing list v4_signatures: #{miss_v4sid.to_a.join(', ')}"
  status = 1
end

# check file vuln_associations and cves
cves = parse_json(File.read("#{file_path}/server/cves.json"))['oesis'][1]
cves_ids = Set.new
cves.each_value do |cves_value|
  cves_ids.merge(cves_value.keys)
end

miss_cves = vuln_asso_cves - cves_ids
vuln_asso_cves.clear
cves_ids.clear
if miss_cves.size >= 1
  puts "cves missing list cves: #{miss_cves.to_a.join(', ')}"
  status = 1
end

# check file patch_associations and patch_aggregations
patch_association = JSON.parse(File.read("#{file_path}/server/patch_associations.json"))['oesis'][1]
patch_id_asso = Set.new
patch_association.each_value do |patch_association_value|
  patch_association_value.each_value do |value|
    patch_id_asso << value['patch_id']
  end
end

patch_aggre = JSON.parse(File.read("#{file_path}/server/patch_aggregation.json"))['oesis'][1]
patch_id_patch_aggre = Set.new
patch_aggre.each_value do |patch_aggre_value|
  patch_id_patch_aggre = patch_aggre_value.keys.map(&:to_i).to_set
end

miss_patchs = patch_id_asso - patch_id_patch_aggre
if miss_patchs.size >= 1
  puts "patch_aggregations missing list patch: #{miss_patchs.to_a.join(', ')}"
  status = 1
end

puts 'Success' if status.zero?
exit status
