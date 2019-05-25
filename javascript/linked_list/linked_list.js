var Node = function (v, nxt) {
  this.value = v;
  this.nxt = nxt;
};

var LinkedList = function () {
  this.head = null;
}

LinkedList.prototype.add = function(v) {
  if (!this.head) {
    this.head = new Node(v, null);
    return;
  }

  if (v < this.head.value) {
    this.head = new Node(v, this.head);
    return;
  }

  var current = this.head;
  while (current.nxt && current.nxt.value < v) {
    current = current.nxt;
  }
  current.nxt = new Node(v, current.nxt);
};

LinkedList.prototype.toString = function() {
  var ret = '[ ';
  var current = this.head;
  while (current) {
    ret += current.value;
    if (current.nxt) {
      ret += ', ';
    }
    current = current.nxt;
  }
  ret += ' ]';
  return ret;
};

LinkedList.prototype.inspect = function() {
  return '' + this.toString();
};

LinkedList.prototype.getIndexOf = function(v) {
  if (!this.head) {
    return -1;
  }

  var current = this.head;
  var i = 0;
  while (current) {
    if (current.value == v) {
      return i;
    }
    i++;
    current = current.nxt;
  }
};

var randLen = 10;
var randMin = 10;
var randMax = 100;
var randAry = new Array(randLen).fill(true).map(e => Math.floor(Math.random() * (randMax - randMin)) + randMin)
var ll = new LinkedList();
randAry.forEach(e => ll.add(e));
console.log(randAry)
console.log(''+ll);
var toFind = randAry[ Math.floor(Math.random() * randLen) ];
console.log('finding', toFind);
var found = ll.getIndexOf(toFind);
console.log('found at', found)
