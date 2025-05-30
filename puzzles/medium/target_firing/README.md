# Target Firing

## Goal

### Story

Your spaceship is under attack by aliens! (It's actually your friend's
spaceship, so the situation is even worse) Luckily your spaceship is equipped
with an antimatter beam, while the aliens only have cheap (but still dangerous)
laser pointers. Can you destroy all alien spaceships safely, or should you flee?

### Prompt

As the AI within the ship's computer, your goal is to **determine the optimal
order of alien spaceships to destroy** such that you leave the encounter with
the maximum strength of your shields. **Print the remaining strength of the
shields**, or **FLEE** if your spaceship is predicted to take more damage than
your shields can handle. Your friend will not forgive you if the ship is
damaged.

### Details

The encounter can be modeled by turn-based combat. Your spaceship's shields
begin with **5000** strength. You are fighting against **N** alien spaceships of
various properties. These properties are:

-   **SHIP** - the type of the spaceship, which can be either **FIGHTER** or
    **CRUISER**
-   **HP** - the amount of damage the spaceship can receive before being
    destroyed
-   **ARMOR** - the damage reduction of the spaceship
-   **DAMAGE** - the amount of damage the spaceship deals per turn

On each turn, all alien spaceships reduce your ship's shields by **DAMAGE** as
your antimatter beam charges, and then one spaceship takes damage from your
antimatter beam. Your beam deals **10** base damage to a spaceship. The actual
damage that the spaceship receives is decreased by the spaceship's **ARMOR**.
Luckily, your antimatter beam does double damage to **FIGHTER**-class
spaceships; hence, the damage that **FIGHTER**-class spaceships receives is
**20 - ARMOR**. Your antimatter beam always deals at least **1** damage, even if
the target spaceship's **ARMOR** is greater than your beam's damage.

## Input

-   Line 1: An integer **N** for the number of alien spaceships
-   Next **N** lines: One string followed by three integers, space-separated,
    representing the **SHIP** type, **HP**, **ARMOR**, and **DAMAGE** of the
    alien spaceship

## Output

-   An integer representing the maximum strength of shields left after an
    optimal encounter, or **FLEE** if your spaceship will take hull damage
    (shield strength &lt; 0)

## Constraints

-   2 &leq; **N** &leq; 50
-   1 &leq; **HP**, **DAMAGE** &lt; 1000
-   0 &leq; **ARMOR** &lt; 50
-   **SHIP** = **FIGHTER** or **CRUISER**
