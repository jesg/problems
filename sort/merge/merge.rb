
def merge(arr, p, q, r)
  l = arr.slice(p...q)
  h = arr.slice(q...r)
  i = j = 0
  (p...r).each do |k|
    if l[i].nil?
      arr[k] = h[j]
      j += 1
    elsif h[j].nil?
      arr[k] = l[i]
      i += 1
    elsif l[i] <= h[j]
      arr[k] = l[i]
      i += 1
    else
      arr[k] = h[j]
      j += 1
    end
  end
end

def merge_sort(arr, p, r)
  if p < r
    q = (p + r) / 2
    merge_sort(arr, p, q)
    merge_sort(arr, q + 1, r)
    merge(arr, p, q, r)
  end
end

d = [4, 0, 5, 2, 9, 3, 6]
merge_sort(d, 0, d.length)
puts d
