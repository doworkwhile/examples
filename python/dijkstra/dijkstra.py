import random


"""
An UndirectedGraph has bi-directional traversal paths between nodes.
Arguments:
  nodes = the number of nodes in the graph
    must be > 2
  minPaths = the lower bound of the random range of possible paths per node
    must be > maxPaths
  maxPaths = the upper bound of the random range of possible paths per node
  minCost = the lower bound of the random range of costs per path
    must be > maxCost
  maxCost = the upper bound of the random range of costs per path
"""
class UndirectedGraph:
  def __init__(self, nodes=10, minPaths=0, maxPaths=3, minCost=1, maxCost=20):
    if nodes < 2:
      raise ValueError("there must be at least 2 node")
    if minPaths > maxPaths:
      raise ValueError("minPaths must be < maxPaths")
    if minCost > maxCost:
      raise ValueError("minCost must be < maxCost")
    self.nodeCount = nodes
    self.minPaths = minPaths
    self.maxPaths = maxPaths
    self.minCost = minCost
    self.maxCost = maxCost
    self.paths = [[] for i in xrange(self.nodeCount)]
    self.costs = [[] for i in xrange(self.nodeCount)]

    self.constructRandom()

  def constructRandom(self):
    for i in xrange(self.nodeCount):
      # add 0->maxPaths paths & costs
      pathOptions = range(self.nodeCount)
      pathOptions.remove(i)
      pathCount = random.randint(self.minPaths, self.maxPaths)
      pathCount = min(pathCount, self.nodeCount - 1)
      for j in xrange(pathCount):
        popPathOptionIndex = 0
        if len(pathOptions) > 1:
          popPathOptionIndex = random.randint(0, len(pathOptions) - 1)
        pathTo = pathOptions.pop(popPathOptionIndex)
        if not pathTo in self.paths[i]:
          self.paths[i].append(pathTo)
          self.paths[pathTo].append(i)
          pathCost = self.randomPathCost()
          self.costs[i].append(pathCost)
          self.costs[pathTo].append(pathCost)

  def randomPathCost(self):
    return random.randint(self.minCost, self.maxCost)

  # for the node at index i
  # yield as a tuple each path and cost
  # like (path, cost)
  def nodeIter(self, i):
    indexPaths = self.paths[i]
    indexCosts = self.costs[i]
    for j in xrange(len(indexPaths)):
      yield (indexPaths[j], indexCosts[j])



# the Dijkstra algorithm keeps one of these per node
class VertexRecord:
  def __init__(self, index):
    self.index = index
    self.known = False
    self.cost = float("Inf")
    self.prev = -1

# find the path from start to end through an undirected graph
def dijksta(graph, start, end):
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
    else:
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
print dijksta(ug, start, end)