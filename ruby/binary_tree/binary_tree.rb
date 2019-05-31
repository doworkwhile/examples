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
    lastWentRight = false
    while current.value != v
      parent = current
      if v > current.value
        lastWentRight = true
        current = current.right
      else
        lastWentRight = false
        current = current.left
      end 
      return false unless current
    end
    
    # 4 possible conditions:
    # if both children
    # if no children
    # if right child
    # if left child
    if !current.right && !current.left
      return deletionCaseNoChildren(current, parent, lastWentRight)
    elsif current.right && current.left
      return deletionCaseBothChildren(current, parent)
    elsif current.right
      return deletionCaseOneChild(parent, current.right, lastWentRight)
    elsif current.left
      return deletionCaseOneChild(parent, current.left, lastWentRight)
    end

    # just in case
    false
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

  end

  def depth_count(depth)

  end

  def depth_find(depth)

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

  def deletionCaseNoChildren(current, parent, directionRight)
    unless parent
      @head = nil
    else
      if directionRight
        parent.right = nil
      else
        parent.left = nil
      end
    end
    true
  end

  def deletionCaseBothChildren(current, parent)
    return false unless current.right

    # find the node larger than current
    # we expect current.right to not be nil
    minParent = current.right
    minAtRight = current.right
    while minAtRight.left != nil
      minParent = minAtRight
      minAtRight = minAtRight.left
    end

    # swap values
    current.value = minAtRight.value

    # if replacement is immediately to right,
    if minParent == minAtRight
      current.right = nil
    else
      minParent.left = minAtRight.right
    end
    true
  end

  def deletionCaseOneChild(parent, successor, directionRight)
    unless parent
      self.head = successor
    else
      if directionRight
        parent.right = successor
      else
        parent.left = successor
      end
    end
    true
  end
end