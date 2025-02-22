#!/bin/bash

# Check if the correct number of arguments is passed
if [ $# -ne 2 ]; then
  echo "Usage: $0 <source_file> <destination_file>"
  exit 1
fi

# Assign input arguments to variables
source_file=$1
destination_file=$2

# Check if the source file exists
if [ ! -f "$source_file" ]; then
  echo "Source file does not exist."
  exit 1
fi

# Copy the file
cp "$source_file" "$destination_file"

# Verify if the copy was successful
if [ $? -eq 0 ]; then
  echo "File copied successfully."
else
  echo "Failed to copy the file."
  exit 1
fi
