# Blunder - Episode 2

## Goal

You have managed to find Blunder. His circuits are programmed with an algorithm which has made him lose all sense of humor or fun. You decide to return his system to his original behavior.

The first trait of character that you are going to work on is his passion for money. Blunder can detect bank notes several miles away.

Your objective is to write a program that will lead him to always find the most money possible, wherever it is.

## Rules

To check that your algorithm works properly, Blunder is placed in a room at the entrance of a building. There is a sum of money in each of the rooms that make up this building. Each room has exactly two doors which you can use to get out. Each door leads either to a new room or to the outside of the building.

Blunder must collect as much money as possible, by going from room to room, **without being able to go back**, until he gets out of the building. Thanks to his sensors, Blunder can analyze the building right from the outset in order to detect the list of rooms and the money contained in each of them. This analysis of the rooms will be provided as input for your program so that you can implement an algorithm that will make the best decisions.

Each room in the building has a unique number. Each door of a room is marked with a number, which represents the number of the room that it opens, or E if it opens to the outside of the building. Several doors can lead to one room but due to the layout of the building **it is impossible for Blunder to go through the same room twice**. Some doors open in one direction only.

The first room in which Blunder finds himself has the number **0**.

## Input

**Line 1**: the number **N** of rooms in the building.

**N following lines**: one line with a room number (integer), a sum of money (integer), the two numbers of the rooms which are accessible (integers or E if the door is an exit). These four values are separated by a white space.

## Output

An integer representing the maximum amount of money that Blunder can collect by taking a series of doors to reach the outside of the building.

## Constraints

0 < **N** < 10000
