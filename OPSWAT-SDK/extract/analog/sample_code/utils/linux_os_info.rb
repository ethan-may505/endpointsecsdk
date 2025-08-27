# frozen_string_literal: true
require "json"

# Predefined list of allowed OS names and their corresponding output names
# os_name_map: os name -> [os name strip, major only]
OS_NAME_MAP = {
  'Red Hat' => ['RedHat', true],
  'AlmaLinux' => ['Alma', true],
  'Linux Mint' => ['Mint', false],
  'Ubuntu' => ['Ubuntu', false],
  'CentOS' => ['CentOS', false],
  'Debian' => ['Debian', false],
  'Amazon Linux' => ['Amazon', false],
  'Rocky Linux' => ['Rocky', true],
  'Oracle Linux' => ['Oracle', true],
  'SLED' => ['SLED', false],
  'SUSE Linux Enterprise Desktop' => ['SLED', false],
  'SLES' => ['SLES', false],
  'SUSE Linux Enterprise Server' => ['SLES', false],
  'SLETC' => ['SLETC', false],
  'SUSE Linux Enterprise Thin Client' => ['SLETC', false]
  # Add more mappings if needed
}.freeze

OS_TO_PACKAGE_MANAGER_MAP = {
  %w[Ubuntu Debian Mint] => 200_041,
  %w[Amazon Rocky Oracle RedHat Alma] => 200_042,
  ['SLES'] => 200_058
}.freeze

# Function to extract the major version (and minor if needed) from the string
def extract_version(str, major_only)
  version = ''
  dot_encountered = false
  count_digits = 0

  str.each_char do |ch|
    if ch =~ /\d/ # Check if character is a digit
      version += ch
      count_digits = 1 if count_digits.zero? # First group of digits
    elsif ch == '.' && count_digits == 1 && !dot_encountered
      if major_only
        # If only the major version is needed, stop after the dot
        break
      end

      # Include the dot only after the first group of digits
      version += ch
      dot_encountered = true
    elsif dot_encountered && ch !~ /\d/
      # If a non-digit is encountered after the dot, stop
      break
    elsif count_digits.positive?
      # If any non-digit is encountered after the first group of digits, stop
      break
    end
  end

  version
end

# Function to extract OS name and version - returns only the normalized OS name
def normalize_os_info(input, os_version = '')
    # This would normally be populated with your OS name mappings
    # Find the OS name in the input string
    OS_NAME_MAP.each do |key, value|
      next unless input.start_with?(key)

      os_name = value[0]
      major_only = value[1]

      # If os_version is provided, process it through the extract_version function
      if !os_version.empty?
        os_version = extract_version(os_version, major_only)
      else
        # If os_version is not provided, extract it from the input string
        remaining = input[key.length..]
        os_version = extract_version(remaining, major_only)
      end

      # If no version information is found, raise an error
      raise 'No version information found' if os_version.empty?

      return os_name, "#{os_name} #{os_version}" # Return the normalized OS name
    end

    raise 'Could not match OS name'
rescue StandardError => e
    puts "Error normalizing OS info: #{e.message}"
    ''
end

def find_package_manager(os_name)
  OS_TO_PACKAGE_MANAGER_MAP.each do |os_list, value|
    return value if os_list.include?(os_name)
  end
  nil  # return nil if no match is found
end
