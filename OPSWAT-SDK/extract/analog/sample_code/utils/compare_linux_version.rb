# frozen_string_literal: true

def getEpoch(version)
  return version.split(':')[0].to_i if version.split(':').length > 1

  return 0
end

def getUpstream(version)
  upStartIdx = 0
  colonIdx = version.index(':')
  upStartIdx = colonIdx + 1 if colonIdx

  lastHyphenIdx = version.rindex('-')
  if lastHyphenIdx
    version[upStartIdx...lastHyphenIdx]
  else
    version[upStartIdx..-1]
  end
end

def getDebian(version)
  lhi = version.rindex('-')
  return version[lhi + 1..-1] if lhi

  return ''
end

# compare each component of version
# return 0 if two component is equal
# return 1 if ver1 > ver 2
# @return 2 if ver1 < ver2
# @return -1 if unknown
def CompareEpoch(epoch1, epoch2)
  r = epoch1 - epoch2
  if r > 0
    return 1
  elsif r < 0
    return 2
  else
    return 0
  end
end

# return 0 if two component is equal
# return 1 if ver1 > ver 2
# @return 2 if ver1 < ver2
# @return -1 if unknown
def CompareUpstream(upstream1, upstream2)
  s1 = 0
  s2 = 0
  while upstream1[s1] || upstream2[s2]
    # First the initial part of each string consisting entirely of non-digit characters is determined. These two parts (one of which may be empty) are compared lexically. If a difference is found it is returned. The lexical comparison is a comparison of ASCII values modified so that all the letters sort earlier than all the non-letters and so that a tilde sorts before anything, even the end of a part. For example, the following parts are in sorted order: ‘~~’, ‘~~a’, ‘~’, the empty part, ‘a’.
    # -> get the initial, non-digit chars of the two versions
    ndp1 = upstream1[s1..-1][/^\D+/]
    ndp1 = '' if ndp1.nil?
    ndp2 = upstream2[s2..-1][/^\D+/]
    ndp2 = '' if ndp2.nil?
    # compare lexically
    ndp1.chars.each_with_index do |c1, i|
      c2 = ndp2[i]
      c2 = '' if c2.nil?
      next if c1 == c2

      if c1 == '~' # tilde sorts before anything
        return 2
      elsif c2 == '~'
        return 1
      elsif c1 == ''
        return 2
      elsif c2 == ''
        return 1
      elsif c1.match?(/[a-zA-Z]/) && !c2.match?(/[a-zA-Z]/) # all letters sort earlier than non-letters
        return 2
      elsif c2.match?(/[a-zA-Z]/) && !c1.match?(/[a-zA-Z]/)
        return 1
      elsif c1 > c2
        return 1
      elsif c1 < c2
        return 2
      end
    end
    if ndp1.size < ndp2.size
      return 1 if ndp2[ndp1.size] == '~'

      return 2

    end
    s1 += ndp1.size
    s2 += ndp2.size

    # Then the initial part of the remainder of each string which consists entirely of digit characters is determined. The numerical values of these two parts are compared, and any difference found is returned as the result of the comparison. For these purposes an empty string (which can only occur at the end of one or both version strings being compared) counts as zero.
    dc1 = upstream1[s1..-1][/\d+/]
    dc1 ? (s1 += dc1.size) : (dc1 = 0)
    dc2 = upstream2[s2..-1][/\d+/]
    dc2 ? (s2 += dc2.size) : (dc2 = 0)
    if dc1.to_i > dc2.to_i
      return 1
    elsif dc1.to_i < dc2.to_i
      return 2
    end
  end
  return 0
end

def CompareDebian(version1, version2)
  return CompareUpstream(version1, version2)
end

# compare each component of version
# return 0 if two component is equal
# return 1 if ver1 > ver 2
# @return 2 if ver1 < ver2
# @return -1 if unknown
def compare_version(version1, version2)
  return 0 if version1 == version2

  cpEpoch = CompareEpoch getEpoch(version1), getEpoch(version2)
  return cpEpoch if cpEpoch != 0

  cpUpstream = CompareUpstream getUpstream(version1), getUpstream(version2)
  return cpUpstream if cpUpstream != 0

  cpDebian = CompareDebian getDebian(version1), getDebian(version2)
  return cpDebian
end

# return true if version is within range
# return false if not or unkown
# range: {
#  /(start|start_except)/: String,
#  /(limit|limit_except)/: String
# }
def is_linux_package_version_in_range?(version, range)
  return false unless range.key?('start') || range.key?('start_except')
  return false unless range.key?('limit') || range.key?('limit_except')

  start = range['start']
  start_except = range['start_except']
  limit = range['limit']
  limit_except = range['limit_except']

  if start
    return false if [2, -1].include?(compare_version(version, start))
  else
    return false if [0, 2, -1].include?(compare_version(version, start_except))
  end

  if limit_except
    return false if [0, 1, -1].include?(compare_version(version, limit_except)) && limit_except != 'N/A'
  else
    return false if [1, -1].include?(compare_version(version, limit)) && limit != 'N/A'
  end

  return true
end
