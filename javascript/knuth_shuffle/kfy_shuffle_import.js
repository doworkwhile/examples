function kfy_shuffle (ary) {
  for (let i = ary.length - 1; i > 0; i--) {
    const swap = Math.floor(Math.random() * i);
    const temp = ary[swap];
    ary[swap] = ary[i];
    ary[i] = temp;
  }
  return ary;
}

module.exports = kfy_shuffle;
