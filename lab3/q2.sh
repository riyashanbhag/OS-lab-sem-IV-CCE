#!/bin/bash

# Prompt the user for the folder path
echo "Enter the folder path:"
read folder

# Check if the folder exists
if [ -d "$folder" ]; then
    # Prompt the user for the search pattern (string)
    echo "Enter the pattern to search for:"
    read pattern

    # List files containing the pattern in the folder (without full path, just filenames)
    echo "Files containing the pattern '$pattern' are:"
    grep -lR --include="*" "$pattern" "$folder" | sed "s|^$folder/||"
else
    echo "The folder '$folder' does not exist."
fi
