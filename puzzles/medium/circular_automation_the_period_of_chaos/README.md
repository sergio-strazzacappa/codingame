# Circular Automation, The Period Of Chaos

## Goal

In mathematics and computability theory, an elementary cellular automaton is a
one-dimensional cellular automaton where there are two possible states (labeled
0 and 1) and the rule to determine the state of a cell in the next generation
depends only on the current state of the cell and its two immediate neighbors.

## The Numbering System

There are **2^3=8** possible configurations for a cell and its two immediate
neighbors. The rule defining the cellular automaton must specify the
resulting state for each of these possibilities so there are **2^(2^3)=256**
possible elementary cellular automates. Stephen Wolfram proposed a scheme,
known as the Wolfram code, to assign each rule a number from 0 to 255 which has
become standard. Each possible current configuration is written in order, 111,
110, ..., 001, 000, and the resulting state for each of these configurations is
written in the same order and interpreted as the binary representation of an
integer. This number is taken to be the rule number of the automaton. For
example, 110 (base 10)=01101110 (base 2). So rule 110 (ruleNumber) is defined
by the transition rule:

<pre style="color:#FFFFFF">
=================================
|111|110|101|100|011|010|001|000|
| 0 | 1 | 1 | 0 | 1 | 1 | 1 | 0 |
=================================
</pre>

You can find similar a puzzle in coding game here:
https://www.codingame.com/training/medium/elementary-cellular-automaton

More information about elementary cellular automaton can be found here:
http://mathworld.wolfram.com/ElementaryCellularAutomaton.html

## Statement

Based on **lineLength** an odd number, start with a line with 1 in the middle
and fill all the rest with '.' char. \
'.' character represent the 0 value, it is used to make the display more readable. \
'1' character represent the 1 value.

### Example

line_length = 1 : 1 for 1 \
line_length = 3 : .1. for 010 \
line_length = 5 : ..1.. for 00100

For this exercise, we connect the two extremities of the line, think about a
motif that will be displayed over an infinite cylinder. \
The left cell of the first cell is the last cell. \
The right cell of the last cell is the first cell. \
Then repeat the transformation to the current line till you find a repetition
scheme, a line that was already outputted before. \
Since same line will always provide same output, we can be sure that a
repetition period exist and this period is less or equal to
**2^(lineLength) + 1**.

## Goal

Output the repetition period (the number of iteration separating two matching
patterns), if the number of iteration comes greater than **maxIter** and no
solution was found yet, output _BIG_.

### Example 1

- **lineLength** = 5
- **maxIter** = 20000
- **ruleNumber** = 254

The lines will be like that:

<pre style="color:#FFFFFF">
..1..
.111.
11111
11111
</pre>

After the second line, the lines stay the same forever the the repetition
period is then 1.

### Example 2

- **lineLength** = 5
- **maxIter** = 20000
- **ruleNumber** = 1

The lines will be like that:

<pre style="color:#FFFFFF">
..1..
1...1
..1..
</pre>

Period is 2.

## Bonus

Display each line of iteration inside the error stream to better understand how
the chaos can emerge from a simple defined problem.

## Input

**Line 1**: **lineLength** the length of the line to repeat \
**Line 2**: **maxIter** maximum number of iteration \
**Line 3**: **ruleNumber** the rule number

## Output

The repetition period or _BIG_ if no period can be found after
**maxIteriterations**

## Constraints

**lineLength** is odd and &lt; 500 \
**maxIter** &leq; 50000 \
0 ≤ **ruleNumber** &leq; 255
