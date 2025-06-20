# Chinese Numbers

## Goal

There are ten basic Chinese characters for numbers: **〇**, **一**, **二**,
**三**, **四**, **五**, **六**, **七**, **八** and **九**, representing the
values 0 through 9.

Each character is converted into a 5x5 ASCII art representation using **0** for
filled-in spaces and **\*** for empty spaces as follows:

<pre style="color:#FFFFFF">
0      1      2      3      4
*000*  *****  00000  00000  00000
0***0  *****  *****  *****  0*0*0
0***0  00000  *****  *000*  00*00
0***0  *****  *****  *****  0***0
*000*  *****  00000  00000  00000

5      6      7      8      9
00000  **0**  **0**  *0*0*  **0**
**0**  **0**  **0**  *0*0*  **0**
*0000  00000  00000  *0*0*  0000*
**0*0  *0*0*  **0**  *0*0*  *0*0*
00000  0***0  **000  0***0  0**00
</pre>

The input is 5 strings, where each group of 5 in each string is a number. Your
goal is to output the number represented (if the numbers read 1, 2, and 3, you
output 123).

Chinese characters in input are separated by a space.

## Input

-   5 lines: A string **s** for a line of the ASCII art

## Output

-   1 line: A positive integer represented by the ASCII art

## Constraints

-   5 &leq; length of **s** &leq; 66
