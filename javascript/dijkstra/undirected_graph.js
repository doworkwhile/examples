function randRange (low, high) {
  return low + Math.floor((Math.random() * (high - low)));
}

function anyInRangeBut (low, high, butNot) {
  let ret = butNot[0];
  while (butNot.includes(ret)) {
    ret = randRange(low, high);
  }
  return ret;
}

const UndirectedGraph = function (nodes, minPaths, maxPaths, minCost, maxCost) {
  this.nodes = nodes;
  this.minPaths = minPaths;
  this.maxPaths = maxPaths;
  this.minCost = minCost;
  this.maxCost = maxCost;
  this.paths = [];
  this.costs = [];

  for (let i = 0; i < nodes; i++) {
    this.paths[i] = [];
    this.costs[i] = [];

    let randPathCount = randRange(minPaths, maxPaths + 1);
    for (let j = 0; j < randPathCount; j++) {
      let randPathDest = anyInRangeBut(0, nodes, [i, ...this.paths[i]]);
      let randPathCost = randRange(minCost, maxCost + 1);
      this.paths[i].push(randPathDest);
      this.costs[i].push(randPathCost);
    }
  }
};

UndirectedGraph.prototype.print = function () {
  for (let i = 0; i < this.nodes; i++) {
    process.stdout.write('path ' + i + '[ ');
    for (let j = 0; j < this.paths[i].length; j++) {
      process.stdout.write('(->' + this.paths[i][j] + ', $' + this.costs[i][j] + ') ');
    }
    console.log(']');
  }
};

module.exports = UndirectedGraph;