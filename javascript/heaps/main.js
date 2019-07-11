const MinHeap = require('./min_heap.js');
const MaxHeap = require('./max_heap.js');

const testElements = [92, 15, 8, 82, 14, 93, 75, 44, 98, 84];

const minH = new MinHeap();
const maxH = new MaxHeap();

for (let elem of testElements) {
  minH.add(elem);
  maxH.add(elem);
}

// test min heap
let minOrderedAry = [];
let minOrdered = true;
console.log("=== test min heap");
console.log(minH.contents);
for (let i = 0; i < testElements.length; i++) {
  minOrderedAry.push( minH.poll() );
}
console.log(minOrderedAry);
for (let i = 0; i < minOrderedAry.length - 1; i++) {
  if (minOrdered) {
    minOrdered = minOrderedAry[i] < minOrderedAry[i + 1];
  }
}
console.log("Ordered? " + minOrdered);

// test max heap
let maxOrderedAry = [];
let maxOrdered = true;
console.log("=== test max heap");
console.log(maxH.contents);
for (let i = 0; i < testElements.length; i++) {
  maxOrderedAry.push( maxH.poll() );
}
console.log(maxOrderedAry);
for (let i = 0; i < maxH.size() - 1; i++) {
  if (maxOrdered) {
    maxOrdered = maxH[i] < maxH[i + 1];
  }
}
console.log("Ordered? " + maxOrdered);

// test remove
console.log("=== test remove");
for (let elem of testElements) {
  minH.add(elem);
  maxH.add(elem);
}
minH.remove(8);
maxH.remove(8);
console.log('min', minH.contents);
console.log('max', maxH.contents);


