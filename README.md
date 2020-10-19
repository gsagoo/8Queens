# 8queens.cpp
The C++ file produces an executable that calculates the positions of N-Queens on a N by N chessboard such the Queens are not attacking each other. 

For example 

4 Queens on an 4 by 4 chessboard. The arrangment for the 4 Queens would be 
(reflected and rotationally-symmetric solutions are included)

    Solution 1
     _ _ _ _
    |_|Q|_|_|
    |_|_|_|Q|
    |Q|_|_|_|
    |_|_|Q|_|



    Solution 2
    _ _ _ _
    |_|_|Q|_|
    |Q|_|_|_|
    |_|_|_|Q|
    |_|Q|_|_|

A HTML file with the solutions is also produced by the program.

## Compiling the code on Linux/Mac 

Within the directory containing the code compile the code with the following line in your terminal window

    g++ 8queens.cpp -o queens -lm -O

then  execute 

    ./queens 

Alternatively if you have "make" installed you can type 

    make queens
    ./queens



