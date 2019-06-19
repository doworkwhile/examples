require '../linked_list/linked_list.rb'

class HuffmanNode < Node
  attr_accessor :symbol, :left, :right, :prefix
  def initialize(symbol, freq)
    super(freq)
    @symbol = symbol
    @prefix = ""
  end
end

class HuffmanTree
  attr_reader :head

  # accepts an array of symbol and frequence pairs
  # ex [ ['a', 0], ['b', 1], ...]
  def initialize(symbol_and_freq_list)
    @head = nil
    @falseNodeChar = '$'
    @ll = LinkedList.new
    @realNodes = build_nodes(symbol_and_freq_list)
    @realNodes.each { |n| @ll.add_node(n) }
    build_tree
    build_prefixes
  end

  def prefix_for(symbol)
    @realNodes.each { |hn|
      return hn.prefix if hn.symbol == symbol
    }
    nil
  end

  def symbol_and_prefix_list
    @realNodes.map { |hn|
      [hn.symbol, hn.prefix]
    }
  end

  private

  def build_nodes(symbol_and_freq_list)
    symbol_and_freq_list.map { |symbol_and_freq|
      symbol = symbol_and_freq[0]
      freq = symbol_and_freq[1]
      HuffmanNode.new(symbol, freq)
    }
  end

  def build_tree
    # continuously pop 2 nodes from the linked list

    while true
      node1 = @ll.pop
      node2 = @ll.pop

      # if there is only one node left, that's the head
      unless node2
        @head = node1
        return
      end

      # create a new node with combined frequency of both nodes
      # the new node is the parent of both nodes
      # node1 is left because it's value would be smaller, node2 is right
      new_freq = node1.value + node2.value
      new_node = HuffmanNode.new(@falseNodeChar, new_freq)
      new_node.left = node1
      new_node.right = node2
      # reinsert (sorted) the combined node
      @ll.add_node(new_node)
    end
  end

  def build_prefixes
    build_prefixes_recurse(@head, nil, false)
  end

  def build_prefixes_recurse(current, parent, went_right)
    return unless current

    if parent
      current.prefix = parent.prefix
      current.prefix += went_right ? "0" : "1"
    end

    build_prefixes_recurse(current.left, current, false)
    build_prefixes_recurse(current.right, current, true)
  end
end