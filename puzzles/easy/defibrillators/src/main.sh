#!/usr/bin/env bash

# Read the input
read -r long
read -r lat
read -r n

# Replaces , with .
long=$(echo $long | tr "," ".")
lat=$(echo $lat | tr "," ".")

distance() {
    # Points (x1, y1) and (x2, y2)
    local x1=$1
    local y1=$2
    local x2=$3
    local y2=$4

    bc -l << EOF
        scale = 20
        pi = 4 * a(1)

        x1 = $x1 * pi / 180
        y1 = $y1 * pi / 180
        x2 = $x2 * pi / 180
        y2 = $y2 * pi / 180

        x = (x2 - x1) * c((y1 + y2) / 2)
        y = y2 - y1
        sqrt(x ^ 2 + y ^ 2) * 6371
EOF
}

closest_def=""
min_dist=9999

for ((i = 0; i < $n; i++)); do
    # (id; name; address; phone number; long; lat)
    IFS= read -r defib

    # Get the name, long and lat fields
    def_name=$(echo $defib | tr "," "." | cut -d ";" -f 2)
    def_long=$(echo $defib | tr "," "." | cut -d ";" -f 5)
    def_lat=$(echo $defib | tr "," "." | cut -d ";" -f 6)

    dist=$(distance $long $lat $def_long $def_lat)

    if (( $(echo "$dist < $min_dist" | bc -l) )); then
        min_dist=$dist
        closest_def=$def_name
    fi
done

echo "$closest_def"
