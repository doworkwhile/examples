def knuth_shuffle(ary)
  (1..ary.size).each { |i|
    outer = ary.size - i
    swap = rand(outer)
    temp = ary[swap]
    ary[swap] = ary[outer]
    ary[outer] = temp
  }
end

aryLen = 10;
ary = [*0...aryLen]
puts ary.to_s
knuth_shuffle(ary)
puts ary.to_s
