#!/bin/bash

# Function to search patterns in the input file
search_patterns() {
  local file=$1
  echo "Searching for patterns in the file: $file"
  shift  # Remove the file argument, leaving only patterns

  for pattern in "$@"; do
    echo "Lines containing pattern '$pattern':"
    grep "$pattern" "$file"  # Search for the pattern in the input file
    echo
  done
}

# Function to delete patterns from the input file
delete_patterns() {
  local file=$1
  echo "Deleting patterns from the file: $file"
  shift  # Remove the file argument, leaving only patterns

  for pattern in "$@"; do
    # Use sed to remove all occurrences of the pattern
    sed -i "/$pattern/d" "$file"
    echo "Pattern '$pattern' deleted."
  done
}

# Check if file and patterns are provided as arguments
if [ $# -lt 2 ]; then
  echo "Usage: $0 <file> <pattern1> <pattern2> ..."
  exit 1
fi

# Extract the file and patterns from the command-line arguments
file=$1
shift  # Remove the first argument (file) from the list, leaving only patterns

# Check if the file exists
if [ ! -f "$file" ]; then
  echo "File '$file' does not exist."
  exit 1
fi

# Menu-driven loop
while true; do
  echo "Menu:"
  echo "1. Search patterns"
  echo "2. Delete patterns"
  echo "3. Exit"
  echo -n "Choose an option (1/2/3): "
  read option

  case "$option" in
    1)
      # Option to search patterns
      search_patterns "$file" "$@"
      ;;
    2)
      # Option to delete patterns
      delete_patterns "$file" "$@"
      ;;
    3)
      # Option to exit
      echo "Exiting the script."
      exit 0
      ;;
    *)
      # Invalid option
      echo "Invalid option. Please choose 1, 2, or 3."
      ;;
  esac
done
