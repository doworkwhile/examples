const AhoCorasickNode = require('./aho_corasick_node.js');

const AhoCorasickTrie = function () {
  this.head = new AhoCorasickNode('*');
  this.built = false;
};

AhoCorasickTrie.prototype.add = function (word) {
  this._addLettersOfWord(word);
};

AhoCorasickTrie.prototype._addLettersOfWord = function (word) {
  let walkingNode = this.head;

  for (let i = 0; i < word.length; i++) {
    const letter = word[i];
    const foundChild = walkingNode.getChildOfLetter(letter);

    if (foundChild) {
      walkingNode = foundChild;
    } else {
      walkingNode = walkingNode.addChild(letter);
    }
  }

  walkingNode.word = word;
};

AhoCorasickTrie.prototype._buildSuffixLinks = function () {
  const que = [this.head];

  while (que.length > 0) {
    const walkingNode = que.shift();

    if (walkingNode.prevLink == this.head) {
      walkingNode.suffixLink = this.head;
    } else {
      this._walkSuffixLinks(walkingNode);
    }

    this._loadNodeChildrenIntoQueue(walkingNode, que);
  }
};

AhoCorasickTrie.prototype._walkSuffixLinks = function (node) {
  if (node.prevLink == null) {
    return;
  }

  let walkingSuffix = node.prevLink;
  while (walkingSuffix.suffixLink) {
    walkingSuffix = walkingSuffix.suffixLink;

    const walkingSuffixChild = walkingSuffix.getChildOfLetter(node.letter);
    if (walkingSuffixChild) {
      node.suffixLink = walkingSuffixChild;
      break;
    }
  }

  if (node.suffixLink == null) {
    node.suffixLink = this.head;
  }
};

AhoCorasickTrie.prototype._buildOutputLinks = function () {
  const que = [this.head];

  while (que.length > 0) {
    const walkingNode = que.shift();

    const walkingSuffix = walkingNode.suffixLink;
    if (walkingSuffix) {
      if (walkingSuffix.word) {
        walkingNode.outputLink = walkingSuffix;
      } else if (walkingSuffix.outputLink) {
        walkingNode.outputLink = walkingSuffix.outputLink;
      }
    }

    this._loadNodeChildrenIntoQueue(walkingNode, que);
  }
};

AhoCorasickTrie.prototype._loadNodeChildrenIntoQueue = function (node, queue) {
  const nodeChildren = node.getAllChildren();
  for (let child of nodeChildren) {
    queue.push(child);
  }
};

AhoCorasickTrie.prototype.display = function () {
  AhoCorasickNode.recursivePrint(this.head);
};

AhoCorasickTrie.prototype.build = function () {
  this._buildSuffixLinks();
  this._buildOutputLinks();
  this.built = true;
};

AhoCorasickTrie.prototype.search = function (searchString) {
  if (this.built == false) {
    this.build();
  }

  let walkingNode = this.head;
  let outputs = [];

  for (let i = 0; i < searchString.length; i++) {
    const letter = searchString[i];
    let walkingChild = walkingNode.getChildOfLetter(letter);

    while (walkingChild == null && walkingNode != this.head) {
      walkingNode = walkingNode.suffixLink;
      walkingChild = walkingNode.getChildOfLetter(letter);
    }

    if (walkingChild) {
      if (walkingChild.word) {
        outputs.push([i, walkingChild.word]);
      }

      let walkingOutputLink = walkingChild.outputLink;
      while (walkingOutputLink != null) {
        outputs.push([i, walkingOutputLink.word]);
        walkingOutputLink = walkingOutputLink.outputLink;
      }

      walkingNode = walkingChild;
    }

  }

  return outputs;
};

module.exports = AhoCorasickTrie;
