#!/usr/bin/env python3


def distance(x1, y1, x2, y2):
    return ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5


user_lon = float(input().replace(",", "."))
user_lat = float(input().replace(",", "."))
n = int(input())

min_distance = 10000
target = ""

for i in range(n):
    _, name, _, _, lon, lat = input().split(";")
    lon = float(lon.replace(",", "."))
    lat = float(lat.replace(",", "."))

    d = distance(user_lon, user_lat, lon, lat)

    if d < min_distance:
        min_distance = d
        target = name

print(target)
