#!/bin/bash

# Check if arguments are passed
if [ $# -lt 1 ]; then
  echo "Usage: $0 <string1> <string2> ... <stringN>"
  exit 1
fi

# User-defined sort function (Bubble Sort)
sort_strings() {
  local arr=("$@")
  local n=${#arr[@]}

  # Bubble Sort algorithm
  for ((i = 0; i < n-1; i++)); do
    for ((j = 0; j < n-i-1; j++)); do
      # Compare adjacent strings lexicographically
      if [[ "${arr[j]}" > "${arr[$((j+1))]}" ]]; then
        # Swap if the string on the left is lexicographically larger
        temp="${arr[j]}"
        arr[j]="${arr[$((j+1))]}"
        arr[$((j+1))]="$temp"
      fi
    done
  done

  # Print the sorted strings
  echo "${arr[@]}"
}

# Call the sort function with the command-line arguments
sort_strings "$@"
