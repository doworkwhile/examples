import random

"""
An UndirectedGraph has bi-directional traversal paths between nodes.
"""
class UndirectedGraph:
  def __init__(self):
    self.paths = {}

  def addPath(self, fromNode, toNode, cost):
    if not fromNode in self.paths:
      self.paths[fromNode] = {}
    self.paths[fromNode][toNode] = cost

  def neighborsOf(self, node):
    if not node in self.paths:
      return {}
    return self.paths[node]

  def randomNode(self):
    return random.choice(list(self.paths))

