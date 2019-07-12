class AhoCorasickNode

  attr_reader :letter, :children
  attr_accessor :word, :letters_sum, :prev_link, :suffix_link, :output_link

  def initialize(letter)
    @letter = letter
    @children = []
    @word = nil
    @prev_link = nil
    @suffix_link = nil
    @output_link = nil
    @letters_sum = nil
  end

  def child_of_letter(l)
    @children.find { |e| e.letter == l  }
  end

  def add_child(child_node)
    @children << child_node
  end

  def display(depth = 0)
    depth.times { print '----|' }
    print " #{@letter} "
    if @word
      print "( #{@word} )"
    end
    if @suffix_link
      print "[ #{@suffix_link.letter} / #{@suffix_link.letters_sum} ]"
    end
    if @output_link
      print "{ #{@output_link.word} }"
    end
    puts

    children.each { |c| c.display(depth + 1) }
  end

end
