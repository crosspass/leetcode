# @param {Integer[]} nums
# @param {Integer} target
# @return {Integer[]}

def search_range(nums, target)
  min = (nums.index(target) || -1)
  max = min + 1

  while nums[max] == target
    max += 1
  end

  max -= 1
  return [min, max]
end

test_data = [
  { params: { p1: [5, 7, 7, 8, 8, 10], p2: 8 }, res: [3, 4] },
  { params: { p1: [5, 7, 7, 8, 8, 10], p2: 1 }, res: [-1, -1] },
  { params: { p1: [5], p2: 1 }, res: [-1, -1] },
  { params: { p1: [5], p2: 5 }, res: [0, 0] }
]

test_data.each do |v|
  puts "Expected: #{v[:res]}, Actual: #{search_range(v[:params][:p1], v[:params][:p2])}"
end
