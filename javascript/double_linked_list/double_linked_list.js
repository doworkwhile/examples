const Node = function (value, next, prev) {
  this.value = value;
  this.next = next;
  this.prev = prev;
};

const DoubleLinkedList = function () {
  this.head = null;
};

DoubleLinkedList.prototype.addSorted = function (v) {
  // no nodes
  if (!this.head) {
    this.head = new Node(v);
    this.head.next = this.head;
    this.head.prev = this.head;
    return;
  }
  let temp = new Node(v);

  // v is less than head
  if (this.head.value > v) {
    temp.next = this.head;
    temp.prev = this.head.prev;
    this.head.prev.next = temp;
    this.head.prev = temp;
    this.head = temp;
    return;
  }

  // find nodes that will surround
  let lastSmaller = this.head;
  let firstBigger = this.head.next;
  while(firstBigger != this.head && firstBigger.value < v) {
    lastSmaller = firstBigger;
    firstBigger = firstBigger.next;
  }
  temp.next = firstBigger;
  temp.prev = lastSmaller;
  lastSmaller.next = temp;
  firstBigger.prev = temp;
};

DoubleLinkedList.prototype.to_s = function () {
  if (!this.head) {
    return '[ ]';
  }

  let ret = '[ ' + this.head.value;
  let current = this.head.next;
  if (current != this.head) {
    ret += ', ';
  }
  while (current && current != this.head) {
    ret += current.value;
    if (current.next != this.head) {
      ret += ', ';
    }
    current = current.next;
  }
  ret += ' ]';
  return ret;
};

DoubleLinkedList.prototype.getIndex = function (i) {
  if (i == 0) {
    return this.head;
  }

  const moveRight = i > 0;
  const moveDelta = moveRight ? 1 : -1;
  let current = moveRight ? this.head : this.head.prev;
  let counter = moveRight ? 0 : -1;
  while (counter != i) {
    current = moveRight ? current.next : current.prev;
    counter += moveDelta;
  }
  return current;
};

DoubleLinkedList.prototype.indexOf = function (v) {
  if (!this.head) {
    return -1;
  }

  if (this.head.value == v) {
    return 0;
  }

  let counter = 1;
  let current = this.head.next;
  while (current != this.head) {
    if (current.value == v) {
      return counter;
    }
    current = current.next;
    counter++;
  }
  return -1;
};

DoubleLinkedList.prototype.swapIndexes = function (first, second) {
  if (first == second) {
    return;
  }

  const firstNode = this.getIndex(first);
  const secondNode = this.getIndex(second);

  this.swapNodes(firstNode, secondNode);
};

DoubleLinkedList.prototype.swapNodes = function (first, second) {

  // temp stores
  const snoldprev = second.prev;
  const fnoldnext = first.next;
  const adjacent = snoldprev == first;

  // first swap
  second.prev = first.prev;
  second.prev.next = second;
  first.next = second.next;
  first.next.prev = first;

  // checked adj swap
  if (adjacent) {
    second.next = first;
    first.prev = second;
  } else {
    second.next = fnoldnext;
    second.next.prev = second;
    first.prev = snoldprev;
    first.prev.next = first;
  }

  // checked new head
  if (this.head == first) {
    this.head = second;
  } else if (this.head == second) {
    this.head = first;
  }
};

DoubleLinkedList.prototype.insertAt = function (i, v) {
  // if no head, call generic add function
  if (!this.head) {
    this.addSorted(v);
    return;
  }

  const node = this.getIndex(i);
  let temp;

  if (i >= 0) {
    temp = new Node(v, node, node.prev);
    node.prev.next = temp;
    node.prev = temp;
    if (node == this.head && i == 0) {
      this.head = temp;
    }
  } else {
    // node = node.prev
    temp = new Node(v, node.next, node);
    node.next.prev = temp;
    node.next = temp;
  }
};

DoubleLinkedList.prototype.clear = function () {
  this.head = null;
};

DoubleLinkedList.prototype.insertSort = function () {
  // return if size is 0 or 1
  if (!this.head || !this.head.next) {
    return;
  }

  let outerCurrent = this.head.next;
  while (outerCurrent != this.head) {
    let backStep = outerCurrent.prev;
    if (backStep.value > outerCurrent.value) {
      // when we move outerCurrent, we lose the correct link to the next item
      // wherever outerCurrent moves, the next outerCurrent is always here
      const newOuter = outerCurrent.next;

      // step back until backStep is smaller than outerCurrent, or it's the head
      while(backStep != this.head && backStep.value > outerCurrent.value) {
        backStep = backStep.prev;
      }
      // release self
      outerCurrent.prev.next = outerCurrent.next;
      outerCurrent.next.prev = outerCurrent.prev;

      // if backStep == head and smaller, add before, else add after
      if (backStep == this.head && outerCurrent.value < backStep.value) {
        // update self
        outerCurrent.next = backStep;
        outerCurrent.prev = backStep.prev;

        // update surround
        backStep.prev.next = outerCurrent;
        backStep.prev = outerCurrent;

        // update head
        this.head = outerCurrent;
      } else {
        // update self
        outerCurrent.next = backStep.next;
        outerCurrent.prev = backStep;

        // update surround
        backStep.next.prev = outerCurrent;
        backStep.next = outerCurrent;
      }

      // move outerCurrent forward
      outerCurrent = newOuter;
    } else {
      outerCurrent = outerCurrent.next;
    }
  }
};

DoubleLinkedList.prototype.shuffle = function () {
  const lastIndex = this.indexOf(this.head.prev.value);
  for (let i = lastIndex; i > 0; i--) {
    const swapAt = Math.floor(Math.random() * i);
    this.swapIndexes(i, swapAt);
  }
};

DoubleLinkedList.prototype.bubbleSort = function () {
  if (!this.head || !this.head.next) {
    return;
  }

  let outer = this.head.prev;
  while (outer != this.head) {
    let current = this.head;
    while (current != outer) {
      if (current.next.value < current.value && current.next != this.head) {
        this.swapNodes(current, current.next);
        if (current.prev == outer) {
          outer = current;
        }
      } else {
        current = current.next;
      }
    }
    outer = outer.prev;
  }
};

DoubleLinkedList.prototype.find = function (v) {
  if (!this.head) {
    return null;
  }

  if (this.head.value == v) {
    return this.head;
  }

  let current = this.head.next;
  while (current != this.head) {
    if (current.value == v) {
      return current;
    }
    current = current.next;
  }
  return null;
};

DoubleLinkedList.prototype.deleteAt = function (i) {
  let toDelete = this.getIndex(i);

  if (!toDelete) {
    return false;
  }

  this.doDeletion(toDelete);
  return true;
};


DoubleLinkedList.prototype.delete = function (v) {
  let toDelete = this.find(v);

  if (!toDelete) {
    return false;

  }

  this.doDeletion(toDelete);
  return true;
};

DoubleLinkedList.prototype.doDeletion = function (node) {
  node.prev.next = node.next;
  node.next.prev = node.prev;

  if (node == this.head) {
    this.head = node.next;
  }
};

DoubleLinkedList.prototype.to_a = function () {
  if (!this.head) {
    return [];
  }

  let ret = [ this.head.value ];
  let current = this.head.next;
  while (current != this.head) {
    ret.push(current.value);
    current = current.next;
  }
  return ret;
};

DoubleLinkedList.prototype.tail = function () {
  if (!this.head) {
    return null;
  }
  return this.head.prev;
};

module.exports = DoubleLinkedList;