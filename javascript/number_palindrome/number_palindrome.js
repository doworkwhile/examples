const max_n = Math.pow(10, 5);
const n = Math.floor(Math.random() * max_n);

const max_log = Math.floor(Math.log10(n));
const odd_log = max_log % 2 == 0;
const half_max_log = Math.floor(max_log / 2);

const range_low_min = 0;
const range_low_max = odd_log ? half_max_log - 1 : half_max_log;
const range_high_min = half_max_log + 1;
const range_high_max = max_log;

function get_indices_by_range (n, low, high) {
  const result = [];
  for (let i = low; i <= high; i++) {
    let imod = Math.pow(10, i + 1);
    let idiv = Math.pow(10, i);
    result.push(
      Math.floor((n % imod) / idiv)
    );
  }
  return result;
}

const digits_low = get_indices_by_range(n, range_low_min, range_low_max);
const digits_high = get_indices_by_range(n, range_high_min, range_high_max);
digits_high.reverse();

console.log(n);
console.log(digits_low, digits_high);
console.log(digits_low.toString() == digits_high.toString());
