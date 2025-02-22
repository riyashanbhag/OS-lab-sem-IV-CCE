#!/bin/bash

# Prompt the user for the file extension to search for
echo "Enter the file extension (e.g., .txt, .text):"
read extension

# Prompt the user for the target folder where files will be copied
echo "Enter the name of the new folder to copy files to:"
read target_folder

# Check if the target folder exists, if not, create it
if [ ! -d "$target_folder" ]; then
    echo "Target folder does not exist. Creating folder '$target_folder'."
    mkdir "$target_folder"
fi

# Copy files with the specified extension to the target folder
for file in *$extension; do
    # Check if it's a regular file (not a directory)
    if [ -f "$file" ]; then
        cp "$file" "$target_folder/"
        echo "Copied: $file to $target_folder"
    fi
done

echo "File copy operation completed."
