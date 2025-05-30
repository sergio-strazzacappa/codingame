# Fix The Networks

## Goal

John's boss asked him to provision some networks for the company. John is an
experienced network engineer, so the problem should be pretty straightforward.
However, it was late at night, and he had a bit too much to drink, so he messed
up a few of the numbers. Please help John fix the problem!

A CIDR range consists of a prefix and a suffix. The prefix consists of four
8-bit numbers **B** separated by a dot, which represents a 32-bit IP address.
For example, **10.0.0.8** is an IP address. The suffix is a number **S** between
0 and 32 inclusive, which tells us how many bits are fixed, counting from the
left. This means that the remaining bits are variable. These bits determine the
number of addresses **N** available to the CIDR range. \
The prefix and the suffix are separated by a forward slash. An example of a CIDR
range is **10.0.0.8/24**. \
A CIDR range is valid if all of the variable bits are 0.

### Example 1

**192.168.2.0/24** is a **valid** CIDR range because when converted to binary,
the last 8 bits are all 0: \
11000000 . 10101000 . 00000010 . **00000000**

### Example 2

**192.168.10.0/20** is an **invalid** range because when the prefix is converted
to binary, the last 12 bits are not all 0: \
11000000 . 10101000 . 0000**1010 . 00000000**

We can fix it by changing the above CIDR range to **192.168.10.0/23**. Now the
last 9 bits are all 0: \
11000000 . 10101000 . 0000101**0 . 00000000**

Given a **M** number of CIDR ranges, validate each range and print the result.
If a range is valid, print the number of addresses it can hold. If it is
invalid, correct the suffix so that the resulting CIDR range will have the
highest number of addresses possible. Print the new CIDR range and the number of
addresses.

## Input

-   Line 1: An integer **M** for the number of CIDR ranges
-   Next **M** lines: CIDR range

## Output

-   If the CIDR range is valid, print **valid**, and then print **N** for the
    number of addresses
-   If the CIDR range is invalid, print **invalid**, the new CIDR range, and
    then **N** for the number of addresses of the new range

## Constraints

-   1 &leq; **M** &leq; 5
-   0 &leq; **B** &leq; 255
-   0 &leq; **S** &leq; 32
-   1 &leq; **N** &leq; 4294967296
