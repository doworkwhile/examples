def max_subarray(ary)
  max_sub = 0
  max_total = 0
  sub_items = []
  max_items = []

  ary.each { |i|
    max_sub = [0, max_sub + i].max

    did_go_higher = max_sub > max_total
    did_zero_sub = max_sub == 0

    max_total = [max_total, max_sub].max
    
    did_sync_max = max_total != 0 && max_total == max_sub
    did_not_sync_and_not_zero = !did_sync_max && !did_zero_sub

    if did_zero_sub
      sub_items = []
    end
    if did_sync_max || did_not_sync_and_not_zero
      sub_items << i
    end
    if did_sync_max && did_go_higher
      max_items = sub_items.clone
    end
  }

  return [max_items, max_total]
end

def knuth_shuffle(ary)
  (1..ary.size).each { |i|
    outer = ary.size - i
    swap = rand(outer)
    temp = ary[swap]
    ary[swap] = ary[outer]
    ary[outer] = temp
  }
end

ary = [*-3..5]
knuth_shuffle(ary)
puts ary.to_s
puts max_subarray(ary).to_s