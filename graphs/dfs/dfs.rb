require 'set'

Vertex = Struct.new(:color, :d, :prev, :name, :adj, :f)


def dfs(graph)
  time = 0
  graph.each do |vertex|
    next unless vertex.color == :white
    visit(graph, vertex)
  end
end

def visit(graph, u)
  time += 1
  u.d = time
  u.color = :grey
  u.adj.each do |v|
    next unless v.color == :white
    v.prev = u
    visit(graph, v)
  end
  u.color = :black
  time += 1
  u.f = time
end

raw_graph = [
  0,1,
  0,3,
  1,4,
  2,5,
  2,4,
  3,1,
  4,3,
  5,5,
]

# create graph
graph = {}
pairs = raw_graph.each_cons(2).to_a
raw_graph.to_set.each do |a|
  graph[a] = Vertex.new(:white, Float::INFINITY, nil, a, [], nil)
end

pairs.each do |arr|
  a, b = arr
  graph[a].adj << graph[b]
end
