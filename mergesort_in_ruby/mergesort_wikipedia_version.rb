def merge(left, right)
  puts "left #{left.inspect}; right #{right.inspect}"
  out = []
  until left.empty? || right.empty?
    if left.first < right.first
      out << left.shift
    else
      out << right.shift
    end
  end
  out.concat(left).concat(right)
end

def mergesort(array)
  return array if array.size < 2

  left_array = array[0, array.size / 2]
  right_array = array[array.size / 2, array.size]

  merge(mergesort(left_array), mergesort(right_array))
end

a = [29, 4, 39, 59, 7, 48, 5, 14, 83, 77, 25, 62, 82, 57, 35, 1, 39, 20, 4,
     78, 33, 72, 64, 73, 81, 77, 61, 16, 73, 39]

# a = %w(49 34 39 65 100 61 62 46 36 89).map(&:to_i)

sorted_a = mergesort(a)
puts sorted_a.inspect

fail 'Sorting fail' if sorted_a != a.sort
