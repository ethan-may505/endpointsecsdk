# encoding: UTF-8
require_relative 'version'

class Range
  attr_reader :start
  attr_reader :limit

  def initialize start, limit, opt = {}
    @start = (start.is_a?(::Version) ? start : ::Version.new(start))
    @limit = (limit.is_a?(::Version) ? limit : ::Version.new(limit))
  end

  # we check for <= limit in these methods
  def is_in_range(v)
    version = (v.is_a?(::Version) ? v : ::Version.new(v))

    limit_vs_version = Version.compare_version(@limit, version)
    return false if limit_vs_version.nil? || limit_vs_version < 0
    version_vs_start = Version.compare_version(version, @start)
    return false if version_vs_start.nil? || version_vs_start < 0
    return true
  end
end
