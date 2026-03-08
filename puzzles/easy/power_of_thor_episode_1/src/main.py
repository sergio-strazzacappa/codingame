#! /usr/bin/env python3

light_x, light_y, initial_tx, initial_ty = [int(i) for i in input().split()]

while True:
    remaining_turns = int(input())
    direction = ""

    if initial_ty < light_y:
        direction += "S"
        initial_ty += 1
    elif initial_ty > light_y:
        direction += "N"
        initial_ty -= 1

    if initial_tx < light_x:
        direction += "E"
        initial_tx += 1
    elif initial_tx > light_x:
        direction += "W"
        initial_tx -= 1

    print(direction)
