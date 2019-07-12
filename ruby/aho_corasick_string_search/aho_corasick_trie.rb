require './aho_corasick_node.rb'

class AhoCorasickTrie

  def initialize
    @head = AhoCorasickNode.new('*')
    @head.letters_sum = '*'
  end

  def add_word(word)
    word_size = word.size
    walking_node = @head
    letter_index = 0

    while letter_index < word_size
      letter = word[letter_index]
      child_with_letter = walking_node.child_of_letter(letter)

      if child_with_letter
        walking_node = child_of_letter
      else
        new_node = AhoCorasickNode.new(letter)
        new_node.prev_link = walking_node
        new_node.letters_sum = word[0..letter_index]
        walking_node.add_child(new_node)
        walking_node = new_node
      end


      letter_index += 1

      if letter_index == word_size
        walking_node.word = word
      end
    end

    self.build_suffixes
    self.build_outputs
  end

  def build_suffixes
    queue = [@head]

    while queue.size > 0
      item = queue.shift

      item_prev = item.prev_link
      if item_prev == @head
        item.suffix_link = @head
      elsif item_prev
        item_back = item_prev
        while item_back.suffix_link
          item_back = item_back.suffix_link
          item_back_child_of_letter = item_back.child_of_letter(item.letter)
          if item_back_child_of_letter
            item.suffix_link = item_back_child_of_letter
            break
          end
        end
        if item.suffix_link == nil
          item.suffix_link = @head
        end
      end

      item.children.each { |c|
        queue << c
      }
    end
  end

  def build_outputs
    queue = [@head]

    while queue.size > 0
      item = queue.shift
      item_suffix = item.suffix_link

      if item_suffix
        if item_suffix.word
          item.output_link = item_suffix
        elsif item_suffix.output_link
          item.output_link = item_suffix.output_link
        end
      end

      item.children.each { |c|
        queue << c
      }
    end
  end

  def search(word)
    outputs = []

    walking_node = @head
    letter_index = 0
    word_size = word.size
    while letter_index < word_size
      letter = word[letter_index]
      child_with_letter = walking_node.child_of_letter(letter)

      while child_with_letter == nil && walking_node != @head
        walking_node = walking_node.suffix_link
        child_with_letter = walking_node.child_of_letter(letter)
      end

      if child_with_letter
        if child_with_letter.word
          outputs << [letter_index, child_with_letter.word]
        end

        output_link_chain = child_with_letter.output_link
        while output_link_chain
          outputs << [letter_index, output_link_chain.word]
          output_link_chain = output_link_chain.output_link
        end

        walking_node = child_with_letter
      end

      letter_index += 1
    end

    return outputs
  end

  def display
    @head.display
  end

end
