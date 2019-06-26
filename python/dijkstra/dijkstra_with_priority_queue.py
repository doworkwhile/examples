from priority_queue import PriorityQueue
from undirected_graph import UndirectedGraph
import random

def dijkstra(graph, start, end):
  pq = PriorityQueue()
  visited = {}
  costs = {}
  prev = {}

  costs[start] = 0
  pq.add(start, costs[start])
  visitCount = 0

  while not pq.isEmpty():
    current = pq.poll()
    visited[current] = True

    neighbors = graph.paths[current]
    neighborsCosts = graph.costs[current]

    for i in xrange(len(neighbors)):
      n = neighbors[i]
      currentCost = costs[current] + neighborsCosts[i]

      if not n in costs or costs[n] > currentCost:
        costs[n] = currentCost
        prev[n] = current

      unvisited = not n in visited
      if unvisited:
        pq.add(n, costs[n])
        visited[n] = True

  if not end in costs:
    return "None"

  finalPath = []
  current = end
  while costs[current] != 0:
    finalPath.append(current)
    current = prev[current]
  finalPath.append(start)

  return (list(reversed(finalPath)), costs[end])


ug = UndirectedGraph(10)
startEndOptions = range(ug.nodeCount)
start = startEndOptions.pop(random.randint(0, len(startEndOptions) - 1))
end = startEndOptions.pop(random.randint(0, len(startEndOptions) - 1))

print 'paths', ug.paths
print 'costs', ug.costs
print 'path from', start, 'to', end
print dijkstra(ug, start, end)
