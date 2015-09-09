
# implement thimbleby's solution to the chinese @postman problem
# http://www.cs.swansea.ac.uk/~csharold/cv/files/cpp.pdf


class Graph

  attr_accessor :n, :neg, :pos, :degree, :path, :edges, :cheapest_edge, :f, :defined, :label, :c, :initialized
  # private :n, :@degree, :@neg, :@pos, :path, :edges, :cheapest_edge, :f, :defined, :label, :c, :initialized

  def initialize(vertices)
    @n = vertices
    @degree = Array.new(n).fill(0)
    @defined = Array.new(n).fill { |_| Array.new(n).fill(false) }
    @label = Array.new(n).fill { |_| Array.new(n).fill { |_| [] } }
    @c = Array.new(n).fill { |_| Array.new(n).fill(0.0) }
    @f = Array.new(n).fill { |_| Array.new(n).fill(0) }
    @edges = Array.new(n).fill { |_| Array.new(n).fill(0) }
    @cheapest_edge = Array.new(n).fill { |_| Array.new(n).fill(0) }
    @path = Array.new(n).fill { |_| Array.new(n).fill(0) }
    @initialized = true
  end


  def cpp
    puts label.to_s
    initialized?
    least_cost_paths
    check_valid
    find_feasible
    puts 'hi' while improvments
    print(0)
  end

  def add_edge(lab, u, v, cost)
    @label[u][v] = [] unless defined[u][v]
    @label[u][v] << lab
    if !defined[u][v] || c[u][v] > cost
      @c[u][v] = cost
      @cheapest_edge[u][v] = edges[u][v]
      @defined[u][v] = true
      @path[u][v] = v
    end
    @edges[u][v] += 1
    @degree[u] += 1
    @degree[v] -= 1
    self
  end

  def check_valid
    (0...n).each do |i|
      raise '@negative cycle' if c[i][i] < 0
      (0...n).each do |j|
        raise 'not strongly connected' unless defined[i][j]
      end
    end
  end

  def least_cost_paths
    (0...n).each do |k|
      (0...n).each do |i|
        if defined[i][k]
          (0...n).each do |j|
            if defined[k][j] && (!defined[i][j] || c[i][j] > c[i][k]+c[k][j])
              @defined[i][j] = true
              @path[i][j] = path[i][k]
              @c[i][j] = c[i][k] + c[k][j]
              # negative cycle
              return if i == j && c[i][j] < 0
            end
          end
        end
      end
    end
  end

  def find_feasible
    nn, np = 0, 0
    (0...n).each do |i|
      if degree[i] < 0
        nn += 1
      elsif degree[i] > 0
        np += 1
      end
    end

    @neg = Array.new(nn)
    @pos = Array.new(np)
    nn, np = 0, 0
    (0...n).each do |i|
      if degree[i] < 0
        @neg[nn] = i
        nn += 1
      elsif degree[i] > 0
        @pos[np] = i
        np += 1
      end
    end

    (0...nn).each do |u|
      i = neg[u]
      (0...np).each do |v|
        j = pos[v]
        @f[i][j] = -degree[i] < degree[j] ? -degree[i] : degree[j]
        @degree[i] += f[i][j]
        @degree[j] -= f[i][j]
      end
    end
  end

  def improvments
    r = Graph.new(n)
    (0...neg.length).each do |u|
      i = neg[u]
      (0...pos.length).each do |v|
        j = pos[v]
        if edges[i][j] > 0
          r.add_edge(nil, i, j, c[i][j])
        end
        if f[i][j] != 0
          r.add_edge(nil, j, i, -c[i][j])
        end
      end
    end

    r.least_cost_paths
    puts r.c.to_s
    (0...n).each do |i|
      if r.c[i][i] < 0
        k = 0
        kunset = true
        u = i
        begin
          v = r.path[u][i]
          if r.c[u][v] < 0 && (kunset || k > f[v][u])
            k = f[v][u]
            kunset = false
          end
          u = v
        end while u != i
        u = i
        begin
          v = r.path[u][i]
          if r.c[u][v] < 0
            @f[v][u] -= k
          else
            @f[u][v] += k
          end
          u = v
        end while u != i
        puts 'foobar'
        return true
      end
    end
    false
  end

  def print(start)
    puts f.to_s
    v = start
    loop do
      u = v
      (0...n).each do |i|
        if f[u][i] > 0
          v = i
          @f[u][v] -= 1
          puts "  take path from #{u} to #{v}: "
        end
        while u != v
          p = path[u][v]
          puts "    take edge #{label[u][p][cheapest_edge[u][p]]} from #{u} to #{p}"
          u = p
        end
        u = v
        break
      end

      v = -1
      (0...n).each do |i|
        if edges[u][i] > 0
          v = i if v == -1 || i != path[u][start]
        end
        return if v == -1
        puts "take edge #{label[u][v][edges[u][v]-1]} from #{u} to #{v}"
        @edges[u][v] -= 1
      end
    end
  end


  def initialized?
    raise 'graph not initialized' unless initialized
    initialize = false
  end

end

graph = Graph.new(4)
graph.add_edge(:a, 0, 1, 1)
graph.add_edge(:b, 0, 2, 1)
graph.add_edge(:c, 1, 2, 1)
graph.add_edge(:d, 1, 3, 1)
graph.add_edge(:e, 2, 3, 1)
graph.add_edge(:f, 3, 0, 1)
graph.cpp

