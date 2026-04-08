#!/usr/bin/env bash

read -r L
read -r H
IFS= read -r T

# Convert the input to uppercase
T=${T^^}

for ((i = 0; i < H; i++)); do
    IFS= read -r ROW

    # Iterate over each letter
    for ((j = 0; j < ${#T}; j++)); do
        char=${T:j:1}

        # Calculate the ASCII codes
        printf -v char_index "%d" "'$char"
        printf -v A_index "%d" "'A"
        printf -v Z_index "%d" "'Z"

        # Calculate the offset [0..26]
        offset=$((char_index - A_index))
        if [[ $offset -lt 0 ||  $offset -gt 25 ]]; then
            offset=26
        fi

        start=$((offset * L))
        for ((k = start; k < start + L; k++)); do
            echo -n "${ROW:k:1}"
        done
    done

    echo
done
