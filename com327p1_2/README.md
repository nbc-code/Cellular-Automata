# coms327P1

Project1: coms327P1

Author: Noah Cantrell, nbcantrell@iastate.edu

Using VScode 
Part A notes:

    Functions implemented include, 
       - init1DCA which initialized a 1 dimensional cellular automaton
       - set1DCACell which sets a specified cell to a specified state
       - display1DCA which outputs the current state of the 1DCA
       - A Main function that sets all even cells to 2 and odd cells to 1

    Makefile:
        The make file will make use of the command 'make' to compile the project

    Header file:
        dca1d.h contains prototypes for the project and must be included in other parts such as main.c

    DEVELOPER file:
        contains in depth information about files, functions, their purposes, etc.

Errors and Issues:

    There were some warnings regarding passing &cdata as a parameter to some of the functions because it expects an unsigned char pointer.

How to:

    In order to run the program, on the command line, type 'make'.
    This will compile the project and create the file you will use to run the program.

    After it is compiled, you simply need to type './odca' into the command line to execute the program.

    In order to view these in the command prompt, simply type in 'less README.md' or 'less DEVELOPER.md' and this will output either of these documents in a scrollable fashion. To quit the document view, simply press 'q'.
