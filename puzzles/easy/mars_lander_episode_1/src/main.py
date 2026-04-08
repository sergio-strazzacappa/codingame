#!/usr/bin/env python3

surface_n = int(input())

for i in range(surface_n):
    land_x, land_y = [int(j) for j in input().split()]

while True:
    x, y, h_speed, v_speed, fuel, rotate, power = [int(i) for i in input().split()]

    if v_speed <= -40:
        power = 4
    else:
        power = 0

    print("0 " + str(power))
