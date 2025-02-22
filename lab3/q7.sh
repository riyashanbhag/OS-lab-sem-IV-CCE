#!/bin/bash

# Prompt the user for the file name
echo "Enter the name of the file to modify:"
read filename

# Check if the file exists
if [ -f "$filename" ]; then
    # Delete all even-numbered lines using sed
    sed -i '2~2d' "$filename"
    echo "All even-numbered lines have been deleted from $filename."
else
    echo "The file '$filename' does not exist."
fi
