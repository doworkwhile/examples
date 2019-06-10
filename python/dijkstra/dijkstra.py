import random
from undirected_graph import UndirectedGraph

# the Dijkstra algorithm keeps one of these per node
class VertexRecord:
  def __init__(self, index):
    self.index = index
    self.known = False
    self.cost = float("Inf")
    self.prev = -1

# find the path from start to end through an undirected graph
# without using a priority queue, we have to visit every vertex record
# to find the next minimum cost
def dijkstra(graph, start, end):
  vertexes = [VertexRecord(i) for i in xrange(graph.nodeCount)]

  current = start
  vertexes[current].cost = 0

  # iterate until we visit the end index
  while current != end:
    # gather cheapest unvisited, assign index value to current
    # if all unvisted are 'inf', this grabs the first
    cheapestVertex = [vertex for vertex in vertexes if not vertex.known]
    cheapestVertex = min(cheapestVertex, key=lambda x: x.cost)
    current = cheapestVertex.index

    # set visited
    cheapestVertex.known = True

    # if cost is 'inf', we have no more reachable nodes
    if cheapestVertex.cost == float("inf"):
      current = end
      break

    # for each neighbor
    for pathAndCost in graph.nodeIter(cheapestVertex.index):
      neighbor = pathAndCost[0]
      neighborCost = pathAndCost[1]
      neighborVertex = vertexes[neighbor]

      # if the last recorded vertex cost is less than the cost
      # from our neighbor, change the vertext cost
      newCost = cheapestVertex.cost + neighborCost
      if not neighborVertex.known and neighborVertex.cost > newCost:
        neighborVertex.cost = newCost
        neighborVertex.prev = current

  # current is end
  # is the final node unreachable
  if vertexes[current].cost == float("Inf"):
    return None

  # walk back from current, using vertex.prev, building the list
  finalPath = []
  while vertexes[current].cost != 0:
    finalPath.append(vertexes[current].index)
    current = vertexes[current].prev
  finalPath.append(current)

  # return the list and the final cost
  return (list(reversed(finalPath)), vertexes[finalPath[0]].cost)




ug = UndirectedGraph(10)

startEndOptions = range(ug.nodeCount)
start = startEndOptions.pop(random.randint(0, len(startEndOptions) - 1))
end = startEndOptions.pop(random.randint(0, len(startEndOptions) - 1))

print 'paths', ug.paths
print 'costs', ug.costs
print 'path from', start, 'to', end
print dijkstra(ug, start, end)