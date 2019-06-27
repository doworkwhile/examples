class RedBlackNode

  attr_accessor :value, :red, :parent, :left, :right

  def initialize(value, red=true, parent=nil, left=nil, right=nil)
    self.value  = value
    self.red    = red
    self.parent = parent
    self.left   = left
    self.right  = right
  end

  def to_s
    self.value.to_s + (self.red ? "R" : "B")
  end

end

class RedBlackTree

  attr_accessor :head

  def initialize()
    self.head = nil
  end

  def insert(value)
    unless self.head
      self.head = RedBlackNode.new(value)
      insert_adjustment(self.head)
      return
    end

    insert_search = self.head
    insert_node = RedBlackNode.new(value)
    while insert_search.value != value
      if value < insert_search.value
        unless insert_search.left
          insert_search.left = insert_node
          insert_node.parent = insert_search
        end
        insert_search = insert_search.left
      else
        unless insert_search.right
          insert_search.right = insert_node
          insert_node.parent = insert_search
        end
        insert_search = insert_search.right
      end
    end

    # re-balance tree after insertion
    insert_adjustment(insert_node)
  end

  def find(value)
    # the loop is skipped when the tree head is nil
    find_search = self.head
    while find_search
      if find_search.value == value
        return find_search
      elsif value < find_search.value
        find_search = find_search.left
      else # value > find_search.value
        find_search = find_search.right
      end
    end

    return nil
  end

  def delete(value)
    found_node = find(value)
    return unless found_node

    # swap found node value with the largest node on the left
    # (the node with the highest value below the found node)
    # after the value change, the largest node on the left is what we
    # want to perform the other operations on (working_node)
    working_node = found_node
    if working_node.left
      max_left = get_max_on_left(working_node)
      working_node.value = max_left.value
      working_node = max_left
    end

    replace_working_node = (working_node.left.nil? ?
      working_node.right : working_node.left)
    # if the node has a left or right
    if replace_working_node
      # if node is the head, replace it
      if working_node == self.head
        self.head = replace_working_node
      # if the node is the parents left, replace on the left
      elsif working_node == get_left(working_node.parent)
        set_left(working_node.parent, replace_working_node)
      else
      # if the node is the parents right, replace on the right
        set_right(working_node.parent, replace_working_node)
      end

      # unless the node we're deleting is red, we have to adjust the tree
      unless working_node.red
        deletion_adjustment(working_node)
      end
    elsif working_node == self.head
    # the node to remove is the head
      self.head = nil
    else
    # no left or right, not the head
      # unless the node we're deleting is red, we have to adjust the tree
      unless working_node.red
        deletion_adjustment(working_node)
      end

    # just detach the node from its parent
      detach_parent(working_node)
    end
  end

  def display
    unless self.head
      puts "Tree is empty!"
      return
    end

    display_recurse(self.head)
  end

  private

  ### rotations & adjustments for correcting the tree structure

  def rotate_right(from_node)
    left_of_from = from_node.left
    return unless left_of_from

    parent_of_from = get_parent(from_node)

    set_left(from_node, left_of_from.right)

    if get_parent(from_node).nil?
      self.head = left_of_from
    elsif from_node == get_left(parent_of_from)
      set_left(parent_of_from, left_of_from)
    else # from_node == get_right(parent_of_from)
      set_right(parent_of_from, left_of_from)
    end

    set_right(left_of_from, from_node)
  end

  def rotate_left(from_node)
    right_of_from = from_node.right
    return unless right_of_from

    parent_of_from = get_parent(from_node)

    set_right(from_node, right_of_from.left)

    if parent_of_from.nil?
      self.head = right_of_from
    elsif from_node == get_left(parent_of_from)
      set_left(parent_of_from, right_of_from)
    else # from_node == get_right(parent_of_from)
      set_right(parent_of_from, right_of_from)
    end

    set_right(right_of_from, from_node)
  end

  def insert_adjustment(from_node)
    parent_of_from = get_parent(from_node)
    if from_node && from_node != self.head && is_red(parent_of_from)
      sibling_of_parent_of_from = get_sibling(parent_of_from)
      grandparent_of_from = get_parent(parent_of_from)
      parent_is_right_of_grandparent = (
        parent_of_from == get_right(grandparent_of_from))
      from_is_right_of_parent = (from_node == get_right(parent_of_from))

      get_node_is_red(parent_of_from)

      if is_red(sibling_of_parent_of_from)
        set_node_to_red(parent_of_from, false)
        set_node_to_red(sibling_of_parent_of_from, false)
        set_node_to_red(grandparent_of_from, true)
        insert_adjustment(grandparent_of_from)
      elsif !parent_is_right_of_grandparent
        if from_is_right_of_parent
          from_node = parent_of_from
          rotate_left(from_node)
        end

        # after rotation our parent has changed
        new_parent_of_from = get_parent(from_node)
        new_grandparent_of_from = get_parent(new_parent_of_from)
        set_node_to_red(new_parent_of_from, false)
        set_node_to_red(new_grandparent_of_from, true)
        rotate_right(new_grandparent_of_from)
      else # parent_is_right_of_grandparent
        if from_is_right_of_parent == false
          from_node = parent_of_from
          rotate_right(from_node)
        end

        new_parent_of_from = get_parent(from_node)
        new_grandparent_of_from = get_parent(new_parent_of_from)
        set_node_to_red(new_parent_of_from, false)
        set_node_to_red(new_grandparent_of_from. true)
        rotate_left(new_grandparent_of_from)
      end
    end
    set_node_to_red(self.head, false)
  end

  def deletion_adjustment(from_node)
    while from_node != self.head && from_node.red == false
      parent_of_from = from_node.parent

      # node is left of parent
      if from_node == get_left(get_parent(from_node))
        sibling = get_right(get_parent(from_node))

        if is_red(sibling)
          set_node_to_red(sibling, false)
          set_node_to_red(get_parent(from_node), true)
          rotate_left(get_parent(from_node))
          sibling = get_right(get_parent(from_node))
        end

        if is_black(get_left(sibling)) && is_black(get_right(sibling))
          set_node_to_red(sibling, true)
          from_node = get_parent(from_node)
        else
          if (is_black(get_right(sibling)))
            set_node_to_red(get_left(sibling), false)
            set_node_to_red(sibling, true)
            rotate_right(sibling)
            sibling = get_right(get_parent(from_node))
          end

          set_node_to_red(sibling, get_node_is_red(get_parent(from_node)))
          set_node_to_red(get_parent(from_node), false)
          set_node_to_red(get_right(sibling), false)
          rotate_left(get_parent(from_node))
          from_node = self.head
        end

      else
      # node is right of parent
        sibling = get_left(get_parent(from_node))

        if is_red(sibling)
          set_node_to_red(sibling, false)
          set_node_to_red(get_parent(from_node), true)
          rotate_right(get_parent(from_node))
          sibling = get_left(get_parent(from_node))
        end

        if is_black(get_left(sibling)) && is_black(get_right(sibling))
          set_node_to_red(sibling, true)
          from_node = get_parent(from_node)
        else
          if (is_black(get_left(sibling)))
            set_node_to_red(get_right(sibling), false)
            set_node_to_red(sibling, true)
            rotate_left(sibling)
            sibling = get_left(get_parent(from_node))
          end

          set_node_to_red(sibling, get_node_is_red(get_parent(from_node)))
          set_node_to_red(get_parent(from_node), false)
          set_node_to_red(get_left(sibling), false)
          rotate_right(get_parent(from_node))
          from_node = self.head
        end
      end
    end
  end

  ### methods to get node relatives that can handle a nil node
  # these help the tree methods reduce nil checks inside their algorithms

  def is_red(node)
    node.nil? ? false : node.red
  end

  def is_black(node)
    node.nil? ? false : node.red
  end

  def get_left(node)
    node.nil? ? nil : node.left
  end

  def get_right(node)
    node.nil? ? nil : node.right
  end

  def get_parent(node)
    node.nil? ? nil : node.parent
  end

  def get_sibling(node)
    node_parent = get_parent(node)

    return nil unless node_parent

    was_left = (node == node_parent.left)

    return was_left ? node_parent.right : node_parent.left
  end

  def get_grandparent(node)
    get_parent(get_parent(node))
  end

  def set_node_to_red(node, isRed)
    if node
      node.red = isRed
    end
  end

  def get_node_is_red(node)
    node.nil? ? nil : node.red
  end

  def set_left(node, left)
    # detach node left parent connection
    if node.left
      node.left.parent = nil
    end

    # remove new left old parent
    # set new left parent to node
    if left
      detach_parent(left)
      left.parent = node
    end

    # now node left is new left
    node.left = left
  end

  def set_right(node, right)
    # detach node right parent connection
    if node.right
      node.right.parent = nil
    end

    # remove new right old parent
    # set new right parent to node
    if right
      detach_parent(right)
      right.parent = node
    end

    # now node right is new right
    node.right = right
  end

  def detach_parent(node)
    node_parent = get_parent(node)

    return unless node_parent

    was_left = (node == node_parent.left)

    if was_left
      node_parent.left = nil
    else
      node_parent.right = nil
    end
  end

  def get_max_on_left(node)
    search = node.left
    return nil unless search

    while search.right
      search = search.right
    end

    return search
  end

  ### printing

  def display_recurse(node, depth = 0)
    return unless node

    display_recurse(node.right, depth + 1)
    depth.times { print "----|" }
    puts node.to_s
    display_recurse(node.left, depth + 1)
  end

end


rbt = RedBlackTree.new()
(1...16).reverse_each { |e| rbt.insert(e) }
rbt.display()
