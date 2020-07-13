# Magicsquares

A script for finding magic squares of squares.

## Usage

To run the program write the following commands in this folder. This runs algorithm 5 to 1000 using 4 cores.
```bash
make algo5
./main 1000 4 > out.txt
```

## Basics

Magic squares are a grid of 3x3 integers such that the sum of all rows columns
and diagonals equals the same value. Additionally one could restrain the values
to be unique.

A magic square of squares has elements a to i in the following pattern.

| **a** | **b** | **c** |
|-------|-------|-------|
| **d** | **e** | **f** |
| **g** | **h** | **i** |

These values are not the squared yet, so a² + b² + c² = k, would be the
sum of the top row. The value of the sum of the magic square is denoted with k.

This notation is used throughout.

## Algorithms
A few ideas for searching for magic squares are presented below. These algorithms
look for candidates in some range of integers, say [1, N].

### Checking all possible combinations (algorithm 0)
Checking all possible 3x3 grids of integers in the range [1, N] would require
checking N^9 possible magic squares. For a small N of 100 this value is
unimaginably large and checking all possibilities would take an eternity.

### A N^4 approach (algorithm 1)
By choosing some values for a, b, c and d in the range [1, N] we can uniquely
solve the magic square. We can find out the value of k from the top row. Then we
can solve for g, by knowing that the left column square sums to k. All the other
values can be solved similarly. In each case there might not exists an integer
that solves the equation, which means that there does not exist a magic square
for those values of a, b, c and d. In total you have to check about N^4 combinations
for a, b, c and d.

### A solution based on integer factoring (algorithm 5)
First choose values for c and g. Then find the factors of c² - g² = (d - b)(d + b) = (h - f)(h + f). Using these factors it is possible to find d, b, h, f. Finally the values can be found.
