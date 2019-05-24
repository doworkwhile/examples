def partition(ary, pivot)
  left = -1
  right = ary.size

  while (left < right)
    while (left < right && ary[left += 1] < pivot); end
    while (right > left && ary[right -= 1] > pivot); end
    temp = ary[left]
    ary[left] = ary[right]
    ary[right] = temp
  end

  left
end

randMin = 10
randMax = 100
pivot = (randMin + randMax) / 2
aryLen = 10
@ary = [*0...aryLen].map { |e| randMin + rand((randMax - randMin - 1)) }
puts @ary.to_s
partAt = partition(@ary, pivot)
puts "part at #{partAt}"
puts @ary.to_s