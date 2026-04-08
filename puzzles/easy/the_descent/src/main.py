#!/usr/bin/env Python3

while True:
    highest_peak = 0
    highest_index = 0

    for i in range(8):
        mountain_h = int(input())

        if mountain_h > highest_peak:
            highest_peak = mountain_h
            highest_index = i

    print(highest_index)
