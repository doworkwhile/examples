const util = require('util');
const Heap = require('./heap.js');

const MinHeap = function () {
  this.contents = [];
};

MinHeap.prototype.isOrdered = function (a, b) {
  return a < b;
};

util.inherits(MinHeap, Heap);

module.exports = MinHeap;
