# Horse-racing Duals

## The Goal

Casablanca's Hippodrome is organizing a new type of horse racing: duals. During
a dual, only two horses will participate in the race. In order for the race to
be interesting, it is necessary to try to select two horses with similar
strength.

Write a program which, using a given number of strength, identifies the two
closest strengths and shows their difference with an integer (&geq; 0).

## Game input

### Input

- **Line 1**: number `N` of horses
- **The** `N` **following lines**: the strength `P` of each horse. `P` is an
  integer

## Output

- The difference `D` between the two closest strengths. `D` is an integer
  greater or equal to 0

## Constraints

- 1 &lt; `N` &lt; 100000
- 0 &lt; `P` &lt; 10000000
