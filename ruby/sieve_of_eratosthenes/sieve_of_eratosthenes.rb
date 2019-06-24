def sieve(n)
  prime_minimum = 2
  prime_maximum = Math.sqrt(n).to_i
  numbers = [true] * (n - 1)

  (prime_minimum...prime_maximum).each { |i|
    if (numbers[i - prime_minimum])
      ((i*i)..n).step(i).each { |j|
        numbers[j - prime_minimum] = false
      }
    end
  }

  numbers.each_with_index.map { |e, i|
    e ? i + prime_minimum : e
  }.reject { |e| !e }
end

puts sieve(100).to_s