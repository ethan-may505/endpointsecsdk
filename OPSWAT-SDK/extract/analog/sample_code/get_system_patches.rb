# encoding: UTF-8
# {
#   "signature_id": number,   # OESIS signature identifier of the system software
#   "patches": array<string>  # list analog_ids of missing system patches
# }

class GetSystemPatches
  attr_reader :input

  def initialize(input_js)
    @input = input_js
  end

  def get_patches
    @input['patches'].each do |patch_id|
      query_hsh_patch = {
        _id: patch_id
      }
      DataReader.instance.query('patch_system_aggregation', query_hsh_patch) do |patch|
        yield patch
      end
    end
    nil
  end
end
