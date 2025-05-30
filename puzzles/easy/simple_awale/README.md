# Simple Awalé

## Goal

**Awalé** is an african 2 players game consisting of moving grains in some
bowls. Each player has 7 bowls indexed from 0 to 6. The last bowl is the
reserve.

At each turn a player chooses one of his own bowls except the reserve, picks up
all grains there and redistributes them one by one to bowls beginning just after
the chosen one. If the number of grains in hand is sufficient, after adding one
to his reserve the player continues the distribution in the opponent's bowls
excluding his reserve and then back in his own bowls, until his hand is empty.

If the final grain is distributed to the player's reserve, he is allowed to play
again.

### Examples

<pre style="color:#FFFFFF">
bowls num : 0 1 2 3 4 5  6
--------------------------
opp bowls : 5 1 0 6 2 2 [3]
 my bowls : 3 4 0 3 3 2 [2]


I play bowl 0: distribute 3 grains in bowl 1, 2 and 3
bowls num : 0 1 2 3 4 5  6
--------------------------
opp bowls : 5 1 0 6 2 2 [3]
 my bowls : 0 5 1 4 3 2 [2]


I play bowl 5: distribute 2 grains (1 in my reserve and 1 in the first opponent
bowl)
bowls num : 0 1 2 3 4 5  6
--------------------------
opp bowls : 6 1 0 6 2 2 [3]
 my bowls : 3 4 0 3 3 0 [3]


If I end in my reserve I can replay:
I play bowl 3:
bowls num : 0 1 2 3 4 5  6
--------------------------
opp bowls : 5 1 0 6 2 2 [3]
 my bowls : 3 4 0 0 4 3 [3]
REPLAY
</pre>

Your goal is to simulate your turn of game. Given the numbers of grains in each
bowl and the **num** of the chosen bowl your program has to display the new
situation and the string **REPLAY** if the player has a chance to play again.
Print the numbers of grains of opponent bowls separated by space, then yours.
Put reserve counts between brackets.

Remember that the player always skips the opponent's reserve when distributing!

## Input

**Line 1**: **opBowls** a string of numbers of grains in each opponent bowls
separated by spaces \
**Line 2**: **myBowls** a string of numbers of grains in each of my bowls
separated by spaces \
**Line 3**: **num** the index of chosen bowl

## Output

**Line 1**: a string of numbers of grains in each opponent bowls separated by
spaces \
**Line 2**: a string of numbers of grains in each of my bowls separated by
spaces \
If the same player gets to play again: \
**Line 3**: **REPLAY**

## Constraints

0 &leq; num &lt; 6
