# Asteroids

## Goal

You have been tasked with studying a region of space to detect potentially
dangerous asteroids.

You are given two pictures of the night sky of dimensions **W** **\*** **H**,
taken at two different times **t1** and **t2**.

For your convenience, asteroids have been marked with capital letters **A** to
**Z**, the rest is empty space represented by a **dot** (**.**).

Using the information contained in those two pictures, determine the position of
the asteroids at **t3**, and output a picture **of the same region of the sky**.

If necessary, the final coordinates are to be **rounded-down** (floor).

Asteroids travel at different altitudes (with **A** being the closest and **Z**
the farthest from your observation point) and therefore cannot collide with each
other during their transit.

If two or more asteroids have the same final coordinates, output **only the
closest one**.

It is guaranteed that all asteroids at **t1** will still be present at **t2**,
that **no asteroids are hidden** in the given pictures, and that there is only
**one asteroid per altitude**.

**NB**: Because of the flooring operation, it is important that you choose a
coordinate system with the origin at the top left corner and the y axis
increasing in the downward direction.

## Input

-   Line 1: five ints separated by a space, **W** **H** **t1** **t2** **t3**
-   Next **H** lines: a row of picture 1 and picture 2, separated by a white
    space

## Output

-   **H** lines: the state of the sky at **t3**

## Constraints

-   0 &lt; **W** &leq; **H** &leq; 20
-   0 &leq; **t1** &lt; **t2** &leq; **t3** &leq; 10000
