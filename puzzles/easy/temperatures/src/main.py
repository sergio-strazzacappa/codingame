#!/usr/bin/env python3

n = int(input())

if n == 0:
    print(0)
    exit(0)

temps = list(map(int, input().split()))
closest_temp = temps[0]

for t in temps:
    if abs(t) < abs(closest_temp):
        closest_temp = t
    elif t == abs(closest_temp):
        closest_temp = abs(t)

print(closest_temp)
