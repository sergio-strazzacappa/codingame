#!/usr/bin/env bash

declare -a temp

read -r n
read -r -a temp

if [[ "$n" -eq 0 ]]; then
    echo "0"
    exit 0
fi

abs() {
    local n=$1
    echo $(( n < 0 ? -n : n ))
}

closest_temp=$(abs "${temp[0]}")
closest_value=${temp[0]}

for t in "${temp[@]}"; do
    value=$(abs "$t")

    if [[ "$value" -lt "$closest_temp" ]]; then
        closest_temp=$value
        closest_value=$t
    elif [[ "$value" -eq "$closest_temp" && "$closest_value" -lt 0 ]]; then
            closest_value=$t
    fi
done

echo "$closest_value"
