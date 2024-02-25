#!/bin/bash

# Define the directory you want to list
directory="tests"

# Check if the directory exists
if [ -d "$directory" ]; then
    # List all files in the directory without extensions, sort them alphabetically
    files=$(find "$directory" -type f -exec basename {} \; | sed 's/\.[^.]*$//' | sort | uniq)
    
    # Enclose each file name in double quotes and separate them by commas
    formatted_files=$(echo "$files" | sed 's/^/"/; s/$/"/' | tr '\n' ', ')

    # Print the formatted list of files
    echo "${formatted_files%, }"
    echo  # Newline for readability
else
    echo "Directory not found: $directory"
fi

