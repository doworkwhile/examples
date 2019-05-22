
def anagramRotate(chars, at)
  length = chars.size
  return if (at >= length)

  temp = chars[at]
  (at..(length-1)).each { |i|
    chars[i] = chars[i + 1]
  }
  chars[length - 1] = temp
end


def anagramRecurse(chars, at)
  chars_left = chars.size - at
  return if (chars_left == 1)

  (0...chars_left).each { |i|
    anagramRecurse(chars, at + 1)
    if (chars_left == 2)
      puts chars.join('')
    end
    anagramRotate(chars, at)
  }
end

def anagram(text)
  chars = text.split('')
  anagramRecurse(chars, 0)
end

print "anagrams for text > "
input = gets.chomp
anagram(input)