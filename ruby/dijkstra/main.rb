require './undirected_graph.rb'
require './dijkstra.rb'

ug = UndirectedGraph.new
nodes = 10
min_paths = 1
max_paths = 5
min_cost = 2
max_cost = 16

# build graph
# for each node
nodes.times { |i|
  rand_paths = [*min_paths..max_paths].sample
  rand_to = [*0...nodes]
    .delete_if { |n| n == i } # don't path from n to n
    .sample(rand_paths)

  # for each path endpoint from path i
  rand_to.each { |to|
    rand_cost = min_cost + (rand() * (max_cost - min_cost)).floor
    puts "#{i} -> #{to} = #{rand_cost}$"
    ug.add_path(i, to, rand_cost)
  }
}

start_and_end = [*0...nodes].sample(2)
puts "walk from #{start_and_end[0]} to #{start_and_end[1]}"
puts dijkstra(ug, start_and_end[0], start_and_end[1]).to_s
