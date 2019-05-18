#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class Leaf
{
public:
  Leaf(int v) : value(v), smallChild(NULL), bigChild(NULL) {};
  int value;
  Leaf* smallChild;
  Leaf* bigChild;
};

class BinaryTree
{
public:
  BinaryTree() : root(NULL) {};
  ~BinaryTree();
  Leaf* root;
  void addLeaf(Leaf*);
  void print();
  Leaf* findLeaf(int);
  int findDepth(int);
  vector<int> toSortedVector();
  int getLeafMaxDepth(const Leaf* current);
  int getMaxDepth();
  void getLeafsAtDepth(vector<Leaf*>*, int);
  void DSW();
private:
  void freeLeaf(Leaf*);
  void addFromLeaf(Leaf*, Leaf*);
  void printFromLeaf(Leaf*, int);
  void collectFromLeaf(vector<int>*, Leaf*);
  int getLeafHasChild(const Leaf*);
  void collectDepthFromLeaf(vector<int>*, const Leaf*, const int);
  void collectLeafAtDepth(vector<Leaf*>*, Leaf*, int, int);
  void createVine();
  Leaf* rotateRightIntoVine(Leaf*, Leaf*, Leaf*);
  void rebuildTreeFromVine();
  void rotateRebuildTree(int);
  void rotateLeftIntoTree(Leaf*, Leaf*, Leaf*);
};

BinaryTree::~BinaryTree()
{
  if (root) {
    freeLeaf(root);
  }
}

void BinaryTree::freeLeaf(Leaf* l)
{
  if (l->smallChild) {
    freeLeaf(l->smallChild);
  }

  if (l->bigChild) {
    freeLeaf(l->bigChild);
  }

  delete l;
}

void BinaryTree::addLeaf(Leaf* add)
{
  if (!root) {
    root = add;
    return;
  }

  addFromLeaf(root, add);
}

void BinaryTree::addFromLeaf(Leaf* current, Leaf* add)
{
  if (add->value >= current->value) // add is larger
  {
    if (current->bigChild) {
      addFromLeaf(current->bigChild, add);
    } else {
      current->bigChild = add;
    }
  } else { // add is smaller
    if (current->smallChild) {
      addFromLeaf(current->smallChild, add);
    } else {
      current->smallChild = add;
    }
  }
}

void BinaryTree::print()
{
  if (!root) {
    cout << "empty tree!" << endl;
    return;
  }

  printFromLeaf(root, 0);
}

void BinaryTree::printFromLeaf(Leaf* current, int depth)
{
  if (current->bigChild) {
    printFromLeaf(current->bigChild, depth + 1);
  }

  for (int i = 0; i < depth; i++) {
    cout << "-----|";
  }
  cout << "(";
  if (current->value < 10) {
    cout << "  ";
  } else if (current->value < 100) {
    cout << " ";
  }
  cout << current->value << ")" << endl;

  if (current->smallChild) {
    printFromLeaf(current->smallChild, depth + 1);
  }
}

Leaf* BinaryTree::findLeaf(int v) {
  if (!root) {
    return NULL;
  }

  Leaf* search = root;
  while (search->value != v) {
    if (search->value > v) { // leaf to search should be smaller
      search = search->smallChild;
    } else { // else the leaf should be bigger
      search = search->bigChild;
    }

    // out of nodes?
    if (!search) {
      return NULL;
    }
  }
  return search;
}

int BinaryTree::findDepth(int v) {
  if (!root) {
    return -1;
  }

  Leaf* search = root;
  int depth = 0;
  while (search->value != v) {
    if (search->value > v) { // leaf to search should be smaller
      search = search->smallChild;
    } else { // else the leaf should be bigger
      search = search->bigChild;
    }
    ++depth;

    // out of nodes?
    if (!search) {
      return --depth;
    }
  }
  return depth;
}

vector<int> BinaryTree::toSortedVector() {
  vector<int> collection;
  if (!root) {
    return collection;
  }

  collectFromLeaf(&collection, root);
  return collection;
}

void BinaryTree::collectFromLeaf(vector<int>* v, Leaf* current)
{
  if (current->smallChild) {
    collectFromLeaf(v, current->smallChild);
  }

  v->push_back(current->value);

  if (current->bigChild) {
    collectFromLeaf(v, current->bigChild);
  }
}

int BinaryTree::getLeafHasChild(const Leaf* current)
{
  return !!current->smallChild || current->bigChild;
}

void BinaryTree::collectDepthFromLeaf(
  vector<int>* v,
  const Leaf* current,
  const int depth)
{
  if (current->smallChild) {
    collectDepthFromLeaf(v, current->smallChild, depth + 1);
  }
  v->push_back(depth);
  if (current->bigChild) {
    collectDepthFromLeaf(v, current->bigChild, depth + 1);
  }
}

int BinaryTree::getLeafMaxDepth(const Leaf* current)
{
  int hasChild = getLeafHasChild(current);
  if (!hasChild) {
    return 0;
  }

  vector<int> max;
  collectDepthFromLeaf(&max, current, 0);
  int bigMax = 0;
  for (int i = 0 ; i < max.size(); i++) {
    if (max[i] > bigMax) {
      bigMax = max[i];
    }
  }
  return bigMax;
}

