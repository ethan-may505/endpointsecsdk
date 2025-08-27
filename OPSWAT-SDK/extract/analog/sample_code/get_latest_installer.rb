# frozen_string_literal: true

require_relative 'utils/version'
require_relative 'utils/range'
require_relative 'data_reader'

class GetLatestInstaller
  attr_reader :input

  def initialize(input_js)
    @input = input_js
  end

  def is_os_in_range(range, os_id, os_version)
    # check if the customer's operating system can apply this patch
    # range can be OS range version or OS id
    # os_id is integer number
    ver_os_version = Version.new os_version
    regex = /([\(\[]-?[\d\.]+,\s*-?[\d\.]+[\)\]])/
    matches = range.scan(regex)
    return true if matches.size.zero?
    matches.each do |match|
      flag = false
      split_ranges = match[0].split(',')
      s = split_ranges[0].strip   # start
      e = split_ranges[1].strip   # end

      if s[0] == '['
        # check "s" is os_id or os_version
        if s.match?(/[^-0123456789\[]/) # a version
          start = Version.new s[1..-1]
          flag = true if ver_os_version >= start
        else
          start = s[1..-1].to_i
          flag = true if start == -2 || os_id >= start
          # -2 means unlimited
        end
      end
      if s[0] == '('
        # check "s" is os_id or os_version
        if s.match?(/[^-0123456789\(]/) # a version
          start = Version.new s[1..-1]
          flag = true if ver_os_version > start
        else
          start = s[1..-1].to_i
          flag = true if start == -2 || os_id > start
          # -2 means unlimited
        end
      end

      if e[-1] == ']'
        # check "s" is os_id or os_version
        if e.match?(/[^-0123456789\]]/) # a version
          vend = Version.new e[0..-2]
          return true if (ver_os_version <= vend) && flag
        else
          vend = e[0..-2].to_i
          return true if (vend == -2 || os_id <= vend) && flag
          # -2 means unlimited
        end
      end
      if e[-1] == ')'
        # check "s" is os_id or os_version
        if e.match?(/[^-0123456789\)]/) # a version
          vend = Version.new e[0..-2]
          return true if ver_os_version < vend
        else
          vend = e[0..-2].to_i
          return true if (vend == -2 || os_id < vend) && flag
          # -2 means unlimited
        end
      end
    end
    false
  end

  def is_version_in_range(range, version)
    # return true if product version is in range, false otherwise
    ver = Version.new(version)

    unless range['start'].nil?
      s = Version.new(range['start'])
      return false if ver < s
    end
    unless range['limit'].nil?
      e = Version.new(range['limit'])
      return false if ver > e
    end
    true
  end

  def get_association
    # find the association matching the client data
    # return 2 values: result association (nil if error), error string (nil in case of success)
    # client data format:
    # {
    #   "os": {                      # from GetOSInfo
    #     "version": string,
    #      "architecture": string,
    #      "service_pack": string,
    #      "os_type": number,
    #      "os_id": number
    #   },
    #   "product": {
    #      "signature_id": number,   # from GetProductInfo
    #      "product_id": number,
    #      "vendor_id": number,
    #      "version": string,        # from GetVersion
    #      "architecture": string,   # architecture name from GetVersion
    #      "language": string        # language name from GetVersion
    #   }
    # }

    query_hsh_asso = {
      'v4_pid' => input['product']['product_id'],
      'v4_signatures' => input['product']['signature_id']
    }
    asso_maps = []
   
    # support new version patch_associations_1.1 patch_associations_1.2
    DataReader.instance.query('patch_associations', query_hsh_asso) do |asso|
      if asso['os_allow']
        next unless is_os_in_range asso['os_allow'], input['os']['os_id'], input['os']['version']
      end
      if asso['os_deny']
        next if is_os_in_range asso['os_deny'], input['os']['os_id'], input['os']['version']
      end
      next if asso['version_pattern'] && !input['product']['version'].match?(asso['version_pattern'])
      next if asso['arch'] && asso['arch'] != input['product']['architecture']
      next if asso['channel_pattern'] && !input['product']['channel'].match?(asso['channel_pattern'])
      if asso['ranges']
        asso['ranges'].each do |range|
          if is_version_in_range range, input['product']['version']
            asso_maps << asso
            break
          end
        end
      else
        asso_maps << asso
      end
    end

    # if there are many associations (patch identifiers) to choose from
    # then prefer the patch that updates the software to the latest version
    # or just use the first patch if no such patch exists
    latest_count = asso_maps.count { |a| a['is_latest'] }
    if latest_count > 1
      [nil, 'Product is not supported'] # this case shouldn't happen so it's best to avoid returning it
    elsif latest_count == 1
      asso_maps.detect { |asso| asso['is_latest'] }
    elsif asso_maps.size > 0
      asso_maps[0]
    else
      [nil, 'Product is not supported']
    end
  end

  def get_download_link(association)
    # get download link for the patch applicable to the client software
    # return 2 values: download link (nil if error), error string (nil if success)
    query_hsh_patch = { '_id' => association['patch_id'] }
    asso_maps = []
    DataReader.instance.query('patch_aggregation', query_hsh_patch) do |patch|
      return  [nil, 'Patch suport download script or install', true] if patch['download_links'].length < 1 
      patch['download_links'].each do |link|
        next if link['architecture'] && link['architecture'] != @input['product']['architecture']
        next if link['os_architecture'] && link['os_architecture'] != @input['os']['architecture']
        next if link['os_id'] && !link['os_id'].include?(@input['os']['os_id'])

        plang = @input['product']['language'].downcase
        next if !plang.empty? && link['language'] &&
                link['language'].downcase != plang.downcase &&
                link['language'].downcase != plang.split('-')[0].downcase # strip locale code if it exists
        next if plang.empty? && link['language'] && patch['language_default'] &&
                patch['language_default'].downcase != link['language'].downcase # if OESIS cannot detect client software's language then use the default language

        return link['link']
      end
    end

    [nil, 'Patch not found', false]
  end

  def get_patch_info
    asso, error = get_association
    return error if error

    link, error, status = get_download_link asso
    return error if status == false
    puts error if error


    DataReader.instance.query('patch_aggregation', { _id: asso['patch_id'] }) do |patch|
      yield patch, link
    end
    nil
  end
end