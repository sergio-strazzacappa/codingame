# Sparse MatMul

## Goal

A long-running process at the national laboratory is hogging up resources on a
supercomputer. You discover that the algorithm is spending most of its time
multiplying zero by zero. This knowledge can be exploited to optimize the code,
saving million of dollars annually and freeing up the supercomputer to play
CodinGame!

The task is to find the product of two sparse matrices **A** and **B**, where
**A** is **M** × **N** and **B** is **N** × **P**. Each entry of the resulting
**M** × **P** matrix is computed as the dot product (or "sum-product") of a row
of **A** and a column of **B**.

<pre style="color:#FFFFFF">
Matrix A      Matrix B              Product
┌───┬───┬───┐ ┌───┬───┬───┲━━━┱───┐ ┌───┬───┬───┬───┬───┐
│   │   │   │ │   │   │   ┃ 5 ┃   │ │   │   │   │   │   │
┢━━━┿━━━┿━━━┪ ├───┼───┼───╂───╂───┤ ├───┼───┼───╆━━━╅───┤
┃ 1 │ 2 │ 3 ┃ │   │   │   ┃ 0 ┃   │ │   │   │   ┃ 8 ┃   │
┡━━━┿━━━┿━━━┩ ├───┼───┼───╂───╂───┤ ├───┼───┼───╄━━━╃───┤
│   │   │   │ │   │   │   ┃ 1 ┃   │ │   │   │   │   │   │
├───┼───┼───┤ └───┴───┴───┺━━━┹───┘ ├───┼───┼───┼───┼───┤
│   │   │   │                 (3×5) │   │   │   │   │   │
└───┴───┴───┘(4×3)                  └───┴───┴───┴───┴───┘(4×5)
</pre>

Because sparse matrices are typically enormous with mostly zero-valued entries,
they are not efficiently treated as sequential row and column data. Instead, you
decide to use a different representation. Each of **countA** elements of matrix
**A** and **countB** elements of matrix **B** are of the form:

**row** **column** **value**

For matrix **A**, the **row** and **column** indicate the entry at **i**, **j**
with the given **value** &ne; **0.0**, while many more entries which will not be
listed all have values equal to zero. For matrix **B**, the **row** and
**column** indicate the entry at **j**, **k** with nonzero **value**.

For a particular row **i** of **A** and a particular column **k** of **B**, the
dot product iterates over **j** to produce the resulting entry at **i**, **k**.
In this way, each value in the final matrix is the sum of pairwise
multiplications… or equivalently, the sum of pairwise multiplications of nonzero
entries.

Provide this product matrix reduced in the same sparse format, ordering elements
first by **row** and then by **column**, and leaving the **value** unrounded
with all significant digits shown. When you receive a thank you call from the
president, it will be time to celebrate your success!

## Input

-   Line 1: Three space-separated integers **M**, **N**, and **P** for the
    matrix dimensions
-   Line 2: Two space-separated integers **countA** and **countB** for the
    number of nonzero entries of **A** and **B**
-   Next **countA** lines: Integers **row** and **column** as indices **i**,
    **j** into **A**, and the decimal **value** for that entry, separated by
    spaces
-   Next **countB** lines: Integers **row** and **column** as indices **j**,
    **k** into **B**, and the decimal **value** for that entry, separated by
    spaces

## Output

-   **For every nonzero entry in the result**: Integers **row** and **column**
    as indices **i**, **k** into the product matrix, and the decimal **value**
    for that entry (e.g. **8.0**), separated by spaces

## Constraints

-   0 &leq; **i** &lt; **N** &lt; 1,000,000
-   0 &leq; **j** &lt; **M** &lt; 1,000,000
-   0 &leq; **k** &lt; **P** &lt; 1,000,000

All sparse matrices are necessarily sorted by **row** first, then by **column**
