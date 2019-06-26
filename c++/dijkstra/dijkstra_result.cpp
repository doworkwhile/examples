#include <cstdlib>

class DijkstraResult
{
public:
  int* path;
  int pathLen;
  int pathCost;

  // constructors
  DijkstraResult() {
    this->path = NULL;
    this->pathLen = 0;
    this->pathCost = 0;
  };
  DijkstraResult(int* path, int pathLen, int pathCost) :
    path(path), pathLen(pathLen), pathCost(pathCost) {};

  // destructor
  ~DijkstraResult() {
    if (path) {
      free(path);
    }
  };

  void addToPath(int n)
  {
    this->path[this->pathLen++] = n;
  }
};
