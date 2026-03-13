#!/usr/bin/env bash

read -r N
read -r Q

declare -A types
declare -l EXT f_ext

for ((i = 0; i < N; i++)); do
    read -r EXT MT
    types[$EXT]=$MT
done

for ((i = 0; i < Q; i++)); do
    IFS= read -r FNAME
    f_ext=""

    for ((j = ${#FNAME} - 1; j >= 0; j--)); do
        if [[ ${FNAME:j:1} == "." ]]; then
            f_ext="${FNAME:j + 1}"
            break
        fi
    done
    if [[ $f_ext == "" || ${types[$f_ext]} == "" ]]; then
        echo "UNKNOWN"
    else
        echo "${types[$f_ext]}"
    fi
done
