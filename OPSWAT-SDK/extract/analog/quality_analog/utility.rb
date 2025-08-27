#! /usr/bin/env ruby
# frozen_string_literal: true

require 'json'
require 'json-schema' # need json-schema gem
require 'yajl' # need yajl-ruby gem

def parse_json json_content
  parser = Yajl::Parser.new
  begin
    return parser.parse(json_content)
  rescue => e
    puts e
    return nil
  end
end