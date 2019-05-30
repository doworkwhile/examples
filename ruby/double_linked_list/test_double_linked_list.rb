require './double_linked_list.rb'
require 'test/unit'

def fillArray(dll)
  dll.add(10)
  dll.add(20)
  dll.add(30)
end

def fillArrayRand(dll)
  # in case we accidentally generate a sorted array
  # we'll get new numbers here
  [*0...10].map { 10 + rand(89) }.each { |e| dll.insertAt(0, e) }
end

def isSorted?(dll)
  ary = dll.to_a
  last = nil
  for i in ary
    if last && i < last
      return false
    end
    last = i
  end
  true
end

class TestDoubleLinkedList < Test::Unit::TestCase

  def setup
    @dll = DoubleLinkedList.new
  end

  def teardown
    @dll = nil
  end

  def testAdd
    @dll.add(30)
    assert_equal(@dll.head.value, 30)
    @dll.add(10)
    assert_equal(@dll.head.value, 10)
  end

  def testTo_a
    assert_equal(@dll.to_a.size, 0)
    fillArray(@dll)
    assert_equal(@dll.to_a.size, 3)
  end

  def testTo_s
    assert_equal(@dll.to_s, '[]')
    fillArray(@dll)
    assert_equal(@dll.to_s, '[ 10, 20, 30 ]')
  end

  def testSwapIndexes
    fillArray(@dll)
    assert_equal(@dll.head.value, 10)
    @dll.swapIndexes(0, 2)
    assert_equal(@dll.head.value, 30)
    @dll.swapIndexes(2, 0)
    assert_equal(@dll.head.value, 10)
  end

  def testIndexOf
    fillArray(@dll)
    assert_equal(@dll.indexOf(20), 1)
    assert_equal(@dll.indexOf(-1), nil)
  end

  def testInsertAt
    fillArray(@dll)
    @dll.insertAt(0, 5)
    assert_equal(@dll.head.value, 5)
    @dll.insertAt(4, 4)
    assert_equal(@dll.tail.value, 4)
    @dll.insertAt(-1, -1)
    assert_equal(@dll.tail.value, -1)
  end

  def testClear
    fillArray(@dll)
    assert(!!@dll.head)
    @dll.clear
    assert(!@dll.head)
  end

  def testInsertSort
    fillArrayRand(@dll)
    while isSorted?(@dll) # ensure the random array isn't sorted already
      @dll.clear
      fillArrayRand(@dll)
    end

    assert(!isSorted?(@dll))
    @dll.insertSort
    assert(isSorted?(@dll))
  end

  def testShuffle
    fillArrayRand(@dll)
    @dll.insertSort
    assert(isSorted?(@dll))
    @dll.shuffle
    assert(!isSorted?(@dll))
  end

  def testBubbleSort
    fillArrayRand(@dll)
    while isSorted?(@dll) # ensure the random array isn't sorted already
      @dll.clear
      fillArrayRand(@dll)
    end

    assert(!isSorted?(@dll))
    @dll.insertSort
    assert(isSorted?(@dll))
  end

  def testLastIndex
    fillArrayRand(@dll)
    assert_equal(@dll.lastIndex, 9)
  end

  def testFind
    fillArrayRand(@dll)
    toFind = @dll.to_a.sample
    assert(!!@dll.find(toFind))
    assert(!@dll.find(-1))
  end

  def testDelete
    fillArray(@dll)
    @dll.delete(10)
    assert_equal(@dll.head.value, 20)
    @dll.delete(30)
    assert_equal(@dll.head.nxt.value, 20)
  end

  def testDeleteAt
    fillArray(@dll)
    @dll.deleteAt(0)
    assert_equal(@dll.head.value, 20)
    @dll.deleteAt(1)
    assert_equal(@dll.head.nxt.value, 20)
  end

end