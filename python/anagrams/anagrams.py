def build_str(chars):
  return ''.join(chars)

def rotate(textChars, length, at):
  if (at >= length):
    return

  temp = textChars[at]
  for i in range(at, length - 1):
   textChars[i] = textChars[i + 1]
  textChars[length - 1] = temp

def anagramRecurse(textChars, length, at):
  end = length - at;
  if (end == 1):
    return;

  for i in range(0, end):
    anagramRecurse(textChars, length, at + 1)
    if (end == 2):
      print build_str(textChars)
    rotate(textChars, length, at)


def anagram(text):
  textLen = len(text)
  textChars = list(text)
  anagramRecurse(textChars, textLen, 0)

myInput = raw_input("anagrams for text > ")
anagram(myInput)
