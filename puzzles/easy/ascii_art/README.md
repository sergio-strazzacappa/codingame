# ASCII Art

## Rules

ASCII art allows you to represent forms by using characters. To be precise, in
our case, these forms are words. For example, the word _MANHATTAN_ could be
displayed as follows in ASCII art:

<pre style="color:#FFFFFF">
    # #  #  ### # #  #  ### ###  #  ###
    ### # # # # # # # #  #   #  # # # #
    ### ### # # ### ###  #   #  ### # #
    # # # # # # # # # #  #   #  # # # #
    # # # # # # # # # #  #   #  # # # #
</pre>

Your mission is to write a program that can display a line of text in ASCII art
in a style you are given as input.

## Game Input

### Input

- **Line 1**: the width `L` of a letter represented in ASCII art. All letters
  are the same width
- **Line 2**: the height `H` of a letter represented in ASCII art. All letters
  are the same height
- **Line 3**: The line of text `T`, composed of `N` ASCII characters
- **Following lines**: the string of characters ABCDEFGHIJKLMNOPQRSTUVWXYZ?
  represented in ASCII art

## Output

- The text `T` in ASCII art. The characters a to z are shown in ASCII art by
  their equivalent in upper case. The characters that are not in the intervals
  [a-z] or [A-Z] will be shown as a question mark in ASCII art

## Constraints

- 0 &lt; `L` &lt; 30
- 0 &lt; `H` &lt; 30
- 0 &lt; `N` &lt; 200
