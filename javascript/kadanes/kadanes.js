function kadanes (ary) {
  let maxSub = 0;
  let maxTotal = 0;
  let itemsSub = [];
  let itemsMax = [];

  ary.forEach(e => {
    maxSub = Math.max(0, maxSub + e);

    let didGoHigher = maxSub > maxTotal;
    let didZeroSub = maxSub == 0;

    maxTotal = Math.max(maxTotal, maxSub);

    let didSyncMax = maxTotal != 0 && maxTotal == maxSub;
    let didNotSyncAndNotZero = !didSyncMax && !didZeroSub;

    if (didZeroSub) {
      itemsSub = [];
    }
    if (didSyncMax || didNotSyncAndNotZero) {
      itemsSub.push(e);
    }
    if (didSyncMax && didGoHigher) {
      itemsMax = itemsSub.slice(0);
    }
  });

  return [itemsMax, maxTotal];
}

function knuthShuffle (ary) {
  for (let i = ary.length - 1; i > 0; i--) {
    let swap = Math.floor(Math.random() * i);
    let temp = ary[swap];
    ary[swap] = ary[i];
    ary[i] = temp;
  }
}

const ary = [-3, -2, -1, 0, 1, 2, 3, 4, 5];
knuthShuffle(ary);
console.log(ary);
console.log(kadanes(ary));