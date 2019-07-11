const util = require('util');
const Heap = require('./heap.js');

const MaxHeap = function () {
  this.contents = [];
};

MaxHeap.prototype.isOrdered = function (a, b) {
  return a > b;
};

util.inherits(MaxHeap, Heap);

module.exports = MaxHeap;
