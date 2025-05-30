# Folding Paper

## Goal

A sheet of paper is folded several times. The goal is to determine how many
layers of paper are visible from one side of the obtained folding.

Folding motions are:

-   **R** for Right: take the right side and fold it on the left side
-   **L** for Left: take the left side and fold it on the right side
-   **U** for Up: take the high side and fold it on the low side
-   **D** for Down: take the low side and fold it on the high side

## Input

-   Line 1: a fold string **order**: several letters **R**, **L**, **U** and
    **D** with no space in-between
-   Line 2: **side**: a single character **R**, **L**, **U** or **D**

## Output

-   **n**: the number of layers of paper visible from **side**

## Constraints

-   2 characters &leq; length of **order** &leq; 8 characters (Try to fold a
    sheet more than 6 times!)
