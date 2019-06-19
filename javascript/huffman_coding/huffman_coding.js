const HuffmanNode = function (symbol, freq) {
  this.symbol = symbol;
  this.freq = freq;
  this.left = null;
  this.right = null;
  this.next = null;
  this.prefix = '';
};

const SortedLinkedList = function () {
  this.head = null;
};

SortedLinkedList.prototype.insert = function (node) {
  if (!this.head) {
    this.head = node;
    return;
  }

  if (node.freq < this.head.freq) {
    node.next = this.head;
    this.head = node;
    return;
  }

  let current = this.head;
  while (current.next && current.next.freq < node.freq) {
    current = current.next;
  }
  node.next = current.next;
  current.next = node;
};

SortedLinkedList.prototype.pop = function () {
  if (!this.head) {
    return;
  }

  const ret = this.head;
  this.head = this.head.next;
  return ret;
};

SortedLinkedList.prototype.printList = function () {
  let current = this.head;
  process.stdout.write('[ ');
  while (current) {
    process.stdout.write("(" + current.symbol + ", " + current.freq + ") ");
    current = current.next;
  }
  console.log(']');
};

const HuffmanTree = function (symbol_and_freq_list) {
  this.head = null;
  this.combinedNodeChar = '$';
  this.ll = new SortedLinkedList();
  this.nodes = this.buildNodes(symbol_and_freq_list);
  for (let n of this.nodes) {
    this.ll.insert(n);
  }
  this.buildTree();
  this.buildPrefixes(this.head);
};

HuffmanTree.prototype.buildNodes = function (symbol_and_freq_list) {
  const ret = [];
  symbol_and_freq_list.forEach((e) => {
    ret.push(new HuffmanNode(e[0], e[1]));
  });
  return ret;
};

HuffmanTree.prototype.buildTree = function () {
  let building = true;
  while (building) {
    const node1 = this.ll.pop();
    const node2 = this.ll.pop();

    if (!node2) {
      this.head = node1;
      return;
    }

    const newFreq = node1.freq + node2.freq;
    const newNode = new HuffmanNode(this.combinedNodeChar, newFreq);
    newNode.left = node1;
    newNode.right = node2;
    this.ll.insert(newNode);
  }
};

HuffmanTree.prototype.buildPrefixes = function (current, parent, lastWentRight) {
  if (!current) {
    return;
  }

  if (parent) {
    current.prefix = parent.prefix;
    current.prefix += lastWentRight ? "0" : "1";
  }

  this.buildPrefixes(current.left, current, false);
  this.buildPrefixes(current.right, current, true);
};

HuffmanTree.prototype.printTree = function (current, depth) {
  if (!current) { return; }
  const fDepth = depth || 0;
  this.printTree(current.right, fDepth + 1);
  for (let i = 0; i < fDepth; i++) {
    process.stdout.write("---|");
  }
  console.log(current.symbol + ", " + current.freq + ", " + current.prefix);
  this.printTree(current.left, fDepth + 1);
};

HuffmanTree.prototype.symbol_and_prefix_list = function () {
  return this.nodes.map(e => [e.symbol, e.prefix]);
};

const ht = new HuffmanTree([
  ['a', 0],
  ['b', 1],
  ['c', 2],
  ['d', 3],
  ['e', 4]
]);

// console.log(ht.ll);
console.log(ht.symbol_and_prefix_list);
ht.printTree(ht.head);