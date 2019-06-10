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

