from aho_corasick_dictionaries import AhoCorasickDictionaries
from aho_corasick_trie import AhoCorasickTrie

matchWords = [ 'ring', 'ing', 'sink', 'car' ]
findIn = 'darling caring car sinking in helsinki'

acd = AhoCorasickDictionaries()
act = AhoCorasickTrie()
for word in matchWords:
  acd.add(word)
  act.add(word)

print('=== Aho-Corasick ===')
print 'Strings to match:', matchWords
print 'String to search:', findIn

print('=== Aho-Corasick with Dictionaries display === ')
# pre-build the dictionary results before searching
# to properly display the constructed automaton
acd.build()
acd.display()

print('=== Aho-Corasick with Trie display ===')
act.display()

print('=== Searching ===')
acdSearch = acd.search(findIn)
actSearch = act.search(findIn)

print('=== Aho-Corasick with Dictionaries results === ')
# flatten results from the dictionary search
acdSearchFlat = []
for result in acdSearch:
  for resultWord in result[1]:
    flatResult = (result[0], resultWord)
    acdSearchFlat.append(flatResult)
    print flatResult

print('=== Aho-Corasick with Trie results === ')
for result in actSearch:
  print result

print('=== Both agree? ===')
print acdSearchFlat == actSearch

