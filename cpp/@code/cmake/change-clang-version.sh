#!/bin/bash

# Check if the version number is passed as a command-line argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <version-number>"
    exit 1
fi

# The version number to be replaced, passed as the first argument
version=$1

# List of base package names
packages=("clang" "clang-tools" "clang-format" "clang-tidy")

# Loop through each base package name
for basepkg in "${packages[@]}"; do
    # Construct the package name with the version
    pkg="${basepkg}-${version}"

    # Find all files installed by the package, filter executables, and end with the version number
    dpkg -L $pkg | while read file; do
        if [[ -x "$file" && "$file" == *-${version} ]]; then
            # Construct the new filename by removing the version suffix
            newname="${file%-${version}}"
            if [ -e "$newname" ]; then
                if [ -L "$newname" ]; then
                    echo "Overwriting existing symlink for $newname"
                    rm "$newname"
                    ln -s "$file" "$newname"
                else
                    echo "Skipping $newname as it is an existing binary."
                fi
            else
                echo "Creating symlink for $file -> $newname"
                ln -s "$file" "$newname"
            fi
        fi
    done
done
