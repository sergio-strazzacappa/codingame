# Nature Of Quadrilaterals

## Goal

You have to print the nature of the quadrilaterals whose vertices’ coordinates
are given.

The nature can be:

- Nothing, in which case you should write _quadrilateral_
- Parallelogram (opposite sides are parallel to each other)
- Rhombus (all four sides are equal)
- Rectangle (all four angles are right)
- Square (it is a rectangle and a rhombus)

## Input

- **Line 1**: The number of quadrilaterals (`n`)
- **Next** `n` **lines**: Each vertex followed by its coordinates, one
  quadrilateral per line. In the format:
  `A` `xA` `yA` `B` `xB` `yB` `C` `xC` `yC` `D` `xD` `yD`

## Output

- The name of the quadrilateral followed by its nature. For example:
  ABCD is a rhombus.
  DEFA is a quadrilateral.
  The vertices are printed in the given order. Note that ABCD, ABDC and ACBD are
  three distinct quadrilaterals. Just follow the order of the vertices.

## Constraints

- The coordinates are integers between -20 and 20, you have no more than 3
  quadrilaterals
- You won’t have to test if a quadrilateral is degenerate or convex
