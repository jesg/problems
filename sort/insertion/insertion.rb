
d = [4, 5, 0, 1, 9, 3]
(1...d.length).each do |j|
  key = d[j]
  i = j - 1
  while i >= 0 && d[i] > key
    d[i + 1] = d[i]
    i = i - 1
  end
  d[i + 1] = key
end

puts d
