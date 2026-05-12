# Spring Challenge 2026 - Troll Farm

_This is a **league-based** challenge_

_Wood leagues should be considered as a tutorial which lets players discover the
different rules of the game._
_In Bronze league all rules will be unlocked and the real challenge will begin._
_To see the full rules, go
[here](https://www.codingame.com/demo/1423805f9c28c9654cfd4d57b0208df71315c49)
and switch leagues at the top-right corner._

## The Goal

You control a pack of trolls. Make them collect the most resources.

## Rules

Each player starts with a shack and a troll. Control your troll to collect
fruits and then bring the resources back to your shack. The resources can be
used to train more trolls or plant trees. The game is played on a grid, cells
have different terrains and trees on them.

### Troll attributes

Each troll has **4** attributes: `movementSpeed`, `carryCapacity`,
`harvestPower` and `chopPower`. They can't be changed.

### Trees

A tree has a `type` (**PLUM**, **LEMON**, **APPLE**, **BANANA**), a `size`, a
`health`, an amount of `fruits` and a `cooldown`. When cooldown reaches **0**,
the tree either grows in size or, if at maximum size (**4**), produces fruits.
Trees can hold up to **3** fruits.

### Moving units

Each troll has a `movementSpeed` determining how many cells it can `MOVE`
horizontally or vertically per turn. Each cell can hold at most **1** troll per
team. Only **GRASS** cells are walkable. If the target is out of range or not
walkable, the troll moves to the nearest reachable cell towards it.

### Harvesting

Trees can be harvested, given they have fruits on them. When a troll shares a
cell with a tree, `HARVEST` will take as many fruits as possible by free
`carryCapacity` and `harvestPower`. When two trolls harvest the same tree in
parallel, they keep taking one fruit at a time, as long as there are fruits left
and they can still harvest. The last fruit can get duplicated, so that both
trolls can have it.

### Dropping items

When a troll carrying resources is next to its shack (horizontally or
vertically), `DROP` transfers all carried items to the shack.

## Victory Conditions

- You score more points than your opponent. Each fruit in your shack scores
  **1** point

## Loss Conditions

- You have fewer points than your opponent
- You fail to respond in time or output an unrecognized command.

## Game Input

### Initial input

- **First line**: `width` `height`, the grid size
- **Next** `height` **lines**: each line has `width` characters: In this league
  every character is **.** for **GRASS**, **0** for your own **SHACK**, **1**
  for your opponent's **SHACK**

### Input for each game turn

- **First two lines: your inventory followed by your opponent's inventory**:
  `plums`, `lemons`, `apples`, `bananas`, `(reserved)`, `(reserved)`. In this
  league the last two values are always **0**
- **Next line**: `treeCount`, the number of trees
- **Next** `treeCount` **lines**: `type` `x` `y` `size` `health` `fruits`
  `cooldown`, where `type` can be **PLUM**, **LEMON**, **APPLE**, **BANANA**
- **Next line**: `trollsCount`, the number of trolls
- **Next** `trollsCount` **lines**: `id` `player` `x` `y` `movementSpeed`
  `carryCapacity` `harvestPower` `(reserved)` `carryPlum` `carryLemon`
  `carryApple` `carryBanana` `(reserved)` `(reserved)`, where `player` is
  **0** if you own the troll, **1** otherwise

## Output for one game turn

Each turn you can print any number of commands, separated by **;**.

- `MOVE` `id` `x` `y`: Move troll `id` to cell (`x`, `y`)
- `HARVEST` `id`: Make troll `id` harvest on its current cell
- `DROP` `id`: Make troll `id` drop all carried items at the shack
- `WAIT`: to do nothing
- `MSG`: text to display a message in the replay

## Constraints

- Response time for the first turn &leq; **1000** ms
- Response time per turn &leq; **50** ms

_Note: you will only lose the game when you exceed the time limit **3** times by
at most **50** ms or once by more than that. This is to counter random delays
when servers are busy, it is not advised to intentionally exceed the limits._

- The game ends after **100** turns (for this league, later **300**)
- `height` = **8** (for this league, later up to **11**)
- `width` = **2** \* `height`
