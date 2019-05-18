#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class BishopTuple {
public:
  BishopTuple(int nx, int ny) : x(nx), y(ny) {}
  int x;
  int y;
};

int calcNewCollisions(int n)
{
  if (n < 2) {
    return 0;
  }
  return (n*(n-1)) - ((n-1) * (n-2));
}

int main()
{
  // random numbers seed
  srand(time(NULL));

  // create bishop positions
  int rows = 10;
  int cols = 10;
  vector<BishopTuple> bishops;
  bishops.push_back(BishopTuple(4, 6));
  bishops.push_back(BishopTuple(6, 6));
  bishops.push_back(BishopTuple(5, 5));
  bishops.push_back(BishopTuple(4, 4));

  vector<int> RDiagCounts = vector<int>(rows + cols);
  vector<int> LDiagCounts = vector<int>(rows + cols);
  int collisionCount = 0;
  for (int i = 0;  i < bishops.size(); i++) {
    BishopTuple temp = bishops[i];

    // inc the # of bishops on this rdiag
    int rDiag = temp.x + temp.y;
    RDiagCounts[rDiag] += 1;
    int newCollisionCount = calcNewCollisions(RDiagCounts[rDiag]);
    collisionCount += newCollisionCount;

    // inc the # of bishops on this ldiag
    int lDiag = rows - temp.x + temp.y;
    LDiagCounts[lDiag] += 1;
    newCollisionCount = calcNewCollisions(LDiagCounts[lDiag]);
    collisionCount += newCollisionCount;
  }
  for (int i = 0 ; i < RDiagCounts.size(); i++) {
    cout << RDiagCounts[i] << " ";
  }
  cout << endl;
  for (int i = 0 ; i < LDiagCounts.size(); i++) {
    cout << LDiagCounts[i] << " ";
  }
  cout << endl;
  cout << "total collisions: " << collisionCount << endl;
  cout << endl;

  return 0;
}
