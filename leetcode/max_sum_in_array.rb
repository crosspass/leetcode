# @param {number}
# @return {number}
#
# 临时变量:
# 已经遍历过了最大的子数组的和, 左索引，右索引
# 当前子数据的和，左索引，右索引
def max_sum_in_array(array)
  left = right = 0
  current_left = current_right = 0
  current_sum = 0
  max = array.first
  next_a = true
  array.each_with_index do |v ,i|
    if next_a
      current_sum = v
      current_left = current_right = i
      next_a = current_sum > 0 ? false : true
    else
      current_sum += v
      current_right += 1
      next_a = true if current_sum < 0
    end
    if current_sum >= max
      left = current_left
      right = current_right
      max = current_sum
    end
  end
  return array[left..right]
end

data = [
  {data: [-1, -2, -3], result: [-1]},
  {data: [-1, 2, 2, -2, 4], result: [2, 3, -5, 6]},
  {data: [1, 2, 3, -1], result: [1, 2, 3]}
]

data.each do |v|
  puts "expected #{v[:result]}, acutal #{max_sum_in_array(v[:data])}"
end
