# frozen_string_literal: true

require 'json'
require 'singleton'

class DataReader
  include Singleton

  attr_reader :analog_dir

  def connect(analog_dir)
    # select a directory for Analog files and validate it lightly
    @analog_dir = analog_dir
    File.exist?("#{@analog_dir}/header.json") &&
      File.exist?("#{@analog_dir}/server") &&
      File.exist?("#{@analog_dir}/server/patch_associations.json") &&
      File.exist?("#{@analog_dir}/server/patch_aggregation.json") &&
      File.exist?("#{@analog_dir}/server/patch_system_aggregation.json") &&
      File.exist?("#{@analog_dir}/server/vuln_associations.json") &&
      File.exist?("#{@analog_dir}/server/cves.json") &&
      File.exist?("#{@analog_dir}/server/products.json")
  end

  def query(file_name, filter)
    # query an Analog datafile (JSON) using a filter hash that supports dot notation
    read_file_data("#{@analog_dir}/server/#{file_name}.json") do |ele|
      pass = true # whether ele passed the filter
      filter.each_key do |key|
        key_arr = key.to_s.split('.')
        json_object = ele.dig(*key_arr)
        if json_object.is_a?(Array)
          unless json_object.include?(filter[key])
            pass = false
            break
          end
        elsif json_object != filter[key]
          pass = false
          break
        end
      end
      yield ele if pass
    end
  end

  def read_file_data(path)
    # read an Analog file, but ignore header
    data = JSON.parse File.read(path)
    data['oesis'].each do |ele|
      ele.each_key do |key|
        next if key == 'header'

        ele[key].each_key do |id|
          yield(ele[key][id])
        end
      end
    end
  end
end
