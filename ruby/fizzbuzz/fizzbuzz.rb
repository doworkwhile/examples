def fizzbuzz(startNum, endNum)
  (startNum..endNum).each { |n|
    if nmod3(n)
      print "Fizz"
    end
    if nmod5(n)
      print "Buzz"
    end
    if (nnmod3(n) && nnmod5(n))
      print n
    end
    puts
  }
end

def fizzbuzz2(startNum, endNum)
  (startNum..endNum).each { |n|
    if (nmod5(n) && nmod3(n))
      puts "FizzBuzz"
    elsif nmod3(n)
      puts "Fizz"
    elsif nmod5(n)
      puts "Buzz"
    else
      puts n
    end
  }
end

@nmod5cmp = 0
@nmod3cmp = 0
@nnmod3cmp = 0
@nnmod5cmp = 0

def nmod3(n)
  @nmod3cmp += 1
  n % 3 == 0
end
def nmod5(n)
  @nmod5cmp += 1
  n % 5 == 0
end
def nnmod3(n)
  @nnmod3cmp += 1
  n % 3 != 0
end
def nnmod5(n)
  @nnmod5cmp += 1
  n % 5 != 0
end

fizzbuzz(1, 100)
puts "#{@nmod5cmp} #{@nmod3cmp} #{@nnmod5cmp} #{@nnmod3cmp}"


@nmod5cmp = 0
@nmod3cmp = 0
@nnmod3cmp = 0
@nnmod5cmp = 0
fizzbuzz2(1, 100)
puts "#{@nmod5cmp} #{@nmod3cmp} #{@nnmod5cmp} #{@nnmod3cmp}"

