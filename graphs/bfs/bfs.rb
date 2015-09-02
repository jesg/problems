
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
