# @param {String} s
# @return {String}
#
def reverse_vowels(s)
  vowels = ['a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U']

  tmp_s = s.clone
  i = 0
  j = s.size - 1

  # 标记左值或右值
  left_flag = false
  right_flag = false

  while i < j do
    left_flag = true if vowels.include?(tmp_s[i])
    right_flag = true if vowels.include?(tmp_s[j])
    if left_flag and right_flag
      tmp_s[i], tmp_s[j] = tmp_s[j], tmp_s[i]
      left_flag = false
      right_flag = false
    end
    i += 1 unless left_flag
    j -= 1 unless right_flag
  end
  return tmp_s
end

test_data = [
  { data: 'hello', res: 'holle' },
  { data: 'leetcode', res: 'leotcede' },
  { data: 'e', res: 'e' },
  { data: 'ea', res: 'ae' }
]

test_data.each do |v|
  puts "expected #{v[:res]} actual: #{reverse_vowels(v[:data])}"
end
