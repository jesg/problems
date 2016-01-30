# encoding: UTF-8

RubyVM::InstructionSequence.compile_option = {
  :tailcall_optimization => true,
  :trace_instruction => false
}

def bsearch(arr, x, low, high)
  return -1 if low > high

  mid = (low + high) / 2
  if arr[mid] < x
    return bsearch(arr, x, mid+1, high)
  elsif arr[mid] > x
    return bsearch(arr, x, low, mid-1)
  else
    return mid
  end
end

puts bsearch((0..100).to_a, 40, 0, 100)
