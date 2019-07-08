require './heap.rb'

class MinHeap < Heap
  def initialize
    super
  end

  def is_ordered(a, b)
    a < b
  end
end
