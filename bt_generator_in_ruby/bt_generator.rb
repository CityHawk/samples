require 'yaml'
require 'pp'
class Node
  attr_accessor :data, :left, :right

  def initialize(data)
    @data = data
  end

  def to_hash
    hash = {}
    hash['data'] = @data
    hash['left'] = @left.to_hash if @left
    hash['right'] = @right.to_hash if @right
    hash
  end
end

class RandomWord
  def initialize
    @words = File.readlines("/usr/share/dict/words")
  end

  def get
    @words.sample.chomp
  end
end

def addnode(root, r, n)
  return if n == 0
  root.left = Node.new(r.get)
  root.right = Node.new(r.get)
  n -= 1
  addnode root.left, r, n
  addnode root.right, r, n
end

def main
  n = 5
  rnd = RandomWord.new
  root = Node.new(rnd.get)
  addnode root, rnd, n

  # pp root
  puts root.to_hash.to_yaml
end

main
