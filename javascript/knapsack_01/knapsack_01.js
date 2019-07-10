const shuffle = require("../knuth_shuffle/kfy_shuffle_import.js");
const cout = process.stdout;

const n_items = 9;
const w_max = 14;

const w_ary = new Array(n_items).fill(true).map((e,i) => i + 1);
const v_ary = shuffle(new Array(n_items).fill(true).map((e,i) => i + 1));

console.log("number of items", n_items);
console.log("maximum weight", w_max);
console.log("weights", w_ary);
console.log("values", v_ary);

const solutionTable = [];
const n_items_incl_zero = n_items + 1;
const w_max_incl_zero = w_max + 1;
for (let item_row = 0; item_row < n_items_incl_zero; item_row++) {
  solutionTable.push([]);

  for (let weight_col = 0; weight_col < w_max_incl_zero; weight_col++) {
    const prev_row = item_row - 1;
    if (item_row == 0 || weight_col == 0) {
      solutionTable[item_row].push(0);
    } else if (w_ary[prev_row] <= weight_col) {
      const prev_val = v_ary[prev_row];
      const prev_weight = w_ary[prev_row];
      const prev_solution = solutionTable[prev_row][weight_col - prev_weight];
      const new_val = prev_val + prev_solution;
      solutionTable[item_row][weight_col] = Math.max(
        new_val,
        solutionTable[prev_row][weight_col]
      );
    } else {
      solutionTable[item_row][weight_col] = solutionTable[prev_row][weight_col];
    }
  }
}

for (let item_row = 0; item_row < n_items_incl_zero; item_row++) {
  for (let weight_col = 0; weight_col < w_max_incl_zero; weight_col++) {
    const term = solutionTable[item_row][weight_col];
    if (term < 10) {
      cout.write("  " + term);
    } else {
      cout.write(" " + term);
    }
  }
  cout.write("\n");
}

const result = solutionTable[n_items][w_max];
console.log("max value for weight limit = ", result);

const solutionItems = [];
let item_choice = n_items;
let weight_choice = w_max;
let weight_choice_walk = result;
while (item_choice > 0) {
  const look_at = solutionTable[item_choice][weight_choice];
  const prev_look = item_choice - 1;
  const look_before = solutionTable[prev_look][weight_choice];

  if (look_at != look_before) {
    const included_val = v_ary[prev_look];

    weight_choice_walk -= included_val;
    let look_back = look_before;
    while (weight_choice_walk != look_back) {
      weight_choice -= 1;
      look_back = solutionTable[prev_look][weight_choice];
    }

    solutionItems.push({
      weight: item_choice,
      value: v_ary[item_choice - 1] // back by 1 for 0-index
    });
  }

  item_choice = prev_look;
}

console.log("solution items:", solutionItems);
