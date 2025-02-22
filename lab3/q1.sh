#!/bin/bash

# Prompt user to enter file path
echo "Enter the file or directory path:"
read filepath

# Check if the file exists
if [ -e "$filepath" ]; then
    # Check if it's a directory
    if [ -d "$filepath" ]; then
        echo "$filepath is a directory."
    # Check if it's a regular file
    elif [ -f "$filepath" ]; then
        echo "$filepath is a regular file."
    else
        echo "$filepath is neither a regular file nor a directory."
    fi
else
    echo "$filepath does not exist."
fi
