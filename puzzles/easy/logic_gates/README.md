# Logic Gates

## Goal

A logic gate is an electronic device implementing a boolean function, performing
a logical operation on one or more binary inputs and producing a single binary
output.

Given **n** input signal names and their respective data, and **m** output
signal names with their respective type of gate and two input signal names,
provide **m** output signal names and their respective data, in the same order
as provided in input description.

All type of gates will always have two inputs and one output. \
All input signal data always have the same length.

The type of gates are:

-   **AND**: performs a logical **AND** operation
-   **OR**: performs a logical **OR** operation
-   **XOR**: performs a logical **exclusive OR** operation
-   **NAND**: performs a logical **inverted AND** operation
-   **NOR**: performs a logical **inverted OR** operation
-   **NXOR**: performs a logical **inverted exclusive OR** operation

Signals are represented with **underscore** and **minus** characters, an
**undescore** matching a low level (0, or false) and a **minus** matching a high
level (1, or true).

## Input

-   Line 1: **n** number of input signals
-   Line 2: **m** number of output signals
-   **n** next lines: two space separated strings: name of input signal, then
    signal form
-   **m** next lines: four space separated strings: name of output signal, then
    type of logic gate, then first input name, then second input name

## Output

-   **m** lines: two space separated strings: name of output signal, then
    signal form

## Constraints

-   1 &leq; **n** &leq; 4
-   1 &leq; **m** &leq; 16
