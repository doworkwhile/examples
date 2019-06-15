require './binary_tree.rb'
require 'test/unit'


def fill_simple(bt)
  bt.add(20)
  bt.add(30)
  bt.add(10)
end

=begin
        20
    10      30
  7   15  25    40
5             35  50
=end
def fill_complex(bt)
  bt.add(20)
  bt.add(10)
  bt.add(15)
  bt.add(7)
  bt.add(5)
  bt.add(30)
  bt.add(25)
  bt.add(40)
  bt.add(35)
  bt.add(50)
end

class TestBinaryTree < Test::Unit::TestCase

  def setup
    @bt = BinaryTree.new
  end


  def test_add
    assert_equal(@bt.head, nil)
    fill_simple(@bt)

    assert_equal(@bt.head.value, 20)
    assert_equal(@bt.head.right.value, 30)
    assert_equal(@bt.head.left.value, 10)
  end

  def test_find
    fill_simple(@bt)

    assert_equal(@bt.find(20).value, 20)
    assert_equal(@bt.find(30).value, 30)
    assert_equal(@bt.find(10).value, 10)
  end
  
  def test_clear
    fill_simple(@bt)
    assert_equal(@bt.head.value, 20)
    @bt.clear
    assert_equal(@bt.head, nil)
  end

  def test_to_a
    fill_simple(@bt)
    assert_equal(@bt.to_a, [10, 20, 30])

    @bt.clear
    fill_complex(@bt)
    assert_equal(@bt.to_a, [5, 7, 10, 15, 20, 25, 30, 35, 40, 50])
  end

  def test_to_a_preorder
    fill_simple(@bt)
    assert_equal(@bt.to_a_preorder, [20, 10, 30])

    @bt.clear
    fill_complex(@bt)
    assert_equal(@bt.to_a_preorder, [20, 10, 7, 5, 15, 30, 25, 40, 35, 50])
  end

  def test_to_a_postorder
    fill_simple(@bt)
    assert_equal(@bt.to_a_postorder, [10, 30, 20])

    @bt.clear
    fill_complex(@bt)
    assert_equal(@bt.to_a_postorder, [5, 7, 15, 10, 25, 35, 50, 40, 30, 20])
  end


  def test_delete
    fill_complex(@bt)
    @bt.delete(5)
    assert_equal(@bt.to_a, [7, 10, 15, 20, 25, 30, 35, 40, 50])

    @bt.clear
    fill_complex(@bt)
    @bt.delete(10)
    assert_equal(@bt.to_a, [5, 7, 15, 20, 25, 30, 35, 40, 50])

    @bt.clear
    fill_complex(@bt)
    @bt.delete(30)
    assert_equal(@bt.to_a, [5, 7, 10, 15, 20, 25, 35, 40, 50])

    @bt.clear
    fill_complex(@bt)
    @bt.delete(20)
    assert_equal(@bt.to_a, [5, 7, 10, 15, 25, 30, 35, 40, 50])
  end

  def test_find_depth
    fill_complex(@bt)

    # get the list of items in ascending order
    ordered_items = @bt.to_a

    # map the depth of every item
    depths = ordered_items.map { |e| @bt.find_depth(e) }

    # compare to pre-calculated list
    assert_equal(depths, [3, 2, 1, 2, 0, 2, 1, 3, 2, 3])
  end

  def test_depth_max
    assert_equal(@bt.depth_max, 0)

    @bt.add(1)
    assert_equal(@bt.depth_max, 1)

    @bt.clear
    fill_simple(@bt)
    assert_equal(@bt.depth_max, 2)

    @bt.clear
    fill_complex(@bt)
    assert_equal(@bt.depth_max, 4)
  end

  def test_depth_count
    fill_complex(@bt)

    # for each depth, get the count of nodes
    @bt.depth_count(@head)
    depth_counts = [*1..@bt.depth_max].map { |e| @bt.depth_count(e) }

    # compare to pre-calculated list
    assert_equal(depth_counts, [1, 2, 4, 3])
  end

  def test_depth_find
    assert_equal(@bt.depth_find(0), [])
    assert_equal(@bt.depth_find(1), [])

    @bt.add(1)
    assert_equal(@bt.depth_find(0), [])
    assert_equal(@bt.depth_find(1), [1])

    @bt.clear
    fill_simple(@bt)
    assert_equal(@bt.depth_find(1), [20])
    assert_equal(@bt.depth_find(2), [10, 30])

    @bt.clear
    fill_complex(@bt)
    assert_equal(@bt.depth_find(1), [20])
    assert_equal(@bt.depth_find(2), [10, 30])
    assert_equal(@bt.depth_find(3), [7, 15, 25, 40])
    assert_equal(@bt.depth_find(4), [5, 35, 50])
  end

  def test_make_linked_list
    fill_complex(@bt)

    ary = @bt.to_a
    i = 0


    @bt.make_linked_list
    # test the sorted linked list by traversing and comparing indexes
    # to a saved sorted array
    current = @bt.head
    while current
      assert_equal(ary[i], current.value)
      current = current.right
      i += 1
    end
  end

  def test_make_balanced
    fill_simple(@bt)
    @bt.make_balanced

    @bt.clear
    fill_complex(@bt)
    @bt.make_balanced
    assert_equal(@bt.depth_max, 4)

    @bt.clear()
    (0...100).each { |i| @bt.add(i) }
    @bt.make_balanced
    assert_equal(@bt.depth_max, 7)
  end



end