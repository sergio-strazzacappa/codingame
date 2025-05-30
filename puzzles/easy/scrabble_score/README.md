# Scrabble Score

## Goal

-   Given the tile set, with the tile scores
-   Given the board, with double/triple letter/word score cells
-   Given the board with words already played
-   Given the updated board with the word you have just played

You have to compute how many points you scored by playing this word.

## How to compute your score

There are 4 kinds of special cells:

-   **l** (lower L): multiply by 2 the score of the tile
-   **L**: multiply by 3 the score of the tile
-   **w**: multiply by 2 the score of the entire word
-   **W**: multiply by 3 the score of the entire word

The score is calculated by first summing up the scores of the tiles. If any tile
just played falls on **l** / **L**, the score of that tile is doubled/tripled
before summing up. After the sum is found, apply the **w** / **W** multipliers
to the sum if any tile just played falls on those cells, and you get the final
score.

If you play on several **w** or **W**, the multipliers are applied successively.

There are enough test cases to illustrate how scoring works in practice.

More details about the real scrabble game here:

-   https://en.wikipedia.org/wiki/Scrabble
-   https://fr.wikipedia.org/wiki/Scrabble

## Input

-   First line: the number of characters **nbTiles** in the tile set
-   **nbTiles** following lines: a character and an integer, which is the
    associated score, space separated. The character may or may not be a letter
-   Next line: **width** and **height** of the board, space separated
-   **height** following lines: the empty board with double letter score **l**,
    triple letter score **L**, double word score **w**, triple word score **W**,
    or normal cell **.**
-   **height** following lines: the board with words already played (characters
    in the tile set, or **.** for empty cell)
-   **height** following lines: the board with words already played and the word
    you've just played (characters in the tile set, or **.** for empty cell)

## Output

-   **As many lines as necessary, in lexicographical order**: Each new word with
    associated score, space separated
-   **One more line**: **Bonus 50** if 7 new tiles are played
-   **Last line**: **Total** followed by a space and the total points scored

## Constraints

-   2 &leq; **nbTiles** &leq; 30
-   4 &leq; **width**, **height** &leq; 15
-   There are at least 1 and at most 7 new tiles played
-   All new tiles are lined up
-   At least 1 new tile is near a previously played tile
-   There won't be two identical new words
