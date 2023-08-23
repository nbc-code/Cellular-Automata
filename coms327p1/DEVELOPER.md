Project1: coms327P1

Author: Noah Cantrell, nbcantrell@iastate.edu

ca.c

    Contains the working functions of the project.

    create1DCA - Allocates memory and creates the data structure representing our ca. This function takes in an unsigned int to represent the number of cells in our ca as well as an unsigned char which represents the initial state of each cell in our ca. This function allocates memory for the array of cells in our data structure as well as assigns some variables for our data structure. Namely, number of cells and initial state. Finally, it returns our created ca.

    initCA - initializes cell array. Takes a pointer to the ca data structure which was created in main and sets all cells in the ca to the state provided which is also an input parameter. In here, each cell is set to a random initial state value if the user inputs -1 as the initial state, but this is not used in part C. Otherwise, each cell gets initialized to the user's input of the initial state. Checks for null ca.

    set1DCACell - set specified cell to desired state. Takes in a pointer to the ca data structure, an unsigned integer that represents the desired index of the cell you want to set, and an unsigned char that represents the state you want to set the cell to. Checks for out of bounds index and null ca. Function returns 1 if it set the cell to the specified state correctly, and returns 0 otherwise.

    set2DCACell - set specified cell to desired state. Takes in a pointer to the ca data structure, two unsigned integer that represents the desired x and y indexes, and an unsigned char which represents the state to set the cell to. This checks for out of bounds index and null ca. Function returns 1 if it set the cell to the specified state correctly, and returns 0 otherwise.

    displayCA - Prints out each cell in our ca. Takes in the data structure representing our ca. This functions just iterates through the cell array and outputs each of the cell states until it has gone through each cell.

    step1DCA - This function is used to complete one round of a given rule used on our ca. This function takes in our ca, a pointer to the function of the rule that will be used on our ca, and a flag for whether or not wrapping will be allowed (which helps determind how to handle edge cases for the rule). This function sets takes in, and sets, the wrap rule for the rule function to follow. A temporary array is created to hold the results of the rule and passed back into the ca upon completion.

    step2DCA - This function is used to complete one round of a given rule used on our ca. This function takes in our ca, and a pointer to the function of the rule that will be used on our ca. A temporary array is created to hold the results of the rule and passed back into the ca upon completion.

ca.h

    Contains prototypes for each of the above functions as well as the data structure and typedef used to identify and represent our ca.

main.c

    contains overall function calls for ca creation, initialization, and manipulation. Main also contains constants for command line input error checking, variables for those command line inputs, and the rule function for Conway's game of life.

Makefile

    contains commands to compile the project.

README

    contains information regarding the inner workings of the project.

This project so far contains the basics of C. This includes pointers, loops, memory allocation, and simple data structures.

Project 2:

CellularAutomaton.cpp

    Contains working functions for the project. This includes the constructor, deconstructor, operator =, copy constructor, step, display, and displayCA from project 1 used for sanity checking with the output from the graphics server.

    Added changecell, resetCA, displayInitCA, and new constructor that takes in a width and height.

CellularAutomaton.h

    Contains the header information, includes, function and variable declarations for the CellularAutomaton class

    Added changecell, resetCA, displayInitCA, and new constructor that takes in a width and height.

GraphicsClient.cpp

    Contains working functions for the graphics connections and server side data message format. These functions include a constructor, copy constructor, destructor, operator =, setBackgroundColor, setDrawColor, clear, setPixel, drawRectangle, fillRectangle, clearRectangle, drawOval, fillOval, drawLine, drawString, and repaint functions.

    Only addition here was the fileRequest function.

GraphicsClient.h

    Contains the header information, includes, function and variable declarations for the GraphicsClient class

    Only addition here was the fileRequest function.

main.cpp

    contains overall function calls for CellularAutomaton and GraphicsClient creation and manipulation. Main also contains the rule function for Conway's game of life.

    Changed implementation of main. Now it will wait for user input via mouse clicks and preform various functions based on location of mouse clicks. Clicking buttons will do corresponding actions such as running the rule, stepping, clearing, and so on.

Makefile

    contains commands to compile the project.

README

    contains information regarding the inner workings of the project.