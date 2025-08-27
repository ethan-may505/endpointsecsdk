# frozen_string_literal: true

require 'open3'

def show_help
  puts %(
  This sample project code helps customers to check/validate Analog files, helps to test common use cases, check references between files.
  Usage: $ ruby main.rb [--validate | --validate-schema] [--check-soft-linker | --check-hard-linker] [--data-source analog_dir]
  Options:
    --validate
      Validate file Analog: checksum, schema and linker. Report result with each test.
    --validate-schema
      Validate schema of each file on server Analog
    --check-linker
      Check the link that exists between the files on the Analog server.
    --check-hard-linker
      Check the linker must exist between the files on the Analog server.
    --check-soft-linker
      Check the linker that exists between the files on the Analog server.
    --data-source analog_dir
      Choose a directory to read Analog files from. By default, "./analog" directory is used.
  )
end

if ARGV.empty?
  show_help
  exit
end

test_soft_linker = false
test_hard_linker = false
test_linker = false
test_schema = false
test_all = false
@analog_dir = "#{__dir__}/.."

ARGV.each_index do |i|
  case ARGV[i]
  when /^--help$|^-h$/
    show_help
    exit
  when '--check-soft-linker'
    test_soft_linker = true
  when '--check-hard-linker'
    test_hard_linker = true
  when '--check-linker'
    test_linker = true
  when '--validate-schema'
    test_schema = true
  when '--validate'
    test_all = true
  when '--data-source'
    @analog_dir = ARGV[i + 1]
  end
end

def run_file_ruby(file)
  cmd = "ruby #{file} --data-source #{@analog_dir}"
  stdout_and_stderr, status = Open3.capture2e(cmd)
  status = status == 0 ? true : false

  [stdout_and_stderr, status]
end

if test_all
  script_out, success = run_file_ruby 'validate_checksums.rb'
  puts "Validate checksums for all analog server and analog client files, status: \n#{script_out}\n"
end

if test_all || test_schema
  script_out, success = run_file_ruby 'validate_schema.rb'
  puts "Validate schema for all analog server files, status: \n#{script_out}\n"
end

if test_all || test_linker || test_hard_linker
  script_out, success = run_file_ruby 'hard_linker.rb'
  puts "Check the linker must exist between the files of analog server, status: \n#{script_out}\n"
end

if test_all || test_linker || test_soft_linker
  script_out, success = run_file_ruby 'soft_linker.rb'
  puts "Check the linker that exists between the files of analog server, status: \n#{script_out}\n"
end
