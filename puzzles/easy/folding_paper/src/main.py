#! /usr/bin/env python3

order   = input()
side    = input()

index = -1
folds = [1, 1, 1, 1]

for c in order:
    if c == 'U':
        index = 0
    if c == 'R':
        index = 1
    if c == 'D':
        index = 2
    if c == 'L':
        index = 3

    folds[(index + 1) % 4] *= 2
    folds[(index + 3) % 4] *= 2
    folds[(index + 2) % 4] += folds[index]
    folds[index] = 1

if side == 'U':
    index = 0
if side == 'R':
    index = 1
if side == 'D':
    index = 2
if side == 'L':
    index = 3

print(folds[index])
