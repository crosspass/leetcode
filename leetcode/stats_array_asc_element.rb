# param {Integer[]} nums
# @return {Integer}
def length_of_list(nums)
  tmp = Hash.new  {|hash, k| hash[k] = [] }
  tmp[0] << []
  max_key = 1
  nums.each do |v|
    flag = false
    max_key.times do |index|
      tmp[max_key - index - 1].each do |values|
        if values.last.nil? or values.last.to_i < v
          new_values = values.clone
          new_values << v
          tmp[new_values.length] << new_values
          max_key = [new_values.length + 1, max_key].max
          flag = true
        end
      end
      break if flag
    end
  end
  return max_key - 1
end

test_data = [
  { len: 1, data: [6, 5, 4, 3, 2, 1] },
  { len: 6, data: [1, 2, 3, 4, 5, 6] },
  { len: 4, data: [1, 3, 2, 6, 4, 5] },
  { len: 3, data: [4, 5, 1, 6, 2, 3] },
  { len: 1, data: [0] }
]

test_data.each do |v|
  puts "expected #{ v[:len] }, actual #{ length_of_list(v[:data]) }"
end
