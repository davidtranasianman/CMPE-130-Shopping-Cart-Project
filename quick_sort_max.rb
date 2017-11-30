# David Tran/Toan Nguyen
# CMPE 130
# quick_sort_max.rb
# November 30, 2017

def quick_sort_max(array, from = 0, to = nil)
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
  free = min

  while min < max
    # Evaluate for array[max]
    if free == min
      # Swap values if array[max] is smaller than pivot
      if array[max] <= pivot
        array[free] = array[max]
        min = min + 1
        free = max
      else
        max = max - 1
      end

    end
  end

  array[free] = pivot

  quick_sort_max(from, free-1)
  quick_sort_max(free+1, to)
end