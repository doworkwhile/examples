
var randMin = 10;
var randMax = 100;
var pivot = (randMin + randMax) / 2;
var aryLen = 10;
var ary = new Array(aryLen)
  .fill(true)
  .map(e => (randMin + parseInt(Math.random() * (randMax - randMin))));
console.log(ary);

function partition(ary, pivot) {
  var left = -1;
  var right = ary.length;

  while (left < right) {
    while (left < right && ary[++left] < pivot);
    while (right > left && ary[--right] > pivot);

    var temp = ary[left];
    ary[left] = ary[right];
    ary[right] = temp;
  }

  return left;
}

console.log('pivot on', pivot);
var partAt = partition(ary, pivot);
console.log('part at', partAt);
console.log(ary);
