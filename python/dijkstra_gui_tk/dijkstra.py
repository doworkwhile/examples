import random
from priority_queue import PriorityQueue

def dijkstra(graph, start, end):
  queue = PriorityQueue()
  visited = {}
  costs = {}
  prev = {}

  costs[start] = 0
  queue.add(start, costs[start])
  visitCount = 0

  while not queue.isEmpty():
    current = queue.poll()
    visited[current] = True

    neighbors = graph.neighborsOf(current)

    for neighbor in neighbors:
      neighborCost = neighbors[neighbor]
      currentCost = costs[current] + neighborCost

      if not neighbor in costs or costs[neighbor] > currentCost:
        costs[neighbor] = currentCost
        prev[neighbor] = current

      unvisited = not neighbor in visited
      if unvisited:
        queue.add(neighbor, costs[neighbor])
        visited[neighbor] = True

  if not end in costs:
    return "None"

  finalPath = []
  current = end
  while costs[current] != 0:
    finalPath.append(current)
    current = prev[current]
  finalPath.append(start)

  return (list(reversed(finalPath)), costs[end])
