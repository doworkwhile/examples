require './priority_queue.rb'

def dijkstra(graph, first, last)
  queue = PriorityQueue.new
  visited = {}
  costs = {}
  prev = {}

  costs[first] = 0
  queue.add(first, costs[first])

  while !queue.empty?
    current = queue.poll.item
    visited[current] = true

    neighbors = graph.get_paths(current)
    neighbors.each do |to, cost|
      next_cost = costs[current] + cost

      no_cost_yet = !costs.has_key?(to)
      if no_cost_yet || costs[to] > next_cost
        costs[to] = next_cost
        prev[to] = current
      end

      unvisited = !visited.has_key?(to)
      if unvisited
        queue.add(to, costs[to])
        visited[to] = true
      end
    end
  end

  return nil unless costs.has_key?(last)

  final_path = []
  current = last
  while costs[current] != 0
    final_path << current
    current = prev[current]
  end
  final_path << first

  [final_path.reverse, costs[last]]
end
