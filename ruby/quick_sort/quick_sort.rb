def quickSortRecurse(ary, left, right)
  if (left < right)
    pivot = ary[right]

    i = left - 1
    (left...right).each { |j|
      if ary[j] < pivot
        i += 1
        if i != j # swap i & j
          ary[i] += ary[j]
          ary[j] = ary[i] - ary[j]
          ary[i] -= ary[j]
        end
      end
    }

    pivotIndex = i + 1
    if pivotIndex != right # swap pivotIndex & right
      ary[pivotIndex] += ary[right]
      ary[right] = ary[pivotIndex] - ary[right]
      ary[pivotIndex] -= ary[right]
    end

    quickSortRecurse(ary, left, pivotIndex - 1)
    quickSortRecurse(ary, pivotIndex + 1, right)
  end
end

def quickSort(ary)
  quickSortRecurse(ary, 0, ary.size - 1)
end

aryLen = 10
ary = Array.new(aryLen) { |i| aryLen - i }
puts ary.to_s
quickSort(ary)
puts ary.to_s