const UndirectedGraph = require('./undirected_graph.js');
const PriorityQueue = require('./priority_queue.js');

function objHasKey (obj, key) {
  return Object.keys(obj).includes("" + key);
}

function dijkstra (graph, start, end) {
  const pq = new PriorityQueue();
  const visited = {};
  const costs = {};
  const prev = {};

  costs[start] = 0;
  pq.add(start, costs[start]);

  while (!pq.isEmpty()) {
    const current = pq.poll();
    visited[current] = true;

    const neighbors = graph.paths[current];
    const neighborsCosts = graph.costs[current];

    for (let i = 0; i < neighbors.length; i++) {
      const currentNeighbor = neighbors[i];
      const currentCost = costs[current] + neighborsCosts[i];

      if (!objHasKey(costs, currentNeighbor) ||
          costs[currentNeighbor] > currentCost) {
        costs[currentNeighbor] = currentCost;
        prev[currentNeighbor] = current;
      }

      if (!objHasKey(visited, currentNeighbor)) {
        pq.add(currentNeighbor, costs[currentNeighbor]);
        visited[currentNeighbor] = true;
      }
    }

    if (objHasKey(costs, end)) {
      break;
    }
  }

  if (!objHasKey(costs, end)) {
    return;
  }

  const finalPath = [];
  let walkBack = end;
  while (costs[walkBack] != 0) {
    finalPath.push(walkBack);
    walkBack = prev[walkBack];
  }
  finalPath.push(start);
  finalPath.reverse();

  return [finalPath, costs[end]];
}


const nodes = 20;
const ug = new UndirectedGraph(nodes, 1, 3, 1, 10);
ug.print();

const randStart = Math.floor(Math.random() * nodes);
const randEnd = Math.floor(Math.random() * nodes);
console.log('find', randStart, 'to', randEnd);
console.log(dijkstra(ug, randStart, randEnd));
