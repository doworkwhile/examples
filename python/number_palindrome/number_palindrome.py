import random
import math

max_n = 10**5
n = random.randrange(max_n)

max_log = int(math.floor(math.log(n, 10)))
odd_log = max_log % 2 == 0
half_max_log = int(math.floor(max_log / 2))

top_low_range = half_max_log if odd_log else half_max_log + 1
range_low = xrange(0, top_low_range)
range_high = xrange(max_log, half_max_log, -1)

def get_indices(n, index_range):
  return [(n % (10**(i + 1)) / (10**i)) for i in index_range]

digits_low = get_indices(n, range_low)
digits_high = get_indices(n, range_high)

print n
print digits_low, digits_high
print digits_low == digits_high
