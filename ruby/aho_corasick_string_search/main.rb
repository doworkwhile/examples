require './aho_corasick_trie.rb'

match_words = [ 'ring', 'ing', 'sink', 'car' ]
find_in = 'darling caring car sinking in helsinki'

act = AhoCorasickTrie.new

match_words.each { |w| act.add_word(w) }

puts "Test Aho-Corasick"
puts "Matching words:"
puts match_words.to_s
puts "Searching string:"
puts "\"#{find_in}\""
puts "Built Trie:"
act.display
puts "Searching:"
matches = act.search(find_in)
puts "#{matches.size} matches"
matches.each { |match|
  puts match.to_s
}
