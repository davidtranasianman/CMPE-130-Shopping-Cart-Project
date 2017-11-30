# David Tran/Toan Nguyen
# CMPE 130
# quick_sort_min.rb
# November 30, 2017

def quick_sort_min(array, from = 0, to = nil)
  if to == nil
    # Sort the whole array
    to = array.count - 1
  end

  if from >= to
    # Sort is now complete
    return array
  end

  # Start pivot in middle of array
  pivot = array[array.size/2]

  # Create min and max pointers to iterate through array
  min = from
  max = to

  # Set minimum pointer at free spot in array
  free = max

  while min < max
    # Evaluate for array[min]
    if free ==  max
      # Swap values if array[min] is larger than pivot
      if array[min] >= pivot
        array[free] = array[min]
        max = max - 1
        free = min
      else
        min = min + 1
      end
    end
  end


  array[free] = pivot

  quick_sort_max(from, free-1)
  quick_sort_max(free+1, to)
end