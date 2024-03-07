#!/bin/bash

# Check for the required arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 source_directory destination_directory"
    exit 1
fi

source_directory="$1"
destination_directory="$2"

# Ensure the source directory exists
if [ ! -d "$source_directory" ]; then
    echo "Source directory '$source_directory' not found."
    exit 1
fi

# Ensure the destination directory exists
if [ ! -d "$destination_directory" ]; then
    mkdir -p "$destination_directory"
fi

# Copy header files while preserving directory structure
find "$source_directory" -type f -name "*.h" -exec sh -c '
    src="{}"
    dst='"$destination_directory"'
    relpath="${src#'"$source_directory"'/}"
    mkdir -p "$dst/$(dirname "$relpath")"
    cp "$src" "$dst/$relpath"
' \;

echo "Header files copied to '$destination_directory'."

