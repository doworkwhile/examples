# the number of items that can be chosen
n_items = 9

# the weights and values that can be chosen
# the weight of w_ary[i] has the value v_ary[i]
# both use the same range of numbers
# the values are assigned in random order
# both start from 1 instead of 0 to avoid a 0-weight and 0-value item
# a 0-weight item would always be in the solution
# a 0-value item would never be in the solution
w_ary = [*1..n_items]
v_ary = [*1..n_items].shuffle

# the maximum weight of the items after choosing
w_max = 14

# print weight and value pairs
puts "---------"
puts "| w | v |"
puts "---------"
n_items.times { |x|
  puts  "| #{w_ary[x]} | #{v_ary[x]} |"
}
puts "---------"

# this first solution uses dynamic programming.
# store solutions for subsets of the problem, use those to find the answer.
# create a 2d table t[n_items + 1][w_max + 1]
# the first dimension is the item added to the subset of items
# the second dimension is the subset of the maximum weight
# both dimensions are x+1 to include the case of 0 items and 0 weight max
# for example: [1][1] would indicate the subset of only 1 item with a maximum
# possible weight of 1, [2][10] would indicate the subset of the first 2 items
# with a maximum possible weight of 10
solutions_table = []

# these are the dimensions of the table
n_items_incl_zero = n_items + 1
w_max_incl_zero = w_max + 1

# for each row
n_items_incl_zero.times { |item_subset|

  # add the array for this row
  solutions_table << []

  # for each column
  w_max_incl_zero.times { |w_max_subset|

    # the index of the last item
    prev_choice = item_subset - 1

    # when considering 0 items or a max weight of 0
    # no items can be in the solution
    if item_subset == 0 || w_max_subset == 0
      solutions_table[item_subset][w_max_subset] = 0

    # if the weight of the last item can be included in the subset
    elsif w_ary[prev_choice] <= w_max_subset

      # get the value and weight of that last item
      prev_value = v_ary[prev_choice]
      prev_weight = w_ary[prev_choice]

      # get the previous solution (smaller weight subset) in the table
      prev_solution = solutions_table[prev_choice][w_max_subset - prev_weight]

      # combine the value of the last item with the previous solution
      possible_new_val = prev_value + prev_solution

      # the solution for this value/weight subset is either a new value
      # (when the item can be included), or the previous value in the table
      # (when the item cannot be included)
      solutions_table[item_subset][w_max_subset] = [
        possible_new_val, solutions_table[prev_choice][w_max_subset]
      ].max

    # if the item can't be included at this weight subset,
    # use the previous value in the table (from the smaller item subset)
    else
      solutions_table[item_subset][w_max_subset] = solutions_table[prev_choice][w_max_subset]
    end
  }
}

# print solutions table
solutions_table.each_with_index { |row, row_index|
  if row_index == 0
    print "0 "
  else
    print "#{w_ary[row_index - 1]} "
  end
  print "["
  row.each { |col|
    col_s = col.to_s
    if col_s.size == 1
      print "  #{col_s}"
    else
      print " #{col_s}"
    end
  }
  puts " ]"
}

# print solutions table result
solutions_table_result = solutions_table[-1][-1]
puts "solutions table result: #{solutions_table_result}"

# find the chosen items from the solutions table
solutions_table_items = []

# start from the last item in the table
item_choice = n_items
weight_choice = w_max

# store the value at the last item
weight_choice_walk = solutions_table_result

# walk back through the chosen items
while item_choice > 0

  # compare the current solution with the solution in the previous row
  look_at = solutions_table[item_choice][weight_choice]
  prev_look = item_choice - 1
  look_before = solutions_table[prev_look][weight_choice]

  # if they don't match, the solution includes that items weight
  if look_at != look_before

    # now we move left in the table (lower weight subset)
    # until we find a value that matches the value at look_at subtracted by
    # the value of the weight we said was included
    # ex: the first row checked has value 20, the previous row is different
    # so the item represented by that first row is included
    # the value of that item is subtracted by 20, so move left in the
    # previous row until the new value is found
    included_val = v_ary[prev_look]
    weight_choice_walk -= included_val
    look_back = look_before
    while weight_choice_walk != look_back
      weight_choice -= 1
      look_back = solutions_table[prev_look][weight_choice]
    end

    # store the items weight and value
    solutions_table_items << [item_choice, v_ary[item_choice - 1]]
  end

  # the next iteration starts at the previous row
  item_choice = prev_look
end

# print the chosen items
puts "solutions table chosen items: "
solutions_table_items.each { |chosen|
  puts "item of weight #{chosen[0]} and value #{chosen[1]}"
}
