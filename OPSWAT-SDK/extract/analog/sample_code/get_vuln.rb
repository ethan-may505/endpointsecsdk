# frozen_string_literal: true

# {
#   "os": {                        # from GetOSInfo
#     "version": string,
#     "architecture": string,
#     "service_pack": string,
#     "os_type": number,
#     "os_id": number
#   },
#   "product": {
#     "signature_id": number,   # from GetProductInfo
#     "product_id": number,
#     "vendor_id": number,
#     "version": string,        # from GetVersion
#     "channel": string         # (Optional) channel of the product
#     "architecture": string,   # architecture name from GetVersion
#     "language": string        # language name from GetVersion
#   }
# }

require_relative 'utils/version'
require_relative 'utils/range'

class Scan3rdPartySoftwareVulnerability
  attr_reader :input

  def initialize(input_js)
    @input = input_js
  end

  def is_version_in_range(range, version)
    rang_obj = Range.new(range['start'], range['limit'])
    rang_obj.is_in_range(version)
  end

  def channels_match?(product, association)
    return true unless association.has_key?('channel_pattern')
    return false unless product.has_key?('channel')
    return product['channel'].match?(association['channel_pattern'])
  end

  def get_list_cves
    query_hsh_asso = {
      'v4_pids' => input['product']['product_id'],
      'os_type' => input['os']['os_type']
    }

    DataReader.instance.query('vuln_associations', query_hsh_asso) do |asso|
      # Next if 'channel' not match 'channel_pattern'
      next if not channels_match?(input['product'], asso)

      # Next if 'signature' or 'channel pattern' is not available in both input and output
      next if (asso['v4_signatures'] && !(asso['v4_signatures'].include?(input['product']['signature_id'])))

      asso['ranges'].each do |range|
        if is_version_in_range range, input['product']['version']
          yield asso # This vulnerability affects the product
          break
        end
      end
    end
    nil
  end
end
