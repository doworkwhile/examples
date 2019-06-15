class Leaf
  attr_accessor :value, :left, :right
  def initialize(value, left=nil, right=nil)
    @value = value
    @left = left
    @right = right
  end
end

class BinaryTree

  attr_reader :head

  def initialize
    @head = nil
  end

  def add(v)
    unless @head
      @head = Leaf.new(v)
      return
    end

    current = @head
    while current.value != v
      if v < current.value
        current.left = Leaf.new(v) unless current.left
        current = current.left
      else
        current.right = Leaf.new(v) unless current.right
        current = current.right
      end
    end
  end

  def find(v)
    return nil unless @head

    current = @head
    while current
      if v == current.value
        return current
      elsif v > current.value
        current = current.right
      else
        current = current.left
      end  
    end
    return nil
  end

  def clear
    @head = nil
  end

  def delete(v)
    return false unless @head

    # find the node by value, save the parent node
    # and save a boolean that indicates if we last went right(t) or left(f)
    parent = nil
    current = @head
    last_went_right = false
    while current.value != v
      parent = current
      if v > current.value
        last_went_right = true
        current = current.right
      else
        last_went_right = false
        current = current.left
      end 
      return false unless current
    end

    # 4 possible conditions:
    # if both children
    # if right child
    # if left child
    # else no children
    if current.right && current.left
      return deletion_case_both_children(current)
    elsif current.right
      return deletion_replace_top(parent, current.right, last_went_right)
    elsif current.left
      return deletion_replace_top(parent, current.left, last_went_right)
    else
      return deletion_replace_top(parent, nil, last_went_right)
    end
  end

  def to_a
    inorder_to_a(@head)
  end

  def to_a_preorder
    preorder_to_a(@head)
  end

  def to_a_postorder
    postorder_to_a(@head)
  end

  def find_depth(v)
    current = @head
    depth = 0
    while current
      if current.value == v
        return depth
      elsif v < current.value
        current = current.left
      else # v > current.value
        current = current.right
      end
      depth += 1
    end
    nil
  end

  def depth_max
    depth_max_from(@head)
  end

  def depth_count(depth)
    found_at_depth = 0
    traverse_in_order(@head, 1, depth) { |node, node_depth|
      if node_depth == depth
        found_at_depth += 1
      end
    }
    return found_at_depth
  end

  def depth_find(depth)
    set_found_at_depth = []
    traverse_in_order(@head, 1, depth) { |node, node_depth|
      if node_depth == depth
        set_found_at_depth << node.value
      end
    }
    return set_found_at_depth
  end

  def make_linked_list
    return unless @head
    grandparent = nil
    parent = @head
    left_child = nil

    # starting at parent = root
    while parent
      left_child = parent.left

      # if there is a left child
      if left_child

        # this is a "right rotation"
        # move the left child between the grandparent and parent
        # if there is no grandparent, the left child becomes the head
        if grandparent
          grandparent.right = left_child
        else
          @head = left_child
        end
        # now the grandparent.right/head is the left child

        # set the old link to left child to the left childs right child
        parent.left = left_child.right
        # now the left childs right child is the parent
        left_child.right = parent

        # what used to be down left, is now up
        # the old left child could still have more children so move up
        parent = left_child
      else
        # if no left child
        # move down right
        grandparent = parent
        parent = parent.right
      end
    end
  end

  def make_balanced
    # first convert to a linked list
    make_linked_list

    # find the length of the linked list
    # don't just check the max depth, we don't need to check any left nodes
    leaf_count = 0
    start = @head
    while start
      leaf_count += 1
      start = start.right
    end

    # EX
    # leaf_count = 10
    # count_msb_of = 1011
    # msb_shifts = 3
    # rotations_to_half = 7 (1 << 3 = 1000 then 0111 after -1)
    # first_rotation = 3 (10 - 7)
    # then 7/2 > 1, rotate floor(7/2) times
    # then 3/2 > 1, rotate(3/2) times
    # then 1/2 < 1, finished

    count_msb_of = leaf_count + 1
    msb_shifts = 0
    while (1 < count_msb_of)
      count_msb_of = (count_msb_of >> 1)
      msb_shifts += 1
    end
    rotations_to_half = (1 << msb_shifts) - 1


    first_rotation = leaf_count - rotations_to_half
    balance_rotation(first_rotation)

    while (rotations_to_half > 1)
      rotations_to_half /= 2
      balance_rotation(rotations_to_half)
    end

  end

  def doPrint()
    traverse_in_order(@head) { |n, d|
      (d - 1).times { print "---|" }
      puts "#{n.value}"
    }
  end

  private

  def inorder_to_a(leaf, ret=[])
    return unless leaf
    inorder_to_a(leaf.left, ret)
    ret << leaf.value
    inorder_to_a(leaf.right, ret)
    ret
  end

  def preorder_to_a(leaf, ret=[])
    return unless leaf
    ret << leaf.value
    preorder_to_a(leaf.left, ret)
    preorder_to_a(leaf.right, ret)
    ret
  end

  def postorder_to_a(leaf, ret=[])
    return unless leaf
    postorder_to_a(leaf.left, ret)
    postorder_to_a(leaf.right, ret)
    ret << leaf.value
    ret
  end

  def deletion_case_both_children(current)
    return false unless current.right

    # find the node larger than current
    # we expect current.right to not be nil
    min_parent = current.right
    min_at_right = current.right
    while min_at_right.left != nil
      min_parent = min_at_right
      min_at_right = min_at_right.left
    end

    # swap values
    current.value = min_at_right.value

    # if replacement is immediately to right,
    if min_parent == min_at_right
      current.right = nil
    else
      min_parent.left = min_at_right.right
    end
    true
  end

  def deletion_replace_top(parent, successor, direction_right)
    unless parent
      @head = successor
    else
      if direction_right
        parent.right = successor
      else
        parent.left = successor
      end
    end
    true
  end

  def depth_max_from(from=nil, mem=0)
    return mem unless from
    return [
      mem + 1,
      depth_max_from(from.left, mem + 1),
      depth_max_from(from.right, mem + 1)
    ].max
  end

  def traverse_in_order(start, current_depth=1, max_depth=nil)
    return unless start
    return if max_depth && current_depth > max_depth
    traverse_in_order(start.left, current_depth + 1, max_depth) { |e, n|
      yield(e, n)
    }
    yield(start, current_depth)
    traverse_in_order(start.right, current_depth + 1, max_depth) { |e, n|
      yield(e, n)
    }
  end

  # this is a "left rotation"
  # move the parent down left of the right child 
  def balance_rotation(rotations)
    grandparent = nil
    parent = @head
    right_child = @head.right

    # repeat "rotations" # of times
    while rotations > 0
      # in case the # of rotations was too much
      break unless right_child

      # rotate left
      # move the right child of the parent to the right of the grandparent
      # (if no grandparent, it becomes the head)
      if grandparent
        grandparent.right = right_child
      else
        @head = right_child
      end
      # the parents right is now the right childs left child
      parent.right = right_child.left
      # set the right childs left to the parent
      right_child.left = parent
      # end rotate left

      # the new grandparent is the right child
      grandparent = right_child
      # the new parent is to the right of the grandparent
      # which was the old right child (which may not have another right child)
      parent = grandparent.right
      # if the old right child had another right child, we use that
      # for the next iteration
      right_child = parent ? parent.right : nil

      # that was one rotation
      rotations -= 1
    end
  end
end