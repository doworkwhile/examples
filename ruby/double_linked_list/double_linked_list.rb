class Node
  attr_accessor :nxt, :prev, :value

  def initialize(v, nxt=nil, prev=nil)
    @value = v
    @nxt = nxt
    @prev = prev
  end
end

# circularly linked!
class DoubleLinkedList

  attr_accessor :head

  def initialize()
    head = nil
  end

  def tail
    return nil unless head
    head.prev
  end

  def add(v)
    # no nodes
    unless head
      @head = Node.new(v)
      head.nxt = head
      head.prev = head
      return
    end

    # only 1 node
    if v < head.value
      temp = Node.new(v, head, tail)
      tail.nxt = temp
      head.prev = temp
      @head = temp
      return
    end

    # more than 1 node
    last = head
    current = head.nxt
    while current && current.value < v && current != head
      last = current
      current = current.nxt
    end
    temp = Node.new(v, current, last)
    last.nxt = temp;
    current.prev = temp;
  end

  def add_node(n)
    # no nodes
    unless head
      @head = n
      head.nxt = head
      head.prev = head
      return
    end

    # only 1 node
    if n.value < head.value
      n.nxt = head
      n.prev = tail
      tail.nxt = temp
      head.prev = temp
      @head = temp
      return
    end

    # more than 1 node
    last = head
    current = head.nxt
    while current && current.value < n.value && current != head
      last = current
      current = current.nxt
    end
    n.nxt = current
    n.prev = last
    last.nxt = temp;
    current.prev = temp;
  end

  def find(v)
    return nil unless head
    return head if head.value == v

    current = head.nxt
    while current != head
      return current if current.value == v

      current = current.nxt
    end
    nil
  end

  def indexOf(v)
    return nil unless head
    return 0 if head.value == v

    current = head.nxt
    i = 1
    while current != head
      return i if current.value == v

      current = current.nxt
      i += 1
    end
    nil
  end

  def insertAt(i, v)
    unless head
      @head = Node.new(v)
      head.nxt = head
      head.prev = head
      return
    end

    if (i == 0) # insert at head
      temp = Node.new(v, head, tail)
      tail.nxt = temp
      head.prev = temp
      @head = temp
      return
    end

    atIndex = getIndex(i)
    temp = Node.new(v, atIndex, atIndex.prev)
    atIndex.prev.nxt = temp
    atIndex.prev = temp
  end

  def getIndex(i)
    return head if i == 0
    goingUp = i > 0
    moveOp = goingUp ? 1 : -1
    j = goingUp ? 1 : -1
    current = goingUp ? head.nxt : head
    while (i != j)
      j += moveOp
      current = goingUp ? current.nxt : current.prev
    end
    current
  end

  def to_s
    return '[]' unless head

    ret = '[ '
    ret += head.value.to_s
    current = head.nxt
    if current != head
      ret += ', '
      while current != head
        ret += current.value.to_s
        ret += ', ' if current.nxt != head
        current = current.nxt
      end
    end
    ret += ' ]'
  end

  def insertSort
    return unless head && head.nxt

    # these two are stepping forward
    last = head
    current = head.nxt
    while current && current != head
      if current.value < last.value
        # these two are stepping backwards
        toSwap = current
        backstep = last
        while toSwap.value < backstep.value && backstep != head
          backstep = backstep.prev
        end
        # remove self
        toSwap.prev.nxt = toSwap.nxt
        toSwap.nxt.prev = toSwap.prev

        # route self
        toSwap.prev = backstep.prev
        toSwap.nxt = backstep

        # route others to self
        backstep.prev.nxt = toSwap
        backstep.prev = toSwap

        # did we replace the head?
        if backstep == head
          @head = toSwap
        end
      end
      last = current
      current = current.nxt
    end
  end

  def clear
    @head = nil
  end

  def lastIndex
    indexOf(tail.value)
  end

  def swapIndexes(first, second)
    return if first == second
    firstNode = getIndex(first)
    secondNode = getIndex(second)

    swapNodes(firstNode, secondNode)
  end

  def swapNodes(firstNode, secondNode)
    snprevtemp = secondNode.prev
    fnnexttemp = firstNode.nxt
    adjacent = secondNode.prev == firstNode

    secondNode.prev = firstNode.prev
    secondNode.prev.nxt = secondNode
    firstNode.nxt = secondNode.nxt
    firstNode.nxt.prev = firstNode

    if (adjacent)
      secondNode.nxt = firstNode
      firstNode.prev = secondNode
    else 
      firstNode.prev = snprevtemp
      firstNode.prev.nxt = firstNode
      secondNode.nxt = fnnexttemp
      secondNode.nxt.prev = secondNode
    end

    if head == firstNode
      @head = secondNode
    elsif head == secondNode
      @head = firstNode
    end
  end

  def shuffle
    li = lastIndex()
    (0...li).each { |e|
      outer = li - e
      swap = rand(outer)
      swapIndexes(outer, swap)
    }
  end

  def bubbleSort
    return if head == nil || head.nxt == head # list has 0 or 1 nodes

    outer = tail
    while outer != head # outer = move prev from tail until prev is head
      current = head # current = move next from head until current is outer
      while current != outer
        # when the next val is smaller and not the head
        if (current.nxt.value < current.value && current.nxt != head)
          # swap current & next
          # this also handles setting a new head
          swapNodes(current, current.nxt)

          # if old current.nxt was outer
          # we swapped past outer and we are now real outer
          if current.prev == outer
            outer = current
          end

          # don't change current because it was swapped with next
        else
          # move current forward
          current = current.nxt
        end
      end
      # move outer backward
      outer = outer.prev
    end
  end

  def find(v)
    return nil unless head

    current = head
    loop do
      return current if current.value == v
      current = current.nxt
      break if current == head
    end
    nil
  end

  def to_a
    return [] unless head

    ret = [ head.value ]
    current = head.nxt
    while current != head
      ret << current.value
      current = current.nxt
    end
    ret
  end

  def delete(v)
    node = find(v)
    return unless node

    removeNode(node)
  end

  def deleteAt(i)
    node = getIndex(i)
    return unless node

    removeNode(node)
  end

  private

  def removeNode(n)
    n.prev.nxt = n.nxt
    n.nxt.prev = n.prev
    if n == self.head
      self.head = n.nxt
    end
  end

end
