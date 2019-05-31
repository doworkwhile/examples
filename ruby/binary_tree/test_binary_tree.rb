require './binary_tree.rb'
require 'test/unit'


def fillSimple(bt)
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
def fillComplex(bt)
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


  def testAdd
    assert_equal(@bt.head, nil)
    fillSimple(@bt)

    assert_equal(@bt.head.value, 20)
    assert_equal(@bt.head.right.value, 30)
    assert_equal(@bt.head.left.value, 10)
  end

  def testFind
    fillSimple(@bt)

    assert_equal(@bt.find(20).value, 20)
    assert_equal(@bt.find(30).value, 30)
    assert_equal(@bt.find(10).value, 10)
  end
  
  def testClear
    fillSimple(@bt)
    assert_equal(@bt.head.value, 20)
    @bt.clear
    assert_equal(@bt.head, nil)
  end

  def testTo_a
    fillSimple(@bt)
    assert_equal(@bt.to_a, [10, 20, 30])

    @bt.clear
    fillComplex(@bt)
    assert_equal(@bt.to_a, [5, 7, 10, 15, 20, 25, 30, 35, 40, 50])
  end

  def testTo_a_preorder
    fillSimple(@bt)
    assert_equal(@bt.to_a_preorder, [20, 10, 30])

    @bt.clear
    fillComplex(@bt)
    assert_equal(@bt.to_a_preorder, [20, 10, 7, 5, 15, 30, 25, 40, 35, 50])
  end

  def testTo_a_postorder
    fillSimple(@bt)
    assert_equal(@bt.to_a_postorder, [10, 30, 20])

    @bt.clear
    fillComplex(@bt)
    assert_equal(@bt.to_a_postorder, [5, 7, 15, 10, 25, 35, 50, 40, 30, 20])
  end


  def testDelete
    fillComplex(@bt)
    @bt.delete(5)
    assert_equal(@bt.to_a, [7, 10, 15, 20, 25, 30, 35, 40, 50])

    @bt.clear
    fillComplex(@bt)
    @bt.delete(10)
    assert_equal(@bt.to_a, [5, 7, 15, 20, 25, 30, 35, 40, 50])

    @bt.clear
    fillComplex(@bt)
    @bt.delete(30)
    assert_equal(@bt.to_a, [5, 7, 10, 15, 20, 25, 35, 40, 50])

    @bt.clear
    fillComplex(@bt)
    @bt.delete(20)
    assert_equal(@bt.to_a, [5, 7, 10, 15, 25, 30, 35, 40, 50])
  end



end