
# http://stackoverflow.com/questions/21371681/quick-sort-in-ruby-language
#
def quicksort(*ary)
  return [] if ary.empty?

  pivot = ary.delete_at(rand(ary.size))
  left, right = ary.partition(&pivot.method(:>))

  return *quicksort(*left), pivot, *quicksort(*right)
end
