# Organic Compounds

## Goal

Write a program to input the condensed formula of an alicylic hydrocarbon, and
decide whether it is valid or not.

The condensed formula includes units of carbon linked to one another by one or
more bonds.

1 unit of carbon is represented as **CH**`n`.

The bonds are adjacent to the carbon units, either horizontally or vertically.
Bonds are represented as **(**`m`**)**.

The inputs given will have a valid representation, but the bonds might not be
matching. For example, a carbon unit with `n`=1 should have 3 adjacent bonds,
one with `n`=2 should have 2 adjacent bonds, etc.

_Note: To get a better understanding of organic compounds and condensed
formulae, look it up on the web._

## Input

- **Line 1**: An integer `N`, denoting the number of lines
- **Next** `N` **Lines**: String `COMPOUND` representing the hydrocarbon

## Output

- If the hydrocarbon is valid, a single line **VALID**
- If it is not valid, a single line **INVALID**

## Constraints

- 1 &leq; `N` &leq; 20
- In carbon units, 0 &leq; `n` &leq; 4
- In bonds, 0 &lt; `m` &leq; 4
