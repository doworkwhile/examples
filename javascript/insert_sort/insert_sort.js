
function insertSort(ary) {
  let len = ary.length;

  for (let i = 1; i < len; i++) {
      let j = i;
      for (; j > 0 && ary[j] < ary[j-1]; j--) {
        let temp = ary[j];
        ary[j] = ary[j-1];
        ary[j-1] = temp;
      }
  }
}

let minArrayLen = 2;
let maxArrayLen = 10;
let valRange = 1000;
for (let i = minArrayLen; i <= maxArrayLen; i++) {
  let ary = new Array(i)
    .fill(true)
    .map(e => parseInt(Math.random() * valRange))
  console.log(ary);
  insertSort(ary);
  console.log(ary);
  console.log();
}

let ary = [ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
console.log(ary)
insertSort(ary)
console.log(ary)
