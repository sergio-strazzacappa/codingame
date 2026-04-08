# XML MDF-2016

## Goal

In this challenge, a data format that is a simplified version of XML is used.
Tags are identified by a lowercase English letter. A start tag is represented by
that single letter, and the closing tag is represented by the **-** character,
followed by that letter.

For example, the string **ab-bcd-d-c-ae-e** is the equivalent of &lt;a&gt;
&lt;b&gt; &lt;/ b&gt; &lt;c&gt; &lt;d&gt; &lt;/ d&gt; &lt;/ c&gt; &lt;/a&gt;
&lt;e&gt; &lt;/ e&gt; in XML. The supplied string will always be properly
formed.

Now we define the depth of a tag as 1 + the number of tags in which it is
nested.

In the previous example:

- **a** and **e** have a depth of 1
- **b** and **c** have a depth of 2
- **d** has a depth of 3

The weight of a tag name is defined as the sum of the reciprocals of the depths
of each of its occurrences.

For example, in the chain **a-abab-b-a-b**, there are:

- Two tags **a** with depths of 1 and 2
- Two tags **b** with depths of 1 and 3

thus the weight of **a** is $(1/1) + (1/2) = 1.5$ and the weight of **b** is
$(1/1) + (1/3) = 1.33$.

In this challenge you must determine the letter of the tag with the greatest
weight in the string argument.

## Input

- On a single line, a properly formed string `sequence` representing nested tags

## Output

- The letter corresponding to greatest weight tag name. If two tag names have
  the same weight, display the smallest in alphabetical order

## Constraints

- 1 &leq; length of `sequence` &leq; 300
