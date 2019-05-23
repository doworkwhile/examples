myAry = [*0..9]

def binary_recurse(ary, left, right, toFind)
  if (left > right)
    return -1
  end
  check = (left + right) / 2
  found = ary[check]

  if (found == toFind)
    return found
  elsif (found < toFind)
    left = check + 1
  else
    right = check - 1
  end

  binary_recurse(ary, left, right, toFind)
end

puts myAry.to_s
myAry.each { |e|
  puts "finding #{e}"
  puts binary_recurse(myAry, 0, myAry.size, e)
}
