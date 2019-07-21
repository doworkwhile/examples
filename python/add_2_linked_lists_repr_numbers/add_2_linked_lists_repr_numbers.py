import random
import math

class LinkedNode:
  def __init__(self, value):
    self.value = value
    self.next = None

### setup: generate 2 linked lists of random numbers

# first generate 2 random numbers
max_n = 10**3
num1 = random.randrange(max_n)
num2 = random.randrange(max_n)
print num1, num2

# this function transforms a number into a LinkedList and returns the head
def num_to_ll(n):
  # get the number of digits in n
  num_digits = int(math.floor(math.log10(n)) + 1)

  # store the head for the return value
  head = None
  # and the tail for appending new nodes
  tail = None

  # walk the number places (ones, tens, etc.) and build a linked list
  for i in xrange(num_digits):
    # this is the formula for the number place
    imod = 10**(i + 1)
    idiv = 10**i
    place_num = (n % imod) / idiv

    # build a new node with the value
    newNode = LinkedNode(place_num)

    # either set the head or append to the tail
    if not head:
      head = newNode
    else:
      tail.next = newNode
    # the new tail is the new node
    tail = newNode

  # return the head
  return head

# then transform them into linked lists, storing the heads
ll1 = num_to_ll(num1)
ll2 = num_to_ll(num2)

### setup done

### algorithm: add the digits of the linked lists and return a new linked list

resultHead = LinkedNode(0)
resultTail = resultHead

# loop while both linked nodes aren't null
carry = 0
while ll1 or ll2:
  # when a linked list runs out of nodes, it's contribution to the adding
  # will be 0
  ll1Contrib = 0
  ll2Contrib = 0

  # check if we have values from either linked node
  # if it has a value, advance to the next node
  if ll1:
    ll1Contrib = ll1.value
    ll1 = ll1.next
  if ll2:
    ll2Contrib = ll2.value
    ll2 = ll2.next

  # calculate the new value
  # include the value of the current tail
  #   which will be set to 1 if there was a carry
  newVal = resultTail.value + ll1Contrib + ll2Contrib

  # handle a carry situation by storing a value
  # which will be added to the next node
  # and bringing this nodes new value below 10
  if newVal > 9:
    carry = 1
    newVal -= 10
  else:
    carry = 0

  # set the new value
  resultTail.value = newVal

  # create a new node when:
  #   a carry situation was indicated
  #   or there are more nodes to add
  # otherwise break from the loop
  if carry is 1 or ll1 or ll2:
    newNode = LinkedNode(carry)
    resultTail.next = newNode
    resultTail = newNode
  else:
    break


# finally walk the list and print the result
# also store the digits in array as a string
#   to be joined and print the result as a number
resultWalk = resultHead
resultDigits = []
while resultWalk:
  print resultWalk.value,
  resultDigits.append(str(resultWalk.value))
  resultWalk = resultWalk.next
print
print num1, '+', num2, '=', ''.join(reversed(resultDigits))



