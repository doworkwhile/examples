from dijkstra import dijkstra

class Path():
  def __init__(self, player, graph):
    self.graph = graph
    self.player = player
    self.start = None
    self.end = None

  def newPath(self):
    self.start = self.player.location()
    self.end = self.graph.randomNode()
    self.path = dijkstra(self.graph, self.start, self.end)
    # discard the path cost (path[1]) and remove the starting node (path[0][0])
    self.path = self.path[0][1:]
    self.pathAt = 0

    return self.end

  def canMove(self):
    if not self.end:
      return False
    return self.pathAt < len(self.path)

  def next(self):
    ret = self.path[self.pathAt]
    self.pathAt += 1
    return ret

  def doMove(self):
    self.player.moveTo(self.next())


