# Container Terminal

## Goal

Cargo trucks are transporting containers due for export to a seaport terminal.

The containers will be temporarily stored in the terminal to wait for ships to
come. To save space, containers are usually stacked up in the terminal.

There are different ships bound for different destinations. Terminal operators
have to pick the correct containers from temporary storage to load onto the
ships. If the correct containers are on the top of the stack, it will be easy to
pick them up for loading. But if a wanted container is underneath some other
containers, the overlaying containers must first be moved aside before reaching
the wanted container, causing extra operation cost and wasting time.

To manage the container terminal in the most efficient manner, you need a plan.

There are ship A to ship Z, totally 26 different ships bound for 26 different
destinations.

You know the schedule of the ships. Ship A will come earlier than Ship B. Ship B
will come earlier than Ship C. The ships always come in alphabetical order.

You know the schedule of the cargo trucks. The containers for different ships
are arriving in a predictable order. No cargo owner wishes to miss a shipment.
All cargoes will arrive before the first ship to come.

You have to plan when the trucks come, how should the containers be stored.

## Example

Six trucks are sending six containers to the terminal in this order:

**BACCBA**

-   B is a container for ship B. This container comes first
-   It is followed by container A, targeted for ship A
-   A is followed by two containers C, to be loaded to ship C
-   ... and so on for the rest

We can arrange the six containers in two stacks, like this:

<pre style="color:#FFFFFF">
 ___ ___
| A | B |
|___|___|
| A | C |
|___|___|
| B | C |
|___|___|
</pre>

-   When ship A comes, we can pick up the two uppermost A containers to load to
    the ship
-   When ship B comes, the two B containers are on the uppermost layer easy to
    pick up
-   When ship C comes, the remaining two C containers are ready for pick up and
    loading

The whole process used 2 stacking areas.

Note that we do not sort the containers before stacking them up. Sorting is an
option too slow and costly to put into practice.

Now is your turn. You are given the cargo trucks schedule. Find the minimum
stacking areas needed to ensure the most efficient shipment loading, have the
wanted containers always on the top.

## Input

-   Line 1: An integer **N** for the number of lines to follow
-   The following **N** lines: each line is an independent test case, which is a
    string composed of alphabetical upper case letters. Each letter refers to a
    container targeted for its same-letter ship. The cargoes will be transported
    to the terminal strictly in the order shown in the string. Process each line
    as an independent case

## Output

-   Write **N** lines, each line is an integer, which is the answer for its
    corresponding input line

## Constraints

-   1 &leq; **N** &leq; 100
-   1 &leq; length of each line &leq; 500 characters
-   In the real world there is a maximum height limit for each stack of
    containers. In this puzzle we assume there is no such limit
