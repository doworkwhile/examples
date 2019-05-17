#include <iostream>
#include <stdlib.h>

using namespace std;

class Leaf
{
public:
  Leaf(int);
  int value;
  Leaf* smallChild;
  Leaf* bigChild;
};

Leaf::Leaf(int v)
{
  this->value = v;
  this->smallChild = NULL;
  this->bigChild = NULL;
}

class BinaryTree
{
public:
  BinaryTree() : root(NULL) {};
  ~BinaryTree();
  Leaf* root;
  void addLeaf(Leaf*);
  void print();
private:
  void freeLeaf(Leaf*);
  void addFromLeaf(Leaf*, Leaf*);
  void printFromLeaf(Leaf*, int);
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

  return 0;
}