function swap(ary, i, j) {
  // the algorithm breaks if the indexes are the same
  // if you subtract the value at an index from itself, you get 0
  if (i == j) {
    return;
  }
  ary[i] += ary[j]
  ary[j] = ary[i] - ary[j]
  ary[i] -= ary[j]
}

function randRange(randMin, randMax) {
  return Math.round(randMin + (Math.random() * (randMax - randMin)));
}

// range [left, right]
// swap random index of range to right as pivot
// scan range elements and ..
//   stack (swap) all less than pivot to left, swap pivot into top of stack
// recurse [left, pivot-1] and [pivot+1, right]
// (attempts 3 swaps per recursion)
function quickSort(ary, left, right) {
  if (left < right) {
    // choose a random index from [left, right]
    var pivotIndex = randRange(left, right);
    // it does not matter if pivotIndex == right 
    // swap pivotIndex and right
    swap(ary, pivotIndex, right);
    // store the value we moved to the right
    var pivotValue = ary[right];

    // sort all values before right
    // lrScanIndex indexes the range [left, right)
    // lastLessThanPivot is the index of the last number less than pivotValue
    // when lrScanIndex indexes in ary a number which is < pivotValue
    // we can move it to the left of the partition
    var lastLessThanPivot = left - 1;
    for (var lrScanIndex = left; lrScanIndex < right; lrScanIndex++) {
      if (ary[lrScanIndex] < pivotValue) {
        lastLessThanPivot += 1;
        swap(ary, lastLessThanPivot, lrScanIndex);
      }
    }

    // lastLessThanPivot is the last index of a number < pivotValue
    // so the pivot should be place at lastLessThanPivot + 1
    var pivot = lastLessThanPivot + 1;
    swap(ary, pivot, right);

    // the new right side of the left partition is lastLessThanPivot
    quickSort(ary, left, lastLessThanPivot);
    // the new left side of the  right partition is the pivot + 1
    quickSort(ary, pivot + 1, right);
  }
}

ary = new Array(10).fill(true).map(e => randRange(10, 100))
console.log(ary)
quickSort(ary, 0, ary.length - 1)
console.log(ary)