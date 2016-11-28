# leetcode No. 3
# Given a string, find the length of the longest substring without repeating characters.
#
# Examples:
#
# Given "abcabcbb", the answer is "abc", which the length is 3.
#
# Given "bbbbb", the answer is "b", with the length of 1.
#
# Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
# @param {String} s
# @return {Integer}
def length_of_longest_substring(s)
  max = tmp = []
  max_len = 0
  current_len = 0
  current_left = current_right = 0
  i = 0
  s.each_char do |v|
    if tmp.include?(v)
      current_left = current_left + 1
      current_right = i
      tmp = tmp[tmp.index(v) + 1..-1]
      tmp << v
      current_len = tmp.size
    else
      current_right = i
      current_len += 1
      tmp << v
    end
    if max_len < current_len
      max_len = current_len
      # max = tmp.clone
    end
    i += 1
  end
  # return max.join
  return max_len
end

test_data = [
  {data: 'abcabcbb', result: 'abc'},
  {data: 'bbbb', result: 'b'},
  {data: 'pwwkew', result: 'wke' },
  {data: 'dvdf', result: 'vdf' }
]

test_data.each do |v|
  puts "expected: #{v[:result]}, actual: #{length_of_longest_substring(v[:data])}"
end
