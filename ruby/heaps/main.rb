require ('./min_heap.rb')
require ('./max_heap.rb')

min_heap = MinHeap.new
max_heap = MaxHeap.new

test_elements = [92, 15, 8, 82, 14, 93, 75, 44, 98, 84]

test_elements.each { |e|
  min_heap.add(e)
  max_heap.add(e)
}

# test min heap
puts "=== test min heap"
min_ordered = []
puts min_heap.contents.to_s
test_elements.size.times {
  min_ordered << min_heap.poll
}
puts "min_ordered? #{min_ordered == min_ordered.sort}"
puts "polled all elements? #{min_heap.empty?}"

# test max heap
puts "=== test max heap"
max_ordered = []
puts max_heap.contents.to_s
test_elements.size.times {
  max_ordered << max_heap.poll
}
puts "max_ordered? #{max_ordered.reverse == max_ordered.sort}"
puts "polled all elements? #{max_heap.empty?}"
