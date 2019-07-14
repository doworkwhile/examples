# algorithm description
# given 2 linked lists of digits which represent 2 numbers with the digits
# linked in place order, add the 2 numbers into a new linked list with the same
# order

### SETUP

# create 2 linked lists each containing the digits of 2 numbers 0-1000
# with reversed placed values. eg. 765 becomes 5->6->7

# a simple node of a linked list
class LinkedNode
  attr_accessor :next
  attr_accessor :value
end

# take a number and reverse the order of the digits into an array
# eg. 765 -> [5,6,7]
def reversed_digits(n)
  n.to_s.split('').map(&:to_i).reverse
end

# turn an array into a linked list
# eg. [5,6,7] -> 5->6->7
def array_to_linked_list(ary)
  head = nil
  tail = nil

  ary.each_with_index { |e, i|
    node = LinkedNode.new
    node.value = e
    if i == 0
      head = node
      tail = node
    else
      tail.next = node
      tail = node
    end
  }

  head
end

# generate the numbers and the linked list
num1 = rand(1000)
num2 = rand(1000)
puts "number 1: #{num1}"
puts "number 2: #{num2}"
digits1 = reversed_digits(num1)
digits2 = reversed_digits(num2)
puts "numbers of list 1: #{digits1.to_s}"
puts "numbers of list 2: #{digits2.to_s}"
list1_walk = array_to_linked_list(digits1)
list2_walk = array_to_linked_list(digits2)

# create combined list
combined_list_head = LinkedNode.new
combined_list_tail = combined_list_head
combined_list_tail.value = 0

# while either list has another element to add
carry = 0
while list1_walk || list2_walk
  list1_contrib = 0
  list2_contrib = 0

  # use value of, and advance, each linked node

  if list1_walk
    list1_contrib = list1_walk.value
    list1_walk = list1_walk.next
  end

  if list2_walk
    list2_contrib = list2_walk.value
    list2_walk = list2_walk.next
  end

  # the tail value might = 1 because of a carry
  new_val = combined_list_tail.value + list1_contrib + list2_contrib
  carry = new_val > 9
  combined_list_tail.value = new_val % 10

  # if we've carried or still have another item in either list
  # we need a new node
  if carry || list1_walk || list2_walk
    combined_list_tail.next = LinkedNode.new
    combined_list_tail.next.value = carry ? 1 : 0
  end

  # next loop, work on the next node
  combined_list_tail = combined_list_tail.next
end

# walk the list one last time to print the result
final = []
combined_list_walk = combined_list_head
while combined_list_walk
  final << combined_list_walk.value
  combined_list_walk = combined_list_walk.next
end
puts final.to_s


