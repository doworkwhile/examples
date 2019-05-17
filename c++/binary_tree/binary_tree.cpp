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
private:
  void freeLeaf(Leaf*);
  void addFromLeaf(Leaf*, Leaf*);
  void printFromLeaf(Leaf*, int);
  void collectFromLeaf(vector<int>*, Leaf*);
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
    cout << "----|";
  }
  cout << "(";
  if (current->value < 10) {
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



int main()
{
  srand(time(NULL));

  BinaryTree b = BinaryTree();

  int leafLen = 30;
  int randRange = 100;
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

  return 0;
}