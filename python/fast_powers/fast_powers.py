import math

def fastPowers(num, power):
  if power < 0:
    return None

  if power == 0:
    return 1

  # even power
  if power % 2 == 0:
    recurseMult = fastPowers(num, power / 2)
    return recurseMult * recurseMult

  # must be odd power
  recurseMult = fastPowers(num, int(math.floor(power / 2)))
  return recurseMult * recurseMult * num

power2s = map(lambda x: fastPowers(2, x), range(0, 10))
print power2s