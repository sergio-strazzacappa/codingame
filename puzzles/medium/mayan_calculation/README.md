# Mayan Calculation

## The Goal

Upon discovering a new Maya site, hundreds of mathematics, physics and astronomy
books have been uncovered.

The end of the world might arrive sooner than we thought, but we need you to be
sure that it doesn't!

Thus, in order to computerize the mayan scientific calculations, you're asked to
develop a program capable of performing basic arithmetical operations between
two mayan numbers.

## Rules

The mayan numerical system contains **20** numerals going from **0** to **19**.
Here's an ASCII example of their representation:

<pre style="color:#FFFFFF">
0:  .oo.
    o..o
    .oo.
    ....

1:  o...
    ....
    ....
    ....

2:  oo..
    ....
    ....
    ....

3:  ooo.
    ....
    ....
    ....

4:  oooo
    ....
    ....
    ....

5:  ....
    ----
    ....
    ....

6:  o...
    ----
    ....
    ....

7:  oo..
    ----
    ....
    ....

8:  ooo.
    ----
    ....
    ....

9:  oooo
    ----
    ....
    ....

10: ....
    ----
    ----
    ....

11: o...
    ----
    ----
    ....

12: oo..
    ----
    ----
    ....

13: ooo.
    ----
    ----
    ....

14: oooo
    ----
    ----
    ....

15: ....
    ----
    ----
    ----

16: o...
    ----
    ----
    ----

17: oo..
    ----
    ----
    ----

18: ooo.
    ----
    ----
    ----

19: oooo
    ----
    ----
    ----
</pre>

A mayan number is divided into vertical sections. Each section contains a
numeral (from 0 to 19) representing a power of 20. The lowest section
corresponds to 20^0, the one above to 20^1 and so on.

Thereby, the example below is: (12 x 20 x 20) + (0 x 20) + 5 = 4805

<pre style="color:#FFFFFF">
12 X 20^2   oo..
            ----
            ----
            ....

0 X 20^1    .oo.
            o..o
            .oo.
            ....

5 X 20^0    ....
            ----
            ....
            ....
</pre>

To spice the problem up, the mayans used several dialects, and the graphical
representation of the numerals could vary from one dialect to another.

The representation of the mayan numerals will be given as the input of your
program in the form of ASCII characters. You will have to display the result of
the operation between the two given mayan numbers. The possible operations are
**\***, **/**, **+**, **-**.

## Game Input

### Input

-   Line 1: the width **L** and height **H** of a mayan numeral
-   **H** next lines: the ASCII representation of the **20** mayan numerals.
    Each line is (**20** x **L**) characters long
-   Next line: the amount of lines **S1** of the first number
-   **S1** next lines: the first number, each line having **L** characters
-   Next line: the amount of lines **S2** of the second number
-   **S2** next lines: the second number, each line having **L** characters
-   Last line: the operation to carry out: **\***, **/**, **+**, or **-**

### Output

-   The result of the operation in mayan numeration, **H** lines per section,
    each line having **L** characters

### Constraints

-   0 &lt; **L**, **H** &lt; 100
-   0 &lt; **S1**, **S2** &lt; 1000
-   The remainder of a division is always 0
-   The mayan numbers given as input will not exceed 2^63
