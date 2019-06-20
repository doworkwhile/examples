const PriorityQueueElement = function (key, priority) {
  this.key = key;
  this.priority = priority;
};

const PriorityQueue = function () {
  this.elements = [];
};

PriorityQueue.prototype.add = function (key, priority) {
  this.elements.push(new PriorityQueueElement(key, priority));
  this.heapUp();
};

PriorityQueue.prototype.poll = function () {
  if (this.elements.length == 0) {
    return;
  }
  if (this.elements.length == 1) {
    return this.elements.pop().key;
  }

  const ret = this.elements[0];
  this.elements[0] = this.elements.pop();
  this.heapDown();
  return ret.key;
};

PriorityQueue.prototype.heapUp = function () {
  let current = this.elements.length - 1;
  while (this.isParentDisordered(current)) {
    const parentIndex = this.getParentIndex(current);
    this.swap(current, parentIndex);
    current = parentIndex;
  }
};

PriorityQueue.prototype.heapDown = function () {
  let current = 0;
  let nxt = 0;

  while (this.hasLeft(current)) {
    if (this.isRightLeftOrdered(current)) {
      nxt = this.getRightIndex(current);
    } else {
      nxt = this.getLeftIndex(current);
    }

    if (this.isOrdered(current, nxt)) {
      return;
    }

    this.swap(current, nxt);
    current = nxt;
  }
};

PriorityQueue.prototype.isOrdered = function (above, below) {
  return this.elements[above].priority < this.elements[below].priority;
};
PriorityQueue.prototype.isParentDisordered = function (i) {
  return this.hasParent(i) && !this.isOrdered(this.getParentIndex(i), i);
};
PriorityQueue.prototype.isRightLeftOrdered = function (i) {
  return this.hasRight(i) && this.isOrdered(this.getRightIndex(i), this.getLeftIndex(i));
};
PriorityQueue.prototype.parent = function (i) {
  return this.elements[this.getParentIndex(i)];
};
PriorityQueue.prototype.left = function (i) {
  return this.elements[this.getLeftIndex(i)];
};
PriorityQueue.prototype.right = function (i) {
  return this.elements[this.getRightIndex(i)];
};
PriorityQueue.prototype.hasParent = function (i) {
  return this.getParentIndex(i) >= 0;
};
PriorityQueue.prototype.hasLeft = function (i) {
  return this.getLeftIndex(i) < this.elements.length;
};
PriorityQueue.prototype.hasRight = function (i) {
  return this.getRightIndex(i) < this.elements.length;
};
PriorityQueue.prototype.getParentIndex = function (i) {
  return Math.floor((i - 1) / 2);
};
PriorityQueue.prototype.getLeftIndex = function (i) {
  return (i * 2) + 1;
};
PriorityQueue.prototype.getRightIndex = function (i) {
  return (i * 2) + 2;
};
PriorityQueue.prototype.swap = function (aIndex, bIndex) {
  const temp = this.elements[aIndex];
  this.elements[aIndex] = this.elements[bIndex];
  this.elements[bIndex] = temp;
};
PriorityQueue.prototype.isEmpty = function () {
  return this.elements.length == 0;
};

module.exports = PriorityQueue;