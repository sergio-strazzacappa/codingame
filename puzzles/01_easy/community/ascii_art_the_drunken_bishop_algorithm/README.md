# ASCII Art The Drunken Bishop Algorithm

## Goal

Have you ever wondered how the OpenSSH Random Art is produced?

They used _The Drunken Bishop algorithm_, designed by Alexander von Gernler.

_Bishop Peter finds himself in the middle of an ambient atrium. There are walls
on all four sides and apparently there is no exit. The floor is paved with
square tiles, strictly alternating between black and white. His head heavily
aching—probably from too much wine he had before—he starts wandering around
randomly. Well, to be exact, he only makes diagonal steps—just like a bishop on
a chess board. When he hits a wall, he moves to the side, which takes him from
the black tiles to the white tiles (or vice versa). And after each move, he
places a coin on the floor, to remember that he has been there before. After 64
steps, just when no coins are left, Peter suddenly wakes up. What a strange
dream!_

The algorithm is well described in the document _The drunken bishop: An
analysis of the OpenSSH fingerprint visualization algorithm_ (link in
reference).

To summarize, OpenSSH uses MD5 to generate a 128 bits fingerprint for the
server's key, for example in hexadecimal:

**fc:94:b0:c1:e5:b0:98:7c:58:43:99:76:97:ee:9f:b7**

You should create a chess board 17x9 (origin _(0,0)_ at top left corner) and
place a Bishop (the letter **S**) at the center (position _(8,4)_).

<pre style="color:#FFFFFF">
            1111111
  01234567890123456
 +---[CODINGAME]---+ x
0|                 |
1|                 |
2|                 |
3|                 |
4|        S        |
5|                 |
6|                 |
7|                 |
8|                 |
 +-----------------+
 y
</pre>

Then, break the 128 bit fingerprint in input into pairs of bits that define 4
possible moves:

-   00: up-left (↖ North West)
-   01: up-right (↗ North East)
-   10: down-left(↙ South West)
-   11: down-right (↘ South East)

During the 64 steps of the algorithm, the bit pairs are processed byte-wise,
from left to right and least significant bits first.

**Example**: The fingerprint **FC:94**

<pre style="color:#FFFFFF">
      F     C       9     4   ...
    11 11 11 00 : 10 01 01 00 ...
     |  |  |  |    |  |  |  |
Step 4  3  2  1    8  7  6  5
</pre>

For each pair of bits in the input we move the bishop one space on the board
and increment a counter recording how many times we visit each square. Instead
of moving off the board at the edges, the bishop slides along the sides as if
they were walls. For example, if the bishop is on the right edge of the board
and the next move is 01, we simply slide the bishop one space vertically up,
incrementing the counter on the new square as normal. If the Bishop ends up at a
corner and he cannot slide, he simply does not move (and we should increment
counter for that corner cell). Here the four cases:

  <pre style="color:#FFFFFF">
Position     | bit pair | action
-------------+----------+--------
top left     | 00       | no move
top right    | 01       | no move
bottom left  | 10       | no move
bottom right | 11       | no move
</pre>

At the end of the 64 steps, the board is drawn assigning a symbol to each
position on the board according to how many times it was visited. OpenSSH uses
these symbols:

<pre style="color:#FFFFFF">
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
  . o + = * B O X @ %  &  #  /  ^
</pre>

We apply the wrap-around logic if the number of times visited is greater than
14, e.g. we use **o** if a position is visited for 17 times.

The special values **S** and the end value **E** mark the start and end position
of the walk and overwrite the real value of the respective position. Surround
the chessboard with **+** for corners, **-** for top and bottom edges and **|**
for left and right edges. Put **[CODINGAME]** at center in the top edge.

References:

-   http://www.dirk-loss.de/sshvis/drunken_bishop.pdf
-   https://www.jfurness.uk/the-drunken-bishop-algorithm/
-   https://dev.to/krofdrakula/improving-security-by-drawing-identicons-for-ssh-keys-24mc

## Input

-   Line 1: Server fingerprint string format as group of 2 hexadecimal digit
    separated by **:**

## Output

-   11 lines: Random ASCII Art

## Constraints

-   The input string is always 16 bytes (separated by **:**), so there are exactly
    64 steps that can be produced by the input string
