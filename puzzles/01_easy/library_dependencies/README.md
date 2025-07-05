# Library Dependencies

## Goal

You are given **n_imp** lines, each representing a library import in python
style. Then, **n_dep** lines for the dependencies between libraries. Then, step
by step you have to:

1.  Assess if the code will run successfully as it is. If so, print **Compiled
    successfully!** and exit

2.  If the code doesn't run successfully, find where the first\* error is
    located, print the line **Import error: tried to import library1 but
    library2 is required.**

    1.  If it can be fixed by reordering the imports, find the only order such
        that at any time, among the possible importable libraries, the smallest
        (lexicographically) module is chosen. The format will be, the line:
        **Suggest to change import order:**, and then, for each library to
        import in the suggested order, the line **import library** (similar to
        the input imports)

    2.  If the error is not salvageable return the message **Fatal error:
        interdependencies.**

\* The imaginary compiler will import the libraries in the order that they are
given by the puzzle until it finds one that requires a library that was not
previously imported.

## Input

-   Line 1: An integer **n_imp** for the number of libraries to import
-   Next **n_imp** lines: A python-like declaration for a library import
-   Next line: An integer **n_dep** for the number of dependency relation
    between libraries
-   Next **n_dep** lines: A string representing a dependency relation between
    libraries

A dependency relation is given in the format: **library requires library1**
[, **library2**, **library3** ... ]

## Output

-   The compilation log as defined in the statement, one log message per line

## Constraints

-   2 &leq; **n_imp** &leq; 100
-   1 &leq; **n_dep** &leq; 100
-   1 &leq; Total amount of dependencies &leq; 200
