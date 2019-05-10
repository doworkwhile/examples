@arr = Array.new(10) { |i| i + 1 }

def swap(i1, i2)
  t = @arr[i2]
  @arr[i2] = @arr[i1]
  @arr[i1] = t
end

def bubbleSort1()
  (@arr.size - 1).downto(0) do |outer|
    0.upto(outer - 1) do |i|
      if (@arr[i] > @arr[i+1])
        swap(i, i+1)
      end
    end
  end
end

def bubbleSort2()
  for outer in 1...@arr.size do
    router = @arr.size - outer
    for i in 0...router do
      if (@arr[i] > @arr[i+1])
        swap(i, i+1)
      end
    end
  end
end

def bubbleSort3()
  (0...@arr.size).reverse_each do |outer|
    (0...outer).each do |i|
      if (@arr[i] > @arr[i+1])
        swap(i, i+1)
      end
    end
  end
end

@arr.shuffle!
print @arr.to_s + "\n";
bubbleSort1();
print @arr.to_s + "\n"

puts
@arr.shuffle!
print @arr.to_s + "\n";
bubbleSort2();
print @arr.to_s + "\n"

puts
@arr.shuffle!
print @arr.to_s + "\n";
bubbleSort3();
print @arr.to_s + "\n"