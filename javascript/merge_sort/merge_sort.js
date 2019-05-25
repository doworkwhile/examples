var randMin = 0;
var randMax = 10;
var aryLen = 10;
var ary = new Array(aryLen)
  .fill(true)
  .map((e,i) => aryLen - i - 1); // backwards array
console.log(ary);

function mergeSort(ary) {
  var copy = new Array(ary.length);
  mergeSortRecurse(ary, copy, 0, ary.length);
}

function mergeSortRecurse(ary, copy, left, right) {
  var size = Math.floor(right - left); // MUST BE FLOORED
  if (size == 1) {
    return;
  }

  var mid = Math.floor((left + right) / 2); // MUST BE FLOORED
  if (size > 2) {
    mergeSortRecurse(ary, copy, left, mid);
    mergeSortRecurse(ary, copy, mid, right);
  }

  var lbegin = left;
  var rbegin = mid;
  var i = 0;
  while (lbegin < mid && rbegin < right) {
    if (ary[lbegin] < ary[rbegin]) {
      copy[left + i] = ary[lbegin];
      lbegin++;
    } else {
      copy[left + i] = ary[rbegin];
      rbegin++;
    }
    i++;
  }
  while (lbegin < mid) {
    copy[left + i] = ary[lbegin];
    lbegin++;
    i++;
  }
  while (rbegin < right) {
    copy[left + i] = ary[rbegin];
    rbegin++;
    i++;
  }

  for (i = 0; i < size; i++) {
    ary[left + i] = copy[left + i];
  }
}

mergeSort(ary);
console.log(ary);