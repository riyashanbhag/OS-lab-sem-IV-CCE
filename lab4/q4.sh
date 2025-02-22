#!/bin/bash

# Function to count lines
linecount() {
  wc -l < "$1"
}

# Function to count words
wordcount() {
  wc -w < "$1"
}

# Function to count characters
charcount() {
  wc -c < "$1"
}

# Check if the correct number of arguments are provided
if [ $# -lt 2 ]; then
  echo "Usage: $0 [-linecount|-wordcount|-charcount] <file>"
  exit 1
fi

# Extract the option and file from the command-line arguments
option=$1
file=$2

# Check if the file exists
if [ ! -f "$file" ]; then
  echo "File '$file' does not exist."
  exit 1
fi

# Process the option using a case statement
case "$option" in
  -linecount)
    linecount "$file"
    ;;
  -wordcount)
    wordcount "$file"
    ;;
  -charcount)
    charcount "$file"
    ;;
  *)
    echo "Invalid option. Use -linecount, -wordcount, or -charcount."
    exit 1
    ;;
esac
