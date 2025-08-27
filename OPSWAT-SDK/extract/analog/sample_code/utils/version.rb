# frozen_string_literal: true

class Version
  include Comparable

  attr_reader :version_string, :number_segments, :constant_segments

  def initialize(vstr)
    @version_string = vstr.gsub('_', ' ').gsub(/^v(\d)/, '\1')
    @number_segments = []
    @constant_segments = []
    return if vstr.empty? # don't need to process anymore if vstr is empty (invalid)

    temp_segment = ''
    old_status = get_char_status @version_string.chr
    @version_string.chars.each do |char|
      new_status = get_char_status char
      if new_status == old_status
        temp_segment += char
      else
        # found something different, backup the "temp_segment" that is built thus far to appropriate storage
        if old_status == 1 # if we've encountered number til now then save that number
          @number_segments << temp_segment.to_i
        else # else, we will treat it as string constant
          @constant_segments << temp_segment
        end
        temp_segment = char # assign 'char' as first character of new segment
        old_status = new_status # new segment has new character status
      end
    end

    if old_status == 1 # if we've encountered number til now then save that number
      @number_segments << temp_segment.to_i
    else # else, we will treat it as string constant
      @constant_segments << temp_segment
    end

    # remove zeros at the end of version
    count_zero_number_tail = 0
    while @number_segments.size >= 2 && @number_segments.last.zero?
      @number_segments.pop
      count_zero_number_tail += 1
    end
    count_zero_number_tail += 1 if old_status != 1
    while !@constant_segments.empty? && count_zero_number_tail > 0
      @constant_segments.pop
      count_zero_number_tail -= 1
    end
  end

  # compare between this version object and another version object or string
  # return 1 if this > other, 0 if this == other, -1 if this < other and nil if they are not comparable
  def <=>(other)
    return nil unless Version.is_valid_version(other) && Version.is_valid_version(@version_string)

    other_version = other.is_a?(Version) ? other : Version.new(other)

    minimum_num_constants = [@constant_segments.size, other_version.constant_segments.size].min
    minimum_num_numbers = [@number_segments.size, other_version.number_segments.size].min

    j = 0
    if get_char_status(@version_string[0]) == 1 # first char is digit, so compare digit first, then constant strings
      # compare pairs of number segments having the same index
      (0...minimum_num_numbers).each do |i|
        return 1 if @number_segments[i] > other_version.number_segments[i]
        return -1 if @number_segments[i] < other_version.number_segments[i]

        next unless j < minimum_num_constants
        return nil if @constant_segments[j] != other_version.constant_segments[j]

        j += 1
      end
    else # first char is character, so compare constants first, then numbers
      # compare pairs of constant segments having the same index
      # the constant parts must be equal for the 2 versions to be comparable
      (0...minimum_num_numbers).each do |i|
        if j < minimum_num_constants
          return nil if @constant_segments[j] != other_version.constant_segments[j]

          j += 1
        end
        return 1 if @number_segments[i] > other_version.number_segments[i]
        return -1 if @number_segments[i] < other_version.number_segments[i]
      end
    end

    # if it reaches here then the number segments are equal until now,
    # check the longer segment and see if there is only 0 in the left parts
    if @number_segments.size != other_version.number_segments.size
      longer_number_segments = (if @number_segments.size > other_version.number_segments.size
                                  @number_segments
                                else
                                  other_version.number_segments
                                end)
      only_zero = true
      (minimum_num_numbers...longer_number_segments.size).each do |i|
        if longer_number_segments[i] != 0
          only_zero = false
          break
        end
      end
      return 0 if only_zero
      return 1 if @number_segments.size > other_version.number_segments.size

      return -1
    end
    0
  end

  def self.compare_version(version_1, version_2)
	vs1 = (version_1.is_a?(Version) ? version_1 : Version.new(version_1))
	vs2 = (version_2.is_a?(Version) ? version_2 : Version.new(version_2))
	return vs1 <=> vs2
  end
  
  # return type of a character, 1 means number, 0 means alpha character, -1 means other (e.g: '(', '.')
  def get_char_status(char)
    return 1 if /\p{Digit}/ =~ char
    return 0 if /\p{Alpha}/ =~ char

    -1
  end

  def self.is_valid_version(version)
    return true if version && version.to_s =~ /\d/

    false
  end
end