void BinaryTree::collectLeafAtDepth(
  vector<Leaf*>* collection,
  Leaf* checking,
  int current,
  int search)
{
  if (checking->smallChild) {
    collectLeafAtDepth(collection, checking->smallChild, current + 1, search);
  }
  if (current == search) {
    collection->push_back(checking);
  }
  if (checking->bigChild) {
    collectLeafAtDepth(collection, checking->bigChild, current + 1, search);
  }
}

void BinaryTree::getLeafsAtDepth(
  vector<Leaf*>* collection,
  int depth)
{
  if (!root) {
    return;
  }

  collectLeafAtDepth(collection, root, 0, depth);
}

int BinaryTree::getMaxDepth()
{
  if (!root) {
    return 0;
  }

  return getLeafMaxDepth(root);
}

void BinaryTree::DSW()
{
  if (!root) {
    return;
  }

  createVine();
  rebuildTreeFromVine();
}

void BinaryTree::createVine()
{
  Leaf* grandParent = NULL;
  Leaf* parent = root;
  Leaf* smallChild = NULL;

  // starting at root
  // if there is a root smallChild
  // -> attach smallChild to grandparent's bigChild
  // -> set root to the smallChild
  // else
  // -> move to the right
  // -> don't set root
  while (parent) {
    smallChild = parent->smallChild;
    if (smallChild) {
      grandParent = rotateRightIntoVine(grandParent, parent, smallChild);
      parent = smallChild;
    } else {
      grandParent = parent; // move down
      parent = parent->bigChild;
    }
  }
}

Leaf* BinaryTree::rotateRightIntoVine(Leaf* grandParent, Leaf* parent, Leaf* smallChild)
{
  if (grandParent) {
    grandParent->bigChild = smallChild;
  } else {
    root = smallChild;
  }
  parent->smallChild = smallChild->bigChild;
  smallChild->bigChild = parent;
  return grandParent;
}

void BinaryTree::rebuildTreeFromVine()
{
  // length of vine
  int leafCount = 0;
  for (Leaf* temp = root; !!temp; temp = temp->bigChild) {
    leafCount++;
  }

  // MSB of length of vine+1
  int leafCountShifts = leafCount + 1;
  int leafCountMSB = 0;
  while (1 < leafCountShifts) {
    leafCountShifts = (leafCountShifts >> 1);
    leafCountMSB++;
  }
  int doRotations = (1 << leafCountMSB) - 1;
  // rotate left for every node to have a small child
  rotateRebuildTree(leafCount - doRotations);

  // keep rotating every other until balanced
  while(doRotations > 1) {
    doRotations /= 2;
    rotateRebuildTree(doRotations);
  }
}

void BinaryTree::rotateRebuildTree(int max)
{
  Leaf* grandParent = NULL;
  Leaf* parent = root;
  Leaf* bigChild = root->bigChild;
  for (; max > 0; max--) {
    if (bigChild) {
      rotateLeftIntoTree(grandParent, parent, bigChild);
      grandParent = bigChild;
      parent = grandParent->bigChild;
      if (parent) {
        bigChild = parent->bigChild;
      } else {
        bigChild = NULL;
      }
    } else {
      break;
    }
  }
}

void BinaryTree::rotateLeftIntoTree(Leaf* grandParent, Leaf* parent, Leaf* bigChild)
{
  if (grandParent) {
    grandParent->bigChild = bigChild;
  } else {
    root = bigChild;
  }
  parent->bigChild = bigChild->smallChild;
  bigChild->smallChild = parent;
}

int main()
{
  srand(time(NULL));

  BinaryTree b = BinaryTree();

  int leafLen = 30;
  int randRange = 1000;
  Leaf* ary[leafLen];

  for (int i = 0; i < leafLen; i++) {
    int randNum = rand() % randRange;
    ary[i] = new Leaf(randNum);
    b.addLeaf(ary[i]);
  }
  b.print();

  int randFindIndex = rand() % leafLen;
  int valToFind = ary[randFindIndex]->value;
  cout << "Depth of " << valToFind << ": ";
  int found = b.findDepth(valToFind);
  cout << found << endl;

  cout << "Elements in order:" << endl;
  vector<int> collection = b.toSortedVector();
  for (int i = 0; i < collection.size(); i++) {
    cout << collection[i] << " ";
  }
  cout << endl;

  int maxDepth = b.getMaxDepth();
  cout << "Max Depth: " << maxDepth << endl;
  int checkDepth = rand() % maxDepth;
  vector<Leaf*> leafsAtDepth;
  b.getLeafsAtDepth(&leafsAtDepth, checkDepth);
  cout << "Leaves at random index " << checkDepth;
  cout << ": [";
  for (int i = 0; i < leafsAtDepth.size(); i++) {
    cout << leafsAtDepth[i]->value << " ";
  }
  cout << "]";
  cout << endl;
  cout << "balancing with DSW" << endl;
  b.DSW();
  cout << "balanced" << endl;
  b.print();
  maxDepth = b.getMaxDepth();
  cout << "Max Depth: " << maxDepth << endl;
  return 0;
}