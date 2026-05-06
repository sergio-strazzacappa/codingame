# Shadow Of The Knight - Episode 1

## The Goal

You will look for the hostages on a given building by jumping from one window to
another using your grapnel gun. Your goal is to jump to the window where the
hostages are located in order to disarm the bombs. Unfortunately, you have a
limited number of jumps before the bombs go off...

## Rules

Before each jump, the heat-signature device will provide you with the direction
of the bombs based on your current position:

-   **U** (Up)
-   **UR** (Up-Right)
-   **R** (Right)
-   **DR** (Down-Right)
-   **D** (Down)
-   **DL** (Down-Left)
-   **L** (Left)
-   **UL** (Up-Left)

Your mission is to program the device so that **it indicates the location of the
next window you should jump to** in order to reach the bombs' room **as soon as
possible**.

Buildings are represented as a rectangular array of windows, the window in the
**top left corner of the building is at index (0,0)**.

## Note

For some tests, **the bombs' location may change from one execution to the
other:** the goal is to help you find the best algorithm in all cases.

The tests provided are similar to the validation tests used to compute the final
score but remain different.

## Game Input

The program must first read the initialization data from standard input. Then,
within an infinite loop, read the device data from the standard input and
provide to the standard output the next movement instruction.

### Initialization Input

-   Line 1: 2 integers **W** **H**. The (**W**, **H**) couple represents the
    width and height of the building as a number of windows
-   Line 2: 1 integer **N**, which represents the number of jumps you can make
    before the bombs go off
-   Line 3: 2 integers **X0** **Y0**, representing your starting position

### Input For One Game Turn

-   The direction indicating where the bomb is

## Output For One Game Turn

-   A **single line** with 2 integers **X** **Y** separated by a space
    character. (**X**, **Y**) represents the location of the next window you
    should jump to. **X** represents the index along the horizontal axis, **Y**
    represents the index along the vertical axis. (0,0) is located in the
    top-left corner of the building

## Constraints

-   1 &leq; **W** &leq; 10000
-   1 &leq; **H** &leq; 10000
-   2 &leq; **N** &leq; 100
-   0 &leq; **X**, **X0** &lt; **W**
-   0 &leq; **Y**, **Y0** &lt; **H**
-   Response time per turn &leq; 150ms
