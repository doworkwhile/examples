import random

# create a test string
min_str_len = 5
max_str_len = 10
alphabet_len = 6
str_len = random.randint(min_str_len, max_str_len)
test_chrs = [chr(97 + random.randrange(alphabet_len)) for i in xrange(str_len)]
test_str = ''.join(test_chrs)
print test_str

# algorithm: find the first longest substring with no repeats

# any substring needs 2 values to identify it:
# the index that it begins and its length.
# these are the recorded values of the longest substring
longest_sub_start = 0
longest_sub_len = 0

# the algorithm will walk the string and keep track of one substring at a time
# as that substring grows, it is compared to the longest substring already
# recorded
current_sub_start = 0
current_sub_len = 0

# as the algorithm walks the string it will record
# the last index it encountered a character.
# this informs the algorithm that:
# 1) when the last index of an encountered character is past the start of
# the current substring, the substring can't grow larger without including
# a repeating character.
# 2) if the start of the current substring is moved past the last index
# of the encountered character, it can include the new character without
# containing any duplicates (when the start of the substring is moved
# it has also a new length)
slide = {}


# walk the entire length of the string
for i in xrange(len(test_str)):
  # store the current letter of the walk
  letter = test_str[i]

  # has this letter been encountered before and if so: does it interfere with
  # the current substring
  seen = letter in slide
  should_slide_current_start = seen and slide[letter] >= current_sub_start

  # if including this letter would cause a repeat
  if should_slide_current_start:
    # the new start will be 1 after the last index of the repeated letter
    new_start = slide[letter] + 1

    # the difference of the new and old starts indicates amount to reduce
    # from the length
    slide_diff = new_start - current_sub_start

    # set the current start to the new start
    current_sub_start = new_start
    # and adjust the length, this needs an extra -1 because the new start
    # was 1 past the actual index of the repeated letter
    current_sub_len -= slide_diff - 1

  # else this letter can be included without being a repeat
  else:
    # so increase the current substring length
    current_sub_len += 1

  # record the latest index of this letter
  slide[letter] = i

  # compare the new length of the current substring to that of the longest
  # when the current substring is larger,
  # the record of the longest substring should match the current substring
  if current_sub_len > longest_sub_len:
    longest_sub_start = current_sub_start
    longest_sub_len = current_sub_len


# print the answer
print 'result:',
longest_sub_end = longest_sub_start + longest_sub_len
longest_sub_range = xrange(longest_sub_start, longest_sub_end)
print ''.join([test_str[i] for i in longest_sub_range])
