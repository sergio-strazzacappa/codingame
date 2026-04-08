#!/usr/bin/env python3

l = int(input())
h = int(input())
t = input().upper()

dictionary = {
    "A": 0, "B": 1, "C": 2, "D": 3, "E": 4, "F": 5, "G": 6, "H": 7, "I": 8,
    "J": 9, "K": 10, "L": 11, "M": 12, "N": 13, "O": 14, "P": 15, "Q": 16,
    "R": 17, "S": 18, "T": 19, "U": 20, "V": 21, "W": 22, "X": 23, "Y": 24,
    "Z": 25
}

ascii_art = []

for i in range(h):
    row = input()
    ascii_art.append(row)

for i in range(h):
    answer = ""
    for j in range(len(t)):
        char = t[j]

        if char in dictionary:
            index = dictionary[char]
        else:
            index = 26

        answer += ascii_art[i][index * l:(index * l) + l]
    print(answer)
