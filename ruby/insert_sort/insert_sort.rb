ary = [*0..19].shuffle

puts ary.to_s

(1...(ary.size)).each { |lead|
  backStep = lead
  while backStep > 0 && ary[backStep] < ary[backStep-1]
    temp = ary[backStep]
    ary[backStep] = ary[backStep-1]
    ary[backStep-1] = temp
    backStep -= 1
  end
}

puts ary.to_s