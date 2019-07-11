class Heap

  attr_accessor :contents

  def initialize()
    self.contents = []
  end

  # helper methods

  def is_ordered(a, b)
    raise "Subclass must implement is_ordered(a, b)"
  end

  def size
    self.contents.size
  end

  def empty?
    size == 0
  end

  def get_parent_index(i)
    ((i - 1) / 2).floor
  end

  def get_left_index(i)
    (i * 2) + 1
  end

  def get_right_index(i)
    (i * 2) + 2
  end

  def has_parent(i)
    get_parent_index(i) >= 0
  end

  def has_left(i)
    get_left_index(i) < size
  end

  def has_right(i)
    get_right_index(i) < size
  end

  def element(i)
    self.contents[i]
  end

  def parent(i)
    self.contents[ get_parent_index(i) ]
  end

  def left(i)
    self.contents[ get_left_index(i) ]
  end

  def right(i)
    self.contents[ get_right_index(i) ]
  end

  def is_parent_disordered(i)
    is_ordered(parent(i), element(i)) == false
  end

  def are_children_ordered(i)
    is_ordered(right(i), left(i))
  end

  def is_parent_missing_or_ordered(i)
    has_parent(i) == false || is_ordered(parent(i), element(i))
  end

  def swap(a, b)
    temp = element(a)
    self.contents[a] = element(b)
    self.contents[b] = temp
  end

  # heap methods

  def peek
    element(0)
  end

  def peek_end
    return nil if size == 0
    element(size - 1)
  end

  def add(v)
    self.contents << v
    heap_up
  end

  def find_all(v)
    found_at = []

    self.contents.each_with_index { |e, i|
      if e == v
        found_at << i
      end
    }

    found_at
  end

  def find(v)
    self.contents.index(v)
  end

  def poll
    return nil if empty?
    return self.contents.pop if size == 1

    temp = peek
    self.contents[0] = self.contents.pop
    heap_down
    temp
  end

  def remove(v)
    loop do
      remove_index = find(v)

      break unless remove_index

      if remove_index == size - 1
        self.contents.pop
      else
        last_item = self.contents.pop
        self.contents[remove_index] = last_item

        if has_left(remove_index) && is_parent_missing_or_ordered(remove_index)
          heap_down(remove_index)
        else
          heap_up(remove_index)
        end
      end
    end
  end

  def heap_up(start = nil)
    current = start.nil? == false ? start : size - 1

    while has_parent(current) && is_parent_disordered(current)
      parent_index = get_parent_index(current)
      swap(parent_index, current)
      current = parent_index
    end
  end

  def heap_down(start = 0)
    current = start
    to_swap = nil

    while has_left(current)
      if has_right(current) && are_children_ordered(current)
        to_swap = get_right_index(current)
      else
        to_swap = get_left_index(current)
      end

      if is_ordered(element(current), element(to_swap))
        break
      end

      swap(current, to_swap)
      current = to_swap
    end
  end

end
