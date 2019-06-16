class LinkedList

  attr_accessor :head

  def initialize
    @head = nil
  end

  def add(v)
    unless @head
      @head = Node.new(v)
      return
    end

    if v < @head.value
      @head = Node.new(v, @head)
      return
    end

    current = @head
    while current.nxt && current.nxt.value < v
      current = current.nxt
    end
    current.nxt = Node.new(v, current.nxt)
  end

  def add_node(n)
    unless @head
      @head = n
      n.nxt = nil
      return
    end

    if n.value < @head.value
      n.nxt = @head
      @head = n
      return
    end

    current = @head
    while current.nxt && current.nxt.value < n.value
      current = current.nxt
    end
    n.nxt = current.nxt
    current.nxt = n
  end

  def find(v)
    current = @head
    while (current)
      return current if (current.value == v)
      current = current.nxt
    end

    nil
  end

  def pop()
    return nil unless @head
    temp = @head
    @head = @head.nxt
    temp
  end

  def tail
    tail = @head
    while (tail.nxt)
      tail = tail.nxt
    end
    tail
  end

  def getIndexOf(v)
    current = @head
    i = 0
    while (current)
      return i if current.value == v
      current = current.nxt
      i += 1
    end 
    nil
  end

  def to_s
    ret = '['
    current = @head
    while (current)
      ret += current.value.to_s
      break unless current.nxt
      ret += ', ' 
      current = current.nxt
    end
    ret + ']'
  end

end

class Node

  attr_accessor :value
  attr_accessor :nxt

  def initialize(v, nxt=nil)
    @value = v
    @nxt = nxt
  end

end
