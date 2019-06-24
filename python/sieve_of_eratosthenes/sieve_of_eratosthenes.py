import math

def sieve(n):
  primeMinimum = 2
  primeMaximum = int(math.sqrt(n))
  numbers = [True for i in range(n - 1)]

  for i in xrange(primeMinimum, primeMaximum):
    if (numbers[i - primeMinimum]):
      for j in xrange(i*i, n + 1, i):
        numbers[j - primeMinimum] = False

  numbers = [(i + primeMinimum if x else False) for i, x in enumerate(numbers)]

  return filter(lambda x: x != False, numbers)

print sieve(100)