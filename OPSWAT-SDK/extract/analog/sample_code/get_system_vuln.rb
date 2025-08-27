# frozen_string_literal: true

require_relative 'utils/compare_linux_version'
require_relative 'utils/version'
require_relative 'utils/linux_os_info'


class GetSystemVulnerability
  attr_reader :input
  
  def initialize(input_js)
    @input = input_js
    @OS_TYPE_WINDOWS = 1
    @OS_TYPE_LINUX = 2
    @OS_TYPE_MACOS = 4
  end

  def get_list_cves

    case @input['os']['os_type']
    when @OS_TYPE_WINDOWS
      return get_list_cves_windows
    when @OS_TYPE_LINUX
      return get_list_cves_linux
    when @OS_TYPE_MACOS
      return get_list_cves_macos
    else
      puts 'Please provide a valid OS type of neither 1, 2, nor 4'
      return nil
    end
  end

  def get_list_cves_windows
    query_hsh = { os_type: input['os']['os_type'] }
    input_os_id = @input['os']['os_id']
    input_kb_article_name = @input['os']['kb_article_name']
    cves_list = []

    DataReader.instance.query('vuln_system_associations', query_hsh) do |asso|
      cve_id = asso['cve']
      asso['kb_articles'].each do |kb_article|
        next unless kb_article['article_name'] == input_kb_article_name && kb_article['os_id'].include?(input_os_id)

        cves_list.push(cve_id)
        break
      end
    end

    cves_list
  end

  def get_list_cves_linux
    query_hsh = { os_type: @input['os']['os_type'] }
    input_os_name = normalize_os_info(@input['os']['os_name'], @input['os']['os_version'])[1]
    input_package_name = @input['package']['package_name']
    input_package_version = @input['package']['package_version']
    cves_list = []

    DataReader.instance.query('vuln_system_associations', query_hsh) do |asso|
      cve_id = asso['cve']

      asso['affected_os'].each do |affected_os|
        next unless affected_os['os_name'] == input_os_name

        match = false

        affected_os['affected_packages'].each do |affected_package|
          next unless affected_package['package_name'] == input_package_name

          affected_package['ranges'].each do |range|
            next unless is_linux_package_version_in_range?(input_package_version, range)

            match = true
            cves_list.push(
              {
                package_name: input_package_name,
                cve: cve_id,
                fix_version: range['limit_except'] || 'N/A'
              }
            )
            break
          end

          break if match
        end
        break if match
      end
    end

    cves_list
  end

  def get_list_cves_macos
    query_hsh = { os_type: @input['os']['os_type'] }
    input_os_version = @input['os']['os_version']
    input_os_id = @input['os']['os_id']
    cves_list = []

    DataReader.instance.query('vuln_system_associations', query_hsh) do |asso|
      cve_id = asso['cve']
      match = false

      asso['affected_os'].each do |affected_os|
        next unless affected_os['os_id'] == input_os_id

        affected_os['ranges'].each do |range|
          next unless is_mac_version_in_range?(input_os_version, range)

          cves_list.push(cve_id)
          match = true
          break
        end
        break if match
      end
    end

    cves_list
  end

  # return true if version is within range
  # return false if not or unkown
  def is_mac_version_in_range?(version, range)
    return false unless range.key?('start') && range.key?('limit_except')
    return false unless Version.is_valid_version(version) \
                        && Version.is_valid_version(range['start']) \
                        && Version.is_valid_version(range['limit_except'])

    return false if Version.compare_version(version, range['start']) == -1
    return false if [0, 1].include?(Version.compare_version(version, range['limit_except']))

    return true
  end
end
