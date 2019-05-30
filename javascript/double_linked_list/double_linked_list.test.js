/* global test expect beforeEach */

const DoubleLinkedList = require('./double_linked_list.js');

let dll = null;
let randAry = null;

function randInRange (l, h) {
  return l + (Math.round(Math.random() * (h - l)));
}

function fillDLLRandAry () {
  const randMin = 10;
  const randMax = 100;
  randAry = new Array(10).fill(true).map(() => {
    return randInRange(randMin, randMax);
  });
  randAry.forEach((e) => dll.insertAt(0, e));
}

function verifySort (ary) {
  let last = null;
  for (let i = 0; i < ary.length; i++) {
    if (!last) {
      last = ary[i];
    } else if (ary[i] < last) {
      return false;
    }
  }
  return true;
}

function fillDLLSimple () {
  [10, 20, 30].forEach((e) => {
    dll.addSorted(e);
  });
}

beforeEach(() => {
  dll = new DoubleLinkedList();
});

test('DoubleLinkedList.addSorted(v) can insert items to always be a sorted list', () => {
  dll.addSorted(30);
  dll.addSorted(10);
  expect(dll.head.value).toBe(10);
  expect(dll.head.next.value).toBe(30);
});

test('DoubleLinkedList.to_s() can print the list', () => {
  // 0 items
  expect(dll.to_s()).toBe("[ ]");

  // 1 item
  dll.addSorted(1);
  expect(dll.to_s()).toBe("[ 1 ]");

  // multiple items
  dll.clear();
  fillDLLSimple();
  expect(dll.to_s()).toBe("[ 10, 20, 30 ]");
});

test('DoubleLinkedList.getIndex(i) can get the value at an index offset from head', () => {
  fillDLLSimple();
  /* the indexes wrap:
   *   0/3/-3 = 10
   *   1/-2 = 20
   *   2/-1 = 30
  */
  expect(dll.getIndex(0).value).toBe(10);
  expect(dll.getIndex(1).value).toBe(20);
  expect(dll.getIndex(2).value).toBe(30);
  expect(dll.getIndex(3).value).toBe(10);
  expect(dll.getIndex(-1).value).toBe(30);
  expect(dll.getIndex(-2).value).toBe(20);
  expect(dll.getIndex(-3).value).toBe(10);
});

test('DoubleLinkedList.indexOf(v) can get the index offset of a value, or -1', () => {
  fillDLLSimple();
  expect(dll.indexOf(10)).toBe(0);
  expect(dll.indexOf(20)).toBe(1);
  expect(dll.indexOf(30)).toBe(2);
  expect(dll.indexOf(-1)).toBe(-1);
});

test('DoubleLinkedList.insertAt(i, v) can insert v at index i', () => {
  fillDLLSimple();
  dll.insertAt(0, 5);
  expect(dll.head.value).toBe(5);
  dll.insertAt(-1, 40);
  expect(dll.head.prev.value).toBe(40);
  dll.insertAt(5, 50);
  expect(dll.head.prev.value).toBe(50);
  dll.insertAt(7, 7); // skips over head, because i != 0
  expect(dll.head.next.value).toBe(7);
});

test('DoubleLinkedList.clear() can clear the list', () => {
  fillDLLSimple();
  dll.clear();
  expect(dll.head).toBe(null);
});

test('DoubleLinkedList.to_a() can create an array of the list items', () => {
  fillDLLSimple();
  expect(dll.to_a().toString()).toBe([10,20,30].toString());
});

test('DoubleLinkedList.insertSort() can insert sort', () => {
  fillDLLRandAry();
  let dll_ary_a = dll.to_a();
  expect(verifySort(dll_ary_a)).toBe(false);
  dll.insertSort();
  let dll_ary_b = dll.to_a();
  expect(verifySort(dll_ary_b)).toBe(true);
});

test('DoubleLinkedList.shuffle() can shuffle the items', () => {
  fillDLLRandAry();
  const dll_ary_a = dll.to_a();
  dll.shuffle();
  const dll_ary_b = dll.to_a();
  expect(dll_ary_a != dll_ary_b).toBe(true);
});

test('DoubleLinkedList.bubbleSort() can bubble sort', () => {
  fillDLLRandAry();
  let dll_ary_a = dll.to_a();
  while (verifySort(dll_ary_a)) {
    fillDLLRandAry();
    dll_ary_a = dll.to_a();
  }
  expect(verifySort(dll_ary_a)).toBe(false);
  dll.bubbleSort();
  let dll_ary_b = dll.to_a();
  expect(verifySort(dll_ary_b)).toBe(true);
});

test('DoubleLinkedList.find(v) can return the node object with value v', () => {
  fillDLLRandAry();
  let dll_ary = dll.to_a();
  let randItm = dll_ary[randInRange(0, dll_ary.length)];
  expect(dll.find(randItm)).not.toBeNull(); // random item
  expect(dll.find(dll.head.value)).not.toBeNull(); // head
  expect(dll.find(dll.head.prev.value)).not.toBeNull(); // tail
  expect(dll.find(-1)).toBeNull(); // not in list
});

test('DoubleLinkedList.delete(v) can delete the node with value v', () => {
  fillDLLSimple();
  dll.delete(20); // middle
  expect(dll.to_a().toString()).toBe([10,30].toString());
  dll.clear();

  fillDLLSimple();
  dll.delete(10); // head
  expect(dll.to_a().toString()).toBe([20,30].toString());
  dll.clear();

  fillDLLSimple();
  dll.delete(30); // tail
  expect(dll.to_a().toString()).toBe([10,20].toString());
  dll.clear();
});

test('DoubleLinkedList.deleteAt(v) can delete the node with value v', () => {
  fillDLLSimple();
  dll.deleteAt(1); // middle
  expect(dll.to_a().toString()).toBe([10,30].toString());
  dll.clear();

  fillDLLSimple();
  dll.deleteAt(0); // head
  expect(dll.to_a().toString()).toBe([20,30].toString());
  dll.clear();

  fillDLLSimple();
  dll.deleteAt(2); // tail
  expect(dll.to_a().toString()).toBe([10,20].toString());
  dll.clear();

  fillDLLSimple();
  dll.deleteAt(-1); // tail, using negative
  expect(dll.to_a().toString()).toBe([10,20].toString());
  dll.clear();
});

test('DoubleLinkedList.swapIndexes(i1, i2) can swap the nodes at 2 indexes', () => {
  fillDLLSimple();
  dll.swapIndexes(0, 2);
  expect(dll.head.value).toBe(30);
  expect(dll.head.prev.value).toBe(10);
  dll.swapIndexes(2, 0);
  expect(dll.head.value).toBe(10);
  expect(dll.head.prev.value).toBe(30);
});

test('DoubleLinkedList.tail() can get the node behind the head', () => {
  fillDLLSimple();
  expect(dll.tail().value).toBe(30);
});