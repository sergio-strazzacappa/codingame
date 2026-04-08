#! /usr/bin/env python3

from collections import deque

expression = input()

d = deque()

for char in expression:
    if char in "([{":
        d.append(char)
        continue
    else:
        top = ""
        match char:
            case ")":
                top = "("
            case "]":
                top = "["
            case "}":
                top = "{"
            case _:
                continue

        if len(d) > 0 and top == d[-1]:
            d.pop()
        else:
            print("false")
            exit()

if len(d) == 0:
    print("true")
else:
    print("false")
