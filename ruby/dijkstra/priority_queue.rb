class PriorityQueueNode

  attr_reader :item, :priority

  def initialize(item, priority)
    @item = item
    @priority = priority
  end

end

class PriorityQueue

  def initialize
    @contents = []
  end

  def add(item, priority)
    @contents << PriorityQueueNode.new(item, priority)
    heap_up
  end

  def poll
    return nil if @contents.size == 0
    return @contents.pop if @contents.size == 1

    node = @contents[0]
    @contents[0] = @contents.pop
    heap_down
    node
  end

  def heap_up
    walking_index = @contents.size - 1

    while parent_disordered?(walking_index)
      parent_index = get_parent_index(walking_index)
      swap(walking_index, parent_index)
      walking_index = parent_index
    end
  end

  def heap_down
    walking_index = 0
    next_index = nil

    while has_left(walking_index)
      if children_ordered?(walking_index)
        next_index = get_right_index(walking_index)
      else
        next_index = get_left_index(walking_index)
      end

      break if ordered?(@contents[walking_index], @contents[next_index])

      swap(walking_index, next_index)
      walking_index = next_index
    end
  end

  # item orderings
  def ordered?(above, below)
    return above.priority < below.priority
  end

  def children_ordered?(i)
    has_right(i) && ordered?(right(i), left(i))
  end

  def parent_disordered?(i)
    has_parent(i) && !ordered?(parent(i), @contents[i])
  end

  # get item by relation
  def parent(i)
    @contents[get_parent_index(i)]
  end

  def left(i)
    @contents[get_left_index(i)]
  end

  def right(i)
    @contents[get_right_index(i)]
  end

  # has item by relation
  def has_parent(i)
    get_parent_index(i) >= 0
  end

  def has_left(i)
    get_left_index(i) < @contents.size
  end

  def has_right(i)
    get_right_index(i) < @contents.size
  end

  # indexes
  def get_parent_index(i)
    ((i - 1) / 2).floor
  end

  def get_left_index(i)
    (i * 2) + 1
  end

  def get_right_index(i)
    (i * 2) + 2
  end

  # other
  def swap(a, b)
    temp = @contents[a]
    @contents[a] = @contents[b]
    @contents[b] = temp
  end

  def empty?
    @contents.size == 0
  end

end
