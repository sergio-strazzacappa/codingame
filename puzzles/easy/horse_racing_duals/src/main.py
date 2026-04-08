#!/usr/bin/env python3

n = int(input())
horses = []

for i in range(n):
    p = int(input())
    horses.append(p)

horses.sort()
min_diff = 99999

for i in range(len(horses) - 1):
    diff = horses[i + 1] - horses[i]

    if diff < min_diff:
        min_diff = diff

print(min_diff)
