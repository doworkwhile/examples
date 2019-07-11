const Heap = function () {
  this.contents = [];
};

// helper functions

// item location functions

Heap.prototype.getParentIndex = function (i) {
  return Math.floor((i - 1) / 2);
};

Heap.prototype.getLeftIndex = function (i) {
  return (i * 2) + 1;
};

Heap.prototype.getRightIndex = function (i) {
  return (i * 2) + 2;
};

Heap.prototype.hasParent = function (i) {
  return this.getParentIndex(i) >= 0;
};

Heap.prototype.hasLeft = function (i) {
  return this.getLeftIndex(i) < this.size();
};

Heap.prototype.hasRight = function (i) {
  return this.getRightIndex(i) < this.size();
};

Heap.prototype.parent = function (i) {
  return this.contents[this.getParentIndex(i)];
};

Heap.prototype.left = function (i) {
  return this.contents[this.getLeftIndex(i)];
};

Heap.prototype.right = function (i) {
  return this.contents[this.getRightIndex(i)];
};

Heap.prototype.swap = function (a, b) {
  const temp = this.contents[a];
  this.contents[a] = this.contents[b];
  this.contents[b] = temp;
};

Heap.prototype.isOrdered = function () {
  throw new Error("Subclass must implement isOrdered(a, b)");
};

Heap.prototype.isParentDisordered = function (i) {
  return !this.isOrdered(this.parent(i), this.contents[i]);
};

Heap.prototype.areChildrenOrdered = function (i) {
  return this.isOrdered(this.right(i), this.left(i));
};

Heap.prototype.isParentMissingOrOrdered = function (i) {
  return !this.hasParent(i) || !this.isParentDisordered(i);
};

Heap.prototype.empty = function () {
  return this.size() == 0;
};

Heap.prototype.size = function () {
  return this.contents.length;
};

// working methods

Heap.prototype.peek = function () {
  return this.contents[0];
};

Heap.prototype.peekEnd = function () {
  if (this.size() == 0) {
    return null;
  }

  return this.contents[this.size() - 1];
};

Heap.prototype.add = function (v) {
  this.contents.push(v);
  this.heapUp();
};

Heap.prototype.findAll = function (v) {
  const foundAt = [];

  for (let i = 0; i < this.size(); i++) {
    if (this.contents[i] == v) {
      foundAt.push(i);
    }
  }

  return foundAt;
};

Heap.prototype.find = function (v) {
  for (let i = 0; i < this.size(); i++) {
    if (this.contents[i] == v) {
      return i;
    }
  }

  return null;
};

Heap.prototype.poll = function () {
  if (this.size() == 0) {
    return null;
  }

  if (this.size() == 1) {
    return this.contents.shift();
  }

  const temp = this.peek();
  this.contents[0] = this.contents.pop();
  this.heapDown();
  return temp;
};

Heap.prototype.remove = function (v) {
  let removeIndex = true;
  while (removeIndex) {
    removeIndex = this.find(v);

    if (removeIndex == null) {
      break;
    }

    if (removeIndex == this.size() - 1) {
      this.contents.pop();
    } else {
      const lastItem = this.contents.pop();
      this.contents[removeIndex] = lastItem;

      if (this.hasLeft(removeIndex) &&
        this.isParentMissingOrOrdered(removeIndex)) {
        this.heapDown(removeIndex);
      } else {
        this.heapUp(removeIndex);
      }
    }
  }
};

// adjust heap up and down

Heap.prototype.heapUp = function (start) {
  let current = start || this.size() - 1;

  while (this.hasParent(current) && this.isParentDisordered(current)) {
    const parentIndex = this.getParentIndex(current);
    this.swap(parentIndex, current);
    current = parentIndex;
  }
};

Heap.prototype.heapDown = function (start) {
  let current = start || 0;
  let toSwap = null;

  while (this.hasLeft(current)) {
    if (this.hasRight(current) && this.areChildrenOrdered(current)) {
      toSwap = this.getRightIndex(current);
    } else {
      toSwap = this.getLeftIndex(current);
    }

    if (this.isOrdered(this.contents[current], this.contents[toSwap])) {
      break;
    }

    this.swap(current, toSwap);
    current = toSwap;
  }
};

module.exports = Heap;
