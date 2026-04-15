# Horse-racing Hyperduals

## Goal

Casablanca’s hippodrome has grown tired of old-fashioned dual racing and has
kicked it up a notch: they will now be organizing hyperduals.

During a hyperdual, only two horses will participate in the race. In order for
the race to be interesting, it is necessary to try to select two horses with
similar strength.

Write a program which, using a given number of strengths, identifies the two
closest strengths and shows their difference with an integer.

In a hyperdual, a horse's strength is a bidimensional `(Velocity,Elegance)`
vector. The distance between two strengths `(V1,E1)` and `(V2,E2)` is
`abs(V2-V1)+abs(E2-E1)`.

_(This is a harder version of training puzzle **Horse-racing duals**. You may
want to solve that problem first. To date there is no specific achievement if
you solve this one in pure bash. Rest assured it is possible nonetheless!)_

## Input

- **Line 1**: the number `N` of horses
- `N` **following lines**: the speed `V` and elegance `E` of each horse,
  space-separated

## Output

- **Line 1**: the distance `D` between the two closest strengths

## Constraints

- 10 &leq; `N` &leq; 600
- 0 &leq; `V`, `E` &leq; 10000000
- `D` &leq; 0
- All values are integral
