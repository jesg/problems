
Vertex = Struct.new(:color, :d, :prev, :i)

def bfs(graph, s)
  graph.each do |v, i|
    v.color = :white
    v.d = Float::INFINITY
    v.prev = nil
  end

  s.color = :grey
  s.d = 0
  s.prev = nil
  queue = []
  queue.push(s)
  until queue.empty?
    u = queue.pop
    graph[u.i].each do |v|
      next unless v.color == :white
      v.color = :grey
      v.d = u.d + 1
      v.prev = u
      queue.push(v)
    end
    u.color = :black
  end
end

def print_path(graph, s, v)
  if v.i == s.i
    puts s.i
  elsif v.prev == nil
    puts "no path from #{s.i} to #{v.i}"
  else
    print_path(graph, s, v.prev)
    puts v.i
  end
end

graph = [
  [ Vertex.new(:white, Float::INFINITY, nil, 1), Vertex.new(:white, Float::INFINITY, nil, 3) ],
  [ Vertex.new(:white, Float::INFINITY, nil, 4)],
  [ Vertex.new(:white, Float::INFINITY, nil, 5), Vertex.new(:white, Float::INFINITY, nil, 4) ],
  [ Vertex.new(:white, Float::INFINITY, nil, 1)],
  [ Vertex.new(:white, Float::INFINITY, nil, 3)],
  [ Vertex.new(:white, Float::INFINITY, nil, 5)],
]

bfs(graph, Vertex.new(:white, Float::INFINITY, nil, 1))
print_path(graph, graph[0][0], graph[4][0])
