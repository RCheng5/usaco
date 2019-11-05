# Algorithms
## Recursion
### Hanoi Towers

Recursion algorithm:

1. move(int n, char A, char B, char C) is the function for moving n rings from A to B.
2. When n = 1, the function will print out the current move but with the 1 ring moved from A to B.
3. First move n-1 from A to C.
4. Then move the last ring from A to B.
5. Then move the n-1 rings from C to B.

[Program](hanoitower.cpp)

### Wormholes

Algorithm:

1. First create a struct called coord consisting of the x and y values of the coordinates.

2. Then create a struct called pairings consisting of 2 ints which represent the indexes of the coordinates in the pair.

3. Read all of the coordinates into an array of coords.

4. Have a function `config(int n, int t)` that goes through all of the possible configurations of pairings and testing them. It starts at n = 0 pairs and it then chooses 2 new pairs until all of the wormholes are included. Then it tests that configuration. If it works, then the count increments by 1. To make sure there are no overlaps between configurations the after each iteration t will increase to the index of the 1st wormhole of the pair. The 1st wormhole of the next pair has to have an index greater than t. The 2nd wormhole of each pair also must have an index greater than the index of the 1st one. This will remove overlaps between configurations.

5. The test function goes through every wormhole and if Bessie enters the wormhole, then it goes to the wormhole paired with that wormhole. If Bessie exits the wormhole, it goes to the next wormhole on that row. The wormhole each wormhole goes to is recorded in 2 vectors: one for if Bessie enters the wormhole, and one for if Bessie exits that wormhole (if there are no other wormholes in that row, 2nd vector has entry -1). Each times, the function checks if Bessie has entered that wormhole or exited that wormhole to determine whether the test function returns true or false.

# Data Structures
