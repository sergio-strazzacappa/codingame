# Zeckendorf Representation, Part I

## Goal

**Zeckendorf's** theorem asserts that each positive integer can be expressed uniquely as the sum of one or more non-consecutive positive Fibonacci numbers. \
This unique decomposition is called **Zeckendorf representation**.

The **Fibonacci sequence** is an infinite sequence that starts with 0 and 1 then the sum of the previous terms, it goes like this: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

The objective of this puzzle is to output the Zeckendorf representation of a given integer **N**.

**Example**: for **N** = 64: \
The Zeckendorf representation is 64 = 55 + 8 + 1. The output in this case should be 55+8+1

**Note**: \
There are other ways of representing 64 as the sum of Fibonacci numbers

64 = 55 + 5 + 3 + 1 \
64 = 34 + 21 + 8 + 1 \
64 = 34 + 21 + 5 + 3 + 1 \
64 = 34 + 13 + 8 + 5 + 3 + 1

but these are not Zeckendorf representations because 34 and 21 are consecutive Fibonacci numbers, as are 5 and 3.

## Input

**Line 1**: A positive integer **N**

## Output

**Line 1**: Plus-separated non-consecutive Fibonacci numbers whose sum is **N**, sorted in descending order

## Constraints

3 < **N** <= 9007199254740991
