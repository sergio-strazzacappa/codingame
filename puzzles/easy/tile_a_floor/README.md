# Tile A Floor

## Goal

You are a manufacturer and installer of Floor-Tiles.

The beauty of Tiles comes from their symmetry, in that the quadrants of a Tile
are mirror/reflections of each other.

So, when you get an order for a Tile, only the pattern of the top left quadrant
(plus a little more, so you can see the center characters) are the input.
Graphically explained here:

<pre style="color:#FFFFFF">
☑☑☑☐☐
☑☑☑☐☐
☑☑☑☐☐
☐☐☐☐☐
☐☐☐☐☐
</pre>

From that limited input, your task is to:

-   Create a full Tile
-   And display a 2x2 floor (i.e., a floor consisting of 4 of those Tiles)

## Details

-   Each Tile is a square; the input therefore is also a square
-   The input square shows the **top left** character of the full Tile, all the
    way to the **middle character** of the full Tile
-   The input has a side-length of **N**; therefore the full Tile has a
    side-length of 2**N**-1
-   The full floor needs a grout border, and grout separating the individual
    Tiles. Grout is represented by **-** on top/bottom, **|** on left/right, and
    **+** on corners

## Flip/Mirrors Patterns

Generally, a character appearing in the first quadrant just replicates in the
other quadrants.

However, for these special characters, you will need to sometimes print the
opposite-mate of it:

-   () {} [] &lt; &gt;: If any of these are on the left side, then show its
    opposite-mate on the right side
-   ^v AV wm WM un: If any of these are on the top half, then show its
    opposite-mate on the bottom half
-   /\\: If either of these is on the top left quadrant, then show its
    opposite-mate on the two adjacent quadrants

_The opposite-mate is the one beside it in the character-pair as shown_

## Input

-   Line 1: An integer **N**, denoting the number of rows of partial Tile
    pattern
-   Next **N** lines: row of partial Tile pattern

## Output

-   The entire floor

## Constraints

-   3 &leq; **N** &leq; 7
