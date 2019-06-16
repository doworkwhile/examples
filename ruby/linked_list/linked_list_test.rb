require './linked_list.rb'
require 'test/unit'

def fill_array(ll)
  10.times { ll.add(rand(99)) }
end

class TestLinkedList < Test::Unit::TestCase

  def setup
    @ll = LinkedList.new
  end

  def teardown
    @ll = nil
  end

  def test_add
    @ll.add(30)
    assert_equal(@ll.head.value, 30)
    @ll.add(10)
    assert_equal(@ll.head.value, 10)
  end

  def test_add_node
    node1 = Node.new(30)
    @ll.add_node(node1)
    assert_equal(@ll.head.value, 30)
    node2 = Node.new(10)
    @ll.add_node(node2)
    assert_equal(@ll.head.value, 10)
  end

  def test_find
    rand_array = [*0..9].map { rand(99) }
    rand_array.each { |i| @ll.add(i) }
    rand_find = rand_array.sample
    assert_equal(rand_find, @ll.find(rand_find).value)
  end

  def test_pop
    @ll.add(30)
    @ll.add(10)
    assert_equal(@ll.pop.value, 10)
    assert_equal(@ll.head.value, 30)
  end
  
end