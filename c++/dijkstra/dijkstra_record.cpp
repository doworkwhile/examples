#include <cstdlib>
#include <bits/stdc++.h>

class DijkstraRecord
{
public:
  DijkstraRecord(int nodes);
  ~DijkstraRecord();

  void visit(int n);
  bool isUnvisited(int n);

  void setCost(int n, int nCost);
  int getCost(int n);

  void setPrev(int n, int nPrev);
  int getPrev(int n);

  bool hasPrev(int n);
  bool hasNoCost(int n);
  int isCurrentCostLarger(int n, int newCost);
private:
  int nodes;
  int* cost;
  bool* visited;
  int* prev;
};

DijkstraRecord::DijkstraRecord(int nodes)
{
  this->nodes   = nodes;
  this->cost    = (int*)  calloc(nodes, sizeof(int));
  this->visited = (bool*) calloc(nodes, sizeof(bool));
  this->prev    = (int*)  calloc(nodes, sizeof(int));

  for (int i = 0; i < nodes; i++) {
    this->cost[i]    = INT_MAX;
    this->visited[i] = false;
    this->prev[i]    = -1;
  }
}

DijkstraRecord::~DijkstraRecord() {
  free(cost);
  free(visited);
  free(prev);
}

void DijkstraRecord::visit(int n)
{
  this->visited[n] = true;
}

bool DijkstraRecord::isUnvisited(int n)
{
  return !this->visited[n];
}

void DijkstraRecord::setCost(int n, int nCost)
{
  this->cost[n] = nCost;
}

int DijkstraRecord::getCost(int n)
{
  return this->cost[n];
}

void DijkstraRecord::setPrev(int n, int nPrev)
{
  this->prev[n] = nPrev;
}

int DijkstraRecord::getPrev(int n)
{
  return this->prev[n];
}

bool DijkstraRecord::hasPrev(int n)
{
  return this->prev[n] != -1;
}

bool DijkstraRecord::hasNoCost(int n)
{
  return this->cost[n] == INT_MAX;
}

int DijkstraRecord::isCurrentCostLarger(int n, int newCost)
{
  return this->cost[n] > newCost;
}
