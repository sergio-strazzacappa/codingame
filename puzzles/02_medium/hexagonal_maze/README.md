# Hexagonal Maze

## Goal

You are in a maze, made of hexagonal cells.

The following grid:

<pre style="color:FFFFFF">
4 4
ABCD
EFGH
IJKL
MNOP

Has to be understood like this:

  / \   / \   / \   / \
 /   \ /   \ /   \ /   \
|     |     |     |     |
|  A  |  B  |  C  |  D  |    Line 0
|     |     |     |     |
 \   / \   / \   / \   / \
  \ /   \ /   \ /   \ /   \
   |     |     |     |     |
   |  E  |  F  |  G  |  H  | Line 1
   |     |     |     |     |
  / \   / \   / \   / \   /
 /   \ /   \ /   \ /   \ /
|     |     |     |     |
|  I  |  J  |  K  |  L  |    Line 2
|     |     |     |     |
 \   / \   / \   / \   / \
  \ /   \ /   \ /   \ /   \
   |     |     |     |     |
   |  M  |  N  |  O  |  P  | Line 3
   |     |     |     |     |
    \   / \   / \   / \   /
     \ /   \ /   \ /   \ /
</pre>

This means each cell has 6 neighbours: for example, cell _F_ is surrounded by
_B_, _C_, _E_, _G_, _J_, _K_.

The grid is periodic, if you go left you appear on the right if there is no
wall, and vice versa, similarly with up/down.

So cell _B_ also has 6 neighbours: _M_, _N_, _A_, _C_, _E_, _F_.

Even lines are left-aligned, odd lines are right-aligned.

You are given a grid made by walls and free spaces, you have to draw the
shortest path to go from the start to the end.

There may be more than one path, but only one shortest path.

There is always a solution.

The grid contains following symbols:

-   #: wall
-   \_: free space
-   S: start
-   E: end

You must output the same grid with symbols **.** on cells which are on the
shortest way.

## Input

-   First line: two integers **w** and **h**, width and height of the grid
-   **h** following lines: the grid

## Output

-   **h** lines: the grid with the answer

## Constraints

-   4 &leq; **w**, **h** &leq; 25
-   **h** is always even
