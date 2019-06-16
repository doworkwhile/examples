require './huffman_coding.rb'
require 'test/unit'

class TestHuffmanCoding < Test::Unit::TestCase

  def test_huffman_coding
    nodes = [*'a'..'e'].each_with_index.map { |symbol, i| [symbol, i] }
    tree = HuffmanTree.new(nodes)
    assert_equal(tree.prefix_for('a'), "0011")
    assert_equal(tree.prefix_for('b'), "0010")
    assert_equal(tree.prefix_for('c'), "000")
    assert_equal(tree.prefix_for('d'), "01")
    assert_equal(tree.prefix_for('e'), "1")
  end

end