#! /usr/bin/env python3

while True:
    enemy1, dist1 = input(), int(input())
    enemy2, dist2 = input(), int(input())

    if dist1 < dist2:
        print(enemy1)
    else:
        print(enemy2)
