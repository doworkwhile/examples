#include <iostream>
#include <vector>

using namespace std;

/* even though we can only take from the top
 * don't use std::stack because we can't peek to print
*/
vector<int> stackA;
vector<int> stackB;
vector<int> stackC;

void printTower(char name, vector<int>* v)
{
  cout << name << ": ";
  if (v->size() == 0) {
    cout << endl;
    return;
  }

  int i = 0;
  for (; i < v->size() - 1; i++) {
    cout << v->at(i) << " ";
  }
  cout << v->at(v->size() - 1);
  cout << endl;
}

void printTowers()
{
  cout << endl;
  printTower('A', &stackA);
  printTower('B', &stackB);
  printTower('C', &stackC);
}

void solveTower(
  int toMove,
  vector<int>* src,
  vector<int>* inter,
  vector<int>* dest)
{
  if (toMove == 1) {
    src->pop_back();
    dest->push_back(toMove);
  } else {
    solveTower(toMove - 1, src, dest, inter);
    src->pop_back();
    dest->push_back(toMove);
    solveTower(toMove - 1, inter, src, dest);
    return;
  }
}

int main()
{

  int largestRing = 5;
  for (int i = largestRing; i > 0; i--) {
    stackA.push_back(i);
  }

  cout << "Elements to move: " << stackA.size() << endl;
  printTowers();
  solveTower(stackA.front(), &stackA, &stackB, &stackC);
  printTowers();

  return 0;
}