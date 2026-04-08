#!/usr/bin/env bash

while true; do
    highest_peak=0
    highest_index=0

    for ((i = 0; i < 8; i++)); do
        read -r mountain_h

        if [[ $mountain_h -gt $highest_peak ]]; then
            highest_peak=$mountain_h
            highest_index=$i
        fi

    done

    echo "$highest_index"
done
