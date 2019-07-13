# 10-20 numbers between -3 to 3 inclusive
input = [*0..rand(10..20)].map { |e| rand(-3..3) }
puts input.to_s

# sort the inputs
sorted_input = input.sort
sorted_input_len = sorted_input.size
puts input.sort.to_s

# create a store for the solutions
valid_chains = []

# use a left and right marker to track the smallest and largest parts of
# each solution
left_marker = 0
right_marker = sorted_input_len - 1

# walk the sorted inputs from the beginning
# stopping when left_marker + 3 > sorted_input_len
while left_marker + 3 <= sorted_input_len
  left_val = sorted_input[left_marker]

  if left_val > 0
    break
  end

  # walk from the right marker to the left marker + 1 (an extra space for the
  # middle value)
  # the middle value of a solution must be between them
  while right_marker > left_marker + 1
    right_val = sorted_input[right_marker]
    middle_val = 0 - (left_val + right_val)

    # we can only find a middle value when it is larger or equal to the left_marker
    if middle_val >= left_val

      # start from the right marker - 1 and move to left marker
      # check match of middle marker for the middle value of the solution
      middle_marker = right_marker - 1
      while middle_marker > left_marker
        match_val = sorted_input[middle_marker] == middle_val

        # if we have a match, add the solution
        if match_val
          valid_chains << [
            left_val,
            middle_val,
            right_val
          ]
          break
        end

        middle_marker -= 1
      end
    end

    # move the right marker until finding a new number
    # the right marker will be at the index of the new number
    while sorted_input[right_marker] == right_val
      right_marker -= 1
    end
  end

  # move the left marker until finding a new number
  # the left marker will be at the index of the new number
  right_marker = sorted_input_len - 1
  while sorted_input[left_marker] == left_val
    left_marker += 1
  end
end

puts valid_chains.to_s
