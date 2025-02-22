#!/bin/bash

# Check if there are any arguments passed
if [ $# -eq 0 ]; then
  echo "Usage: $0 <file1> <file2> ... <fileN>"
  exit 1
fi

# Loop through all files passed as arguments
for file in "$@"; do
  # Check if the file exists
  if [ -f "$file" ]; then
    # Prompt user for confirmation
    read -p "Are you sure you want to delete '$file'? (y/n): " choice
    case "$choice" in
      y|Y)
        rm "$file"  # Remove the file if confirmed
        echo "$file has been deleted."
        ;;
      n|N)
        echo "$file was not deleted."
        ;;
      *)
        echo "Invalid choice. '$file' was not deleted."
        ;;
    esac
  else
    echo "File '$file' does not exist."
  fi
done
