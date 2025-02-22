#!/bin/bash

# Find all .txt files recursively and rename them to .text
find . -type f -name "*.txt" | while read file; do
    # Get the new file name by replacing .txt with .text
    new_file="${file%.txt}.text"
    
    # Rename the file using mv
    mv "$file" "$new_file"
    echo "Renamed: $file to $new_file"
done
