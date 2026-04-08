#!/usr/bin/env bash

read -r n

declare -a horses
horses=()

# Save the horses strength in an indexed array
for ((i = 0; i < $n; i++)); do
    read -r p
    horses[i]=$p
done

# Sort the horses by their strength
IFS=$'\n' sorted=($(sort -n <<<"${horses[*]}"))

closest=9999;

for ((i = 0; i < $n-1; i++)); do
    diff=$((${sorted[$i + 1]} - ${sorted[$i]}))

    if [[ $diff -lt $closest ]]; then
        closest=$diff
    fi
done

echo $closest
