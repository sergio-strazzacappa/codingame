#!/usr/bin/env bash

IFS= read -r MESSAGE

to_bin() {
    # Converts the parameter in decimal format into binary

    local dec_num=$1
    local bin_num=""

    while [[ $dec_num -gt 0 ]]; do
        bin_num+=$((dec_num % 2))
        ((dec_num /= 2))
    done

    # Complete the remaining bits with 0
    while [[ ${#bin_num} -lt 7 ]]; do
        bin_num+="0"
    done

    echo "$bin_num"
}

binary_message=""

for ((i = 0; i < ${#MESSAGE}; i++)); do
    char=${MESSAGE:i:1}
    printf -v c "%d" "'$char"
    binary_message="$(to_bin $c)${binary_message}"
done

encoded_message=""
last=-1

for ((i = ${#binary_message} - 1; i >= 0; i--)); do
    current=${binary_message:i:1}

    if [[ $current -eq $last ]]; then
        encoded_message+="0"
    elif [[ $last -eq -1 ]]; then
        if [[ $current -eq 0 ]]; then
            encoded_message+="00 0"
        else
            encoded_message+="0 0"
        fi
    elif [[ $current -eq 0 ]]; then
        encoded_message+=" 00 0"
    else
        encoded_message+=" 0 0"
    fi

    last=$current
done

echo "$encoded_message"
