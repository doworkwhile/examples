const AhoCorasickNode = function (letter) {
  this.word = null;
  this.letter = letter;
  this.prevLink = null;
  this.outputLink = null;
  this.suffixLink = null;
  this.children = {};
};

AhoCorasickNode.prototype.getChildOfLetter = function (letter) {
  return this.children[letter];
};

AhoCorasickNode.prototype.addChild = function (letter) {
  const newNode = new AhoCorasickNode(letter);
  newNode.prevLink = this;
  this.children[letter] = newNode;
  return newNode;
};

AhoCorasickNode.prototype.setWord = function (word) {
  this.word = word;
};

AhoCorasickNode.prototype.setOutputLink = function (outputLinkNode) {
  this.outputLink = outputLinkNode;
};

AhoCorasickNode.prototype.setSuffixLink = function (suffixLinkNode) {
  this.suffixLink = suffixLinkNode;
};

AhoCorasickNode.recursivePrint = function (start, depth) {
  const realDepth = depth || 0;

  let outputString = '';
  for (let i = 0; i < realDepth; i++) {
    outputString += "----|";
  }
  outputString += " " + start.letter;
  if (start.word) {
    outputString += " (" + start.word + ")";
  }
  if (start.suffixLink) {
    outputString += " [" + start.suffixLink.letter + "]";
  }
  if (start.outputLink) {
    outputString += " {" + start.outputLink.word + "}";
  }
  console.log(outputString);

  const childKeys = Object.keys(start.children);
  for (let key of childKeys) {
    const child = start.children[key];
    AhoCorasickNode.recursivePrint(child, realDepth + 1);
  }
};

AhoCorasickNode.prototype.getAllChildren = function () {
  return Object.values(this.children);
};

module.exports = AhoCorasickNode;
