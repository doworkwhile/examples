n = 100
for x in range(1,n+1):
  xmod3 = x % 3 == 0
  xmod5 = x % 5 == 0
  if (xmod3 and xmod5):
    print 'FizzBuzz'
  elif (xmod3):
    print 'Fizz'
  elif (xmod5):
    print 'Buzz'
  else:
    print x
