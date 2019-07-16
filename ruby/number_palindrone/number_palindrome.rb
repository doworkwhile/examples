max_n = 10**5
n = rand(max_n)

max_log = Math.log(n, 10).floor
odd_log = max_log % 2 == 0
half_max = max_log / 2

def get_indices(n, range)
  [*range].map { |e|
    imod = 10**(e + 1)
    idiv = 10**e
    (n % imod) / idiv
  }
end

range_low = odd_log ? (0...half_max) : (0..half_max)
range_high = ((half_max + 1)..max_log)
digits_low = get_indices(n, range_low)
digits_high = get_indices(n, range_high).reverse

puts n
puts digits_low.to_s, digits_high.to_s
puts digits_low == digits_high
