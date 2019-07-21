const LinkedNode = function (value) {
  this.value = value;
  this.next = null;
};

// create 2 random numbers
const numMax = Math.pow(10, 5);
const num1 = Math.floor(Math.random() * numMax);
const num2 = Math.floor(Math.random() * numMax);
console.log(num1, num2);

// transform the 2 numbers into a linked list
function numToLL (n) {
  const nDigitPlaces = Math.floor(Math.log10(n)) + 1;

  let head = null;
  let tail = null;
  for (let i = 0; i < nDigitPlaces; i++) {
    const imod = Math.pow(10, i + 1);
    const idiv = Math.pow(10, i);
    const placeNum = Math.floor((n % imod) / idiv);

    const newNode = new LinkedNode(placeNum);

    if (!head) {
      head = newNode;
    } else {
      tail.next = newNode;
    }
    tail = newNode;
  }

  return head;
}
const ll1 = numToLL(num1);
const ll2 = numToLL(num2);

// add the items of the 2 linked lists into a new linked list
let resultHead = new LinkedNode(0);
let resultTail = resultHead;
let ll1Walk = ll1;
let ll2Walk = ll2;
let carry = 0;
while (ll1Walk || ll2Walk) {
  // determine contributions from items left
  let ll1Contrib = 0;
  let ll2Contrib = 0;
  if (ll1Walk) {
    ll1Contrib += ll1Walk.value;
    ll1Walk = ll1Walk.next;
  }
  if (ll2Walk) {
    ll2Contrib += ll2Walk.value;
    ll2Walk = ll2Walk.next;
  }

  // calculate new value and set carry flag
  let newVal = resultTail.value + ll1Contrib + ll2Contrib;
  if (newVal > 9) {
    carry = 1;
    newVal -= 10;
  } else {
    carry = 0;
  }
  resultTail.value = newVal;

  // add a next node if carry flag is set or more items from either list
  if (carry == 1 || ll1Walk || ll2Walk) {
    const newNode = new LinkedNode(carry);
    resultTail.next = newNode;
    resultTail = newNode;
  } else {
    break;
  }
}

let resultWalk = resultHead;
let resultDigits = [];
while (resultWalk) {
  resultDigits.push(resultWalk.value);
  resultWalk = resultWalk.next;
}
resultDigits.reverse();
console.log(Number(resultDigits.join('')));
