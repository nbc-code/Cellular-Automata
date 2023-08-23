Project1: coms327P1

Author: Noah Cantrell, nbcantrell@iastate.edu

dca1d.c

    Contains the working functions of the project.

    init1DCA - initializes cell array. Takes in number of cells to initialize as well as a pointer to the start of the cell array created in main. The cell array may be larger than the number of cells inputed to the function.

    set1DCACell - set specified cell to desired state. Takes in a pointer to the start of the array, and integer that represents the desired index of the cell you want to set, and an unsigned char that represents the state you want to set the cell to.

    display1DCA - Outputs cell array. Takes in an integer that represents the number of cells you wish to output and a pointer to the beginning of the cell array. This functions just iterates through the array and outputs the cell states until it reaches the number of cells.

dca1d.h

    Contains prototypes for each of the above functions.

main.c

    contains overall function calls for cell array initialization, manipulation, and output.

Makefile

    contains commands to compile the project.

README

    contains information regarding the inner workings of the project.

This project so far contains the basics of C. This includes pointers and loops. 