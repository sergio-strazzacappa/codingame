# Bijective Numeration

## Goal

Decimal isn't the only base ten positional numbering system!

Write a simple calculator that operates entirely in _decimary_ notation to sum a
list of positive integer values. Decimary is a fun name for what mathematics
calls **bijective numeration** base ten, which uses **A** to represent ten and
lacks a zero digit.

The system is better illustrated than explained. Starting from one, these
numerals are written:

**1**, **2**, **3**, **4**, **5**, **6**, **7**, **8**, **9**, **A** = ten,
**11**, **12**, **13**, **14**, **15**, **16**, **17**, **18**, **19**, **1A** =
ten plus ten = twenty, **21**, **22**, **23**, **24**, **25**, **26**, **27**,
**28**, **29**, **2A** = thirty, **31**, ...

**88**, **89**, **8A** = ninety, **91**, **92**, **93**, **94**, **95**, **96**,
**97**, **98**, **99**, **9A** = ninety plus ten = one hundred, **A1** = a
hundred and one, **A2**, **A3**, **A4**, **A5**, **A6**, **A7**, **A8**, **A9**,
**AA** = a hundred and ten, **111**, ...

**199**, **19A** = two hundred, **1A1** = two hundred and one, ...

## Input

-   Line 1: An integer **count** representing the number of input values
-   Line 2: A string of **decimary** values, separated by spaces

## Output

-   Line 1: A string in _decimary_ notation representing the **summation**

## Constraints

-   2 &leq; **count** &lt; 10
-   1 &leq; length of each **decimary** representation &lt; 10
