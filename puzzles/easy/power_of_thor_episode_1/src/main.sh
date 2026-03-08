read -r lightX lightY initialTX initialTY

while true; do
    read -r remainingTurns
    direction=""

    # Move down
    if [[ $initialTY -lt $lightY ]]; then
        direction+="S"
        ((initialTY++))
    fi

    # Move up
    if [[ $initialTY -gt $lightY ]]; then
        direction+="N"
        ((initialTY--))
    fi

    # Move right
    if [[ $initialTX -lt $lightX ]]; then
        direction+="E"
        ((initialTX++))
    fi

    # Move left
    if [[ $initialTX -gt $lightX ]]; then
        direction+="W"
        ((initialTX--))
    fi

    echo "$direction"
done
