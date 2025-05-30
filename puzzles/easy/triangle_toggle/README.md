# Triangle Toggle

## Goal

Create a rectangular grid of **\*** such that the top left point is always **(0, 0)** (and coordinates increase along the X-axis and the Y-axis); and the height and width are **HI** and **WI**.

This grid will have a style of either **expanded** or **condensed**:

-   if **expanded**, add a space between **\***'s in each row.
-   if **condensed**, do not.

Carve out triangles from that grid. If part (or all) of a triangle is already carved out, then add those parts back, thus _Triangle Toggle_.

**Note**:

-   _carve out_ means replacing each **\*** in the triangle (its edges and its inside) with a space character.
-   A triangle is sometimes not fully on the grid, but at least some of it is.

## Input

**Line 1**: 2 integers: **HI** **WI** space-separated \
**Line 2**: a string **style** that is either **condensed** or **expanded** \
**Line 3**: an integer **howManyTriangles** to show how many Triangles you will carve \
**Next** **howManyTriangles** **Lines**: 6 space-separated integers representing a single triangle, **X1** **Y1** **X2** **Y2** **X3** **Y3**. Each pair of **X** and **Y** represents the X and Y-coordinates of one vertex of the triangle.

## Output

**HI** **Line**s: The carved out grid.

## Constraints

5 < **HI**, **WI** < 50 \
0 < **howManyTriangles** < 10 \
-20 < every **X**, every **Y** < 70
