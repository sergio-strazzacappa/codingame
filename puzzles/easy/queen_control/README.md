# Queen Control

## Goal

Chess is played on an 8x8 board composed of 64 squares. In this game it is
important to **control** a large amount of these squares to gain the upper hand
on the opponent. A square is said to be controlled when it is in the range of
movement of a chess piece.

The chess piece that can control the most squares is **the queen**. It can move
on any square vertically, horizontally and diagonally.

**Your mission**: Create a program able to calculate the number of squares
controlled by the queen in a specific given position.

A square is considered to be controlled when the queen can move to it.

-   A square containing a piece of the same **color** isn't considered
    controlled
-   But a square containing a piece of the opposite color can be considered
    controlled
-   The square the queen is currently on isn't counted

## Input

-   Line 1: The **color** of the queen (white or black)
-   Next 8 lines: A string **line** of 8 characters describing the chess board
    -   **.** = Empty square
    -   **Q** = The queen
    -   **w** = White piece
    -   **b** = Black piece

## Output

-   Line 1: An integer corresponding to the number of squares controlled by the
    queen

## Constraints

-   None
