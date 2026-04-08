#! /usr/bin/env python3


def draw(n, symbol):
    for _ in range(n):
        print(symbol, end="")


n = int(input())
position = n * 2 - 1

# Draw the top triangle
for i in range(n):
    start = 0

    if i == 0:
        print(".", end="")
        start += 1

    draw(position - start, " ")
    draw(2 * i + 1, "*")
    print()
    position -= 1

# Draw the bottom rectangles
for i in range(n):
    draw(position, " ")
    draw(2 * i + 1, "*")
    draw(n * 2 - i * 2 - 1, " ")
    draw(2 * i + 1, "*")
    print()
    position -= 1
