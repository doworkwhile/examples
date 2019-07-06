choices = 9
weight_max = 14
weight_ary_max = weight_max + 1
choices_ary_max = choices + 1

# creates weights and values
weights = [*1..choices]
values = [*1..choices].shuffle
# values = [3,9,6,7,4,5,8,2,1]

# print weights and values
puts "---------"
puts "| w | v |"
puts "---------"
choices.times { |x|
  puts  "| #{weights[x]} | #{values[x]} |"
}
puts "---------"

# create solutions
solutions_table = []
choices_ary_max.times { |c|
  solutions_table << []
  weight_ary_max.times { |w|
    prev_choice = c - 1
    prev_weight = weights[prev_choice]
    if c == 0 || w == 0
      solutions_table[c][w] = 0
    elsif prev_weight <= w
      val_in_prev_row = values[prev_choice]
      prev_weight = weights[prev_choice]
      prev_solution = solutions_table[prev_choice][w - prev_weight]
      possible_new_val = val_in_prev_row + prev_solution
      solutions_table[c][w] = [
        possible_new_val, solutions_table[prev_choice][w]
      ].max
    else
      solutions_table[c][w] = solutions_table[prev_choice][w]
    end
  }
}

# print solutions
solutions_table.each { |row|
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

# get final result
def recurse_answer(w, v, weightCap, nItems)
  if nItems == 0 || weightCap == 0
    return 0
  end

  lastIndex = nItems - 1
  if w[lastIndex] > weightCap
    return recurse_answer(w, v, weightCap, lastIndex)
  end

  newWeightCap = weightCap - w[lastIndex]
  return [
    v[lastIndex] + recurse_answer(w, v, newWeightCap, lastIndex),
    recurse_answer(w, v, weightCap, lastIndex)
  ].max
end

final_result = recurse_answer(weights, values, weight_max, choices)
puts "final result: #{final_result}"
