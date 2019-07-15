min_str_len = 5
max_str_len = 10
alphabet_len = 6
str = [*0..rand(min_str_len..max_str_len)] # array of digits of random len
  .map { |e| 97 + rand(alphabet_len) } # random ord (97='a', 98='b', ...)
  .map(&:chr) # ord to chr
  .join

current_sub_len = 0
current_start = 0
longest_start = 0
longest_sub_len = 0
slide = {}

i = 0
while i < str.size
  char = str[i]
  has_slide_after_start = slide[char] && slide[char] >= current_start

  if has_slide_after_start
    new_start = slide[char] + 1
    slide_diff = new_start - current_start
    current_start = new_start
    current_sub_len -= slide_diff - 1
  else
    current_sub_len += 1
  end

  slide[char] = i

  if current_sub_len > longest_sub_len
    longest_sub_len = current_sub_len
    longest_start = current_start
  end

  i += 1
end

puts str
puts longest_start
puts longest_sub_len
puts  str[longest_start...(longest_start + longest_sub_len)]
