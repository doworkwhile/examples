#include <cstdlib>

class UndirectedGraph {
public:
  int nodes;
  int minPaths;
  int maxPaths;
  int minCost;
  int maxCost;
  int** paths;
  int** costs;
  int connectionCount;

  UndirectedGraph(int, int, int, int, int);
  ~UndirectedGraph();

  bool validPath(int node, int pathIndex);

private:
  void freeGraph();
  void freePathAndCostElements();
  int randRange(int low, int high);
  int anyInRangeBut(int low, int high, int notNum);
  void initializeRandom();
  void InitializeZeroOneTest();
};

UndirectedGraph::UndirectedGraph(int nodes, int minPaths, int maxPaths,
  int minCost, int maxCost)
{
  this->nodes = nodes;
  this->minPaths = minPaths;
  this->maxPaths = maxPaths;
  this->minCost = minCost;
  this->maxCost = maxCost;
  this->paths = (int**) calloc(nodes, sizeof(int*));
  this->costs = (int**) calloc(nodes, sizeof(int*));
  this->connectionCount = 0;

  this->initializeRandom();
}

UndirectedGraph::~UndirectedGraph()
{
  this->freeGraph();
}

void UndirectedGraph::freePathAndCostElements()
{
  for (int i = 0; i < this->nodes; i++) {
    free(this->paths[i]);
    free(this->costs[i]);
  }
}

void UndirectedGraph::freeGraph()
{
  this->freePathAndCostElements();
  free(this->paths);
  free(this->costs);
}

int UndirectedGraph::randRange(int low, int high) {
  return low + (rand() % (high - low));
}

int UndirectedGraph::anyInRangeBut(int low, int high, int notNum) {
  int ret = notNum;
  while (ret == notNum) {
    ret = randRange(low, high);
  }
  return ret;
}

void UndirectedGraph::initializeRandom()
{
  // make sure the graph is clean before initializing
  if (this->connectionCount == 0) {
    this->freePathAndCostElements();
    this->connectionCount = 0;
  }

  // every node has from minPaths to maxPaths paths & costs
  // already created: paths/costs[i] where i is the node
  // now create: paths/costs[i][j] where j is the path/cost
  for (int i = 0; i < nodes; i++) {
    this->paths[i] = (int*) calloc(maxPaths, sizeof(int));
    this->costs[i] = (int*) calloc(maxPaths, sizeof(int));

    int randPathCount = randRange(minPaths, maxPaths + 1);
    for (int j = 0; j < randPathCount; j++) {
      int randPathDest = anyInRangeBut(0, nodes, i);
      int randPathCost = randRange(minCost, maxCost + 1);
      this->paths[i][j] = randPathDest;
      this->costs[i][j] = randPathCost;
      this->connectionCount++;
    }

    // fill the rest of the paths (random amount added may be less than max)
    // with -1
    for (int j = randPathCount; j < maxPaths; j++)
    {
      this->paths[i][j] = -1;
      this->costs[i][j] = -1;
    }

  }
}

bool UndirectedGraph::validPath(int node, int pathIndex)
{
  return this->paths[node][pathIndex] != -1;
}
