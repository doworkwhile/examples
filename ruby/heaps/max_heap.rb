class MaxHeap < Heap
  def initialize
    super
  end

  def is_ordered(a, b)
    a > b
  end
end
