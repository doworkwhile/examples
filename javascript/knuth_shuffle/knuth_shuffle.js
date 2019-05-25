var aryLen = 10;
var ary = new Array(10).fill(true).map((e,i) => i);
console.log(ary);

function knuthShuffle(ary) {
  for (var i = ary.length - 1; i > 0; i--) {
    var swap = Math.floor(Math.random() * i);
    var temp = ary[swap];
    ary[swap] = ary[i];
    ary[i] = temp;
  }
}

knuthShuffle(ary);
console.log(ary);