def merge(left, right)
  out = []
  i = 0
  j = 0
  while i < left.size && j < right.size
    if left[i] > right[j]
      out << left[i]
      i += 1
    else
      out << right[j]
      j += 1
    end
  end

  while i < left.size
    out << left[i]
    i += 1
  end

  while j < right.size
    out << right[j]
    j += 1
  end

  out
end

def mergesort(array)
  return array if array.size < 2

  left_array = array[0, (array.size / 2) - 1]
  right_array = array[array.size / 2, array.size]

  mergesort(left_array)
  mergesort(right_array)

  merge(left_array, right_array)
end

a = [29, 4, 39, 59, 7, 48, 5, 14, 83, 77, 25, 62, 82, 57, 35, 1, 39, 20, 4,
     78, 33, 72, 64, 73, 81, 77, 61, 16, 73, 39]

puts mergesort(a).inspect
