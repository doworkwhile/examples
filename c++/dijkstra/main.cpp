#include "undirected_graph.cpp"
#include "priority_queue.cpp"
#include "dijkstra_result.cpp"
#include "dijkstra_record.cpp"
#include <ctime>
#include <iostream>

void dijkstraQueueIteration
(PriorityQueue* queue, UndirectedGraph* ug, DijkstraRecord* dr)
{
  // repeat as long as we have nodes in the queue
  while (queue->currentSize != 0) {
    // get the next queue node
    NullablePriorityQueueElement pqElem = queue->poll();
    int current = pqElem.key;
    int currentCost = pqElem.priority;

    // for each path from the node
    for (int i = 0; i < ug->maxPaths; i++) {
      // skip uninitialized paths
      if (ug->validPath(current, i)) {
        int nextPath = ug->paths[current][i];
        int nextCost = currentCost + ug->costs[current][i];

        // if the cost from this node is larger than the cost from another
        if (dr->isCurrentCostLarger(nextPath, nextCost)) {
          dr->setCost(nextPath, nextCost);
          dr->setPrev(nextPath, current);
        }

        // if we haven't visited the path, add it to the queue
        if (dr->isUnvisited(nextPath)) {
          queue->add(nextPath, dr->getCost(nextPath));
          dr->visit(nextPath);
        }
      }
    }
  }
}

void buildDijkstraResult
(DijkstraResult* result, DijkstraRecord* record, int start, int end)
{
  /* first calculate the length of the path to allocate the
   * correct amount of space for the final path array.
   * starting from the end node, check the record for a 'previous' node.
   * if there was a previous node, increment the length counter and
   * do the check again with the 'previous' node.
   *
   * because this counts the connections of the path, we need to start
   * the path length at 1 because there is always 1 more node than
   * connections in the path.
  */
  int finalPathLen = 1;
  int currentInPath = end;
  while (record->hasPrev(currentInPath)) {
    currentInPath = record->getPrev(currentInPath);
    finalPathLen++;
  }

  /* now that we know the size of the array, we can trace the path again
   * appending the node indexes to the final path
  */
  int* finalPath = (int*) calloc(finalPathLen, sizeof(int));
  int pathIndex = 0;
  currentInPath = end;
  while(record->hasPrev(currentInPath)) {
    finalPath[pathIndex++] = currentInPath;
    currentInPath = record->getPrev(currentInPath);
  }
  // append the start index to the end of the final path array
  finalPath[pathIndex] = start;

  // reverse the path from end->start to start->end
  for (int i = 0; i < finalPathLen / 2; i++) {
    int temp = finalPath[i];
    finalPath[i] = finalPath[finalPathLen - i - 1];
    finalPath[finalPathLen - i - 1] = temp;
  }

  // finally, set all the result fields
  result->path = finalPath;
  result->pathLen = finalPathLen;
  result->pathCost = record->getCost(end);
}

DijkstraResult dijkstra(UndirectedGraph* graph, int start, int end)
{
  PriorityQueue queue = PriorityQueue(graph->nodes);
  DijkstraRecord record = DijkstraRecord(graph->nodes);

  // set the cost of the start to 0
  int defaultStartValue = 0;
  record.setCost(start, defaultStartValue);
  record.visit(start);

  // only add the first node to the queue when start != end
  // this will short-circuit the algorithm
  if (start != end) {
    queue.add(start, defaultStartValue);
  }

  // build the record, using the queue and graph
  dijkstraQueueIteration(&queue, graph, &record);

  // create a default result
  DijkstraResult result = DijkstraResult();

  // if the end was not reached it won't have a cost set
  if (record.hasNoCost(end)) {
    std::cout << "no route to end!" << std::endl;
    return result;
  }

  // build the result from the record
  buildDijkstraResult(&result, &record, start, end);

  return result;
}

void printGraph(UndirectedGraph* ug)
{
  for (int i = 0; i < ug->nodes; i++) {
    std::cout << "node " << i << "[";
    for (int j = 0; j < ug->maxPaths; j++) {
      if (ug->validPath(i, j)) {
        std::cout << "(->" << ug->paths[i][j] << ", $"
          << ug->costs[i][j] << ")";
      }
    }
    std::cout << "]" << std::endl;
  }
}

void printResult(DijkstraResult* result)
{
  if (result->pathLen > 0) {
    std::cout << "route = [ ";
    for (int i = 0; i < result->pathLen; i++) {
      std::cout << result->path[i] << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "cost = " << result->pathCost << std::endl;
  }
}

int main()
{
  srand(time(NULL));

  // create and print the graph
  int nodes = 20;
  int minPaths = 5;
  int maxPaths = 10;
  int minCost = 1;
  int maxCost = 9;
  UndirectedGraph ug = UndirectedGraph(
    nodes, minPaths, maxPaths, minCost, maxCost);
  printGraph(&ug);

  // run dijkstra and print the result
  std::cout << "route 0 to 1" << std::endl;
  DijkstraResult result = dijkstra(&ug, 0, 1);
  printResult(&result);
  // if (result.path) {
  //   free(path);
  // }
}
