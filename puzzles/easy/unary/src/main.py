#!/usr/bin/env python3

message = input()
binary = map(int, "".join(format(ord(c), "07b") for c in message))

last = -1
for bit in binary:
    if bit == last:
        print("0", end="")
    elif last == -1 and bit == 0:
        print("00 0", end="")
    elif last == -1 and bit == 1:
        print("0 0", end="")
    elif bit == 0:
        print(" 00 0", end="")
    else:
        print(" 0 0", end="")
    last = bit
print()
