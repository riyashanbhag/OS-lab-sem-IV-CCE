#!/bin/bash

# Iterate over all files in the current directory
for file in *; do
    # Check if it's a regular file
    if [ -f "$file" ]; then
        # Use sed to replace 'ex:' with 'Example:' at the start of the line or after a period
        sed -i 's/\(^\|[.]\)[[:space:]]*ex:/\1Example:/g' "$file"
        echo "Modified: $file"
    fi
done

echo "Modification process completed."
