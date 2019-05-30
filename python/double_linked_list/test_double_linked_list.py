import unittest
from double_linked_list import DoubleLinkedList
import random
from random import sample

dll = DoubleLinkedList()
randAry = None

def fillListSimple(l):
  l.addSorted(10)
  l.addSorted(20)
  l.addSorted(30)

def fillListRand(l):
  randAry = list(map(lambda x: random.randint(10, 99), range(0, 10)))
  for i in randAry:
    l.insertAt(0, i)

def verifySorted(dll):
  ary = dll.to_a()
  last = None
  for n in ary:
    if last and n < last:
      return False
    last = n
  return True

class TestSum(unittest.TestCase):

  def tearDown(self):
    dll.clear()

  def testAddSorted(self):
    dll.addSorted(10)
    self.assertEqual(dll.head.v, 10)

  def testTo_s(self):
    firstString = dll.to_s()
    self.assertEqual(firstString, '[]')

    dll.addSorted(10)
    secondString = dll.to_s()
    self.assertEqual(secondString, '[ 10 ]')

    dll.addSorted(20)
    thirdString = dll.to_s()
    self.assertEqual(thirdString, '[ 10, 20 ]')

  def testTo_a(self):
    self.assertEqual(dll.to_a(), [])

    fillListSimple(dll)
    self.assertEqual(dll.to_a(), [10,20,30])


  def testSwapIndexes(self):
    fillListSimple(dll)
    self.assertEqual(dll.head.v, 10)
    self.assertEqual(dll.head.prev.v, 30)
    dll.swapIndexes(0, 2)
    self.assertEqual(dll.head.v, 30)
    self.assertEqual(dll.head.prev.v, 10)
    dll.swapIndexes(2, 0)
    self.assertEqual(dll.head.v, 10)
    self.assertEqual(dll.head.prev.v, 30)

  def testIndexOf(self):
    fillListSimple(dll)
    self.assertEqual(dll.indexOf(20), 1)
    self.assertEqual(dll.indexOf(-1), None)

  def testInsertAt(self):
    fillListSimple(dll)
    dll.insertAt(0, 5)
    self.assertEqual(dll.head.v, 5)
    dll.insertAt(4, 4)
    self.assertEqual(dll.tail().v, 4)
    dll.insertAt(-1, -1)
    self.assertEqual(dll.tail().v, -1)

  def testClear(self):
    fillListSimple(dll)
    self.assertEqual(dll.head.v, 10)
    dll.clear()
    self.assertEqual(dll.head, None)

  def testInsertSort(self):
    fillListRand(dll)
    self.assertEqual(verifySorted(dll), False)
    dll.insertSort()
    self.assertEqual(verifySorted(dll), True)

  def testShuffle(self):
    fillListRand(dll)
    dll.insertSort()
    self.assertEqual(verifySorted(dll), True)
    dll.shuffle()
    self.assertEqual(verifySorted(dll), False)

  def testBubbleSort(self):
    fillListRand(dll)
    self.assertEqual(verifySorted(dll), False)
    dll.bubbleSort()
    self.assertEqual(verifySorted(dll), True)

  def testFind(self):
    fillListRand(dll)
    randItem = sample(dll.to_a(), 1)[0]
    self.assertEqual(dll.find(randItem) == None, False)
    self.assertEqual(dll.find(-1) == None, True)

  def testLastIndex(self):
    fillListRand(dll)
    self.assertEqual(dll.lastIndex(), 9)

  def testDelete(self):
    fillListSimple(dll)
    self.assertEqual(dll.head.v, 10)
    dll.delete(10)
    self.assertEqual(dll.head.v, 20)
    self.assertEqual(dll.head.prev.v, 30)
    dll.delete(30)
    self.assertEqual(dll.head.prev.v, 20)

  def testDeleteAt(self):
    fillListSimple(dll)
    self.assertEqual(dll.head.v, 10)
    dll.deleteAt(0)
    self.assertEqual(dll.head.v, 20)
    self.assertEqual(dll.head.prev.v, 30)
    dll.deleteAt(1)
    self.assertEqual(dll.head.prev.v, 20)




if __name__ == '__main__':
  unittest.main()