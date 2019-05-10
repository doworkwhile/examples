function bubbleSort(ary) {
  for (let i = ary.length - 1; i > 0; i--) {
    for (let j = 0; j < i; j++) {
      if (ary[j] > ary[j+1]) {
        ary[j] += ary[j+1];
        ary[j+1] = ary[j] - ary[j+1];
        ary[j] -= ary[j+1];
      }
    }
  }
}

let aryMin = 2;
let aryMax = 2;
let valRange = 1000;

for (let i = aryMin; i <= aryMax; i++) {
  let ary = new Array(i)
    .fill(true)
    .map(e => parseInt(Math.random() * valRange));
  console.log(ary);
  bubbleSort(ary);
  console.log(ary);
  console.log();
}

let ary = [ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 ];
console.log(ary);
bubbleSort(ary);
console.log(ary);