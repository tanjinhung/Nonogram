# Nonogram GUI Generator and Solver


```
Problem:                            Answer:
. . . . . . . . . . 5 1 2           # # # # # . # . # # 5 1 2
. . . . . . . . . . 10              # # # # # # # # # # 10
. . . . . . . . . . 2 6             # # . # # # # # # . 2 6
. . . . . . . . . . 1 4             # . . . # # # # . . 1 4
. . . . . . . . . . 3 1             . . . . # # # . . # 3 1
. . . . . . . . . . 1 1 2           . . # . . # . . # # 1 1 2
. . . . . . . . . . 3 3             . # # # . . . # # # 3 3
. . . . . . . . . . 3 4             . # # # . . # # # # 3 4
. . . . . . . . . . 1 5             . . # . . # # # # # 1 5
. . . . . . . . . . 6               . . . . # # # # # # 6
4 3 2 3 5 5 5 3 3 2                 4 3 2 3 5 5 5 3 3 2
  2 4 2   2 3 4 5 6                   2 4 2   2 3 4 5 6
```

Create a Nonogram Generator and Solver.
----------------------------------------

1. The problem can be written into sets that denotes the X and y axis.
2. This can be further compose into a set of sets.
3. Rendering first in an ASCII format.
4. Pressing a space results in the toggling a '.' to a '#' and vice versa.
5. 