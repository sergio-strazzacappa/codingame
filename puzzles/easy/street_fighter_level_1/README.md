# Street Fighter - Level 1

## Goal

Given two champions with list of hits performed by each of them, output who is
the winner and number of hits he strikes on his opponent.

## Rules

-   All champions start with rage = **0**
-   When a champion is hit, his/her rage increases by one
-   When a champion uses special attack, his/her rage restarts at **0**
-   The fight stops when we reach the last line read or when one fighter is dead
    (life &leq; **0**)

In the input, each hit is preceded by the direction of the attack:

-   &gt; means **champion1** hits **champion2**
-   &lt; means **champion2** hits **champion1**

## Example

The table below shows the starting life and the damage caused by punch, kick and
special attack of the champions.

<pre style="color:#FFFFFF">
Champ.|Life|Punch|Kick|Special Attack
KEN   |25  |6    |5   |3*rage
RYU   |25  |4    |5   |4*rage
TANK  |50  |2    |2   |2*rage
VLAD  |30  |3    |3   |2*(rage+opp.rage);opp.rage=0
JADE  |20  |2    |7   |number of hits made*rage
ANNA  |18  |9    |1   |damage received*rage
JUN   |60  |2    |1   |rage; and rage is added to JUN's life
</pre>

| INPUT      | COMMENT                                    |
| ---------- | ------------------------------------------ |
| KEN RYU    | KEN and RYU are fighting                   |
| 4          | total number of hits performed             |
| &lt; KICK  | Ryu kicks Ken, Ken's life decreases by 5   |
| &lt; PUNCH | Ryu punches Ken, Ken's life decreases by 4 |
| &gt; KICK  | Ken kicks Ryu, Ryu's life decreases by 5   |
| &lt; PUNCH | Ryu punches Ken, Ken's life decreases by 4 |
|            | Ryu's life is: 20, Ken's life is: 12       |

**OUTPUT**: Ryu beats Ken in 3 hits

## Input

-   Line 1: **champion1** **champion2** separated by a space where each champion
    is one of: **KEN**, **RYU**, **TANK**, **VLAD**, **JADE**, **ANNA** or
    **JUN**
-   Line 2: **n** is an integer: the total number of hits performed by the
    champions
-   Next **n** Lines: **d** **ATTACK** separated by a space where **d** is &gt;
    or &lt; and gives the direction of the attack; **ATTACK** is one specific
    attack: **PUNCH**, **KICK** or **SPECIAL**

## Output

-   **winner** beats **opponent** in **m** hits

## Constraints

-   **champion1** is always different from **champion2**
-   There is always a winner and a loser. No tie
-   If there is no KO, the winner is the one with more life
