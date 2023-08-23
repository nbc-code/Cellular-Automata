# coms327P1

Project1: coms327P1

Author: Noah Cantrell, nbcantrell@iastate.edu

Using VScode
ca -> "cellular automaton"

PLEASE:

    if you get weird errors when first cloning or pulling this, use rm *.o once or twice to get rid of any weird/old garbage that may have been left behind.

Fun Stuff:

    Some cool ca files are new.txt and input.txt

Part C notes:

    Functions implemented include,
        - create1DCA which allocates memory for, and creates the data structure representation of our 1DCA.
        - create2DCA which allocates memory for, and creates the data structure representation of our 2DCA
        - initCA which initializes our ca cells to a specified initial state.
        - set1DCACell which sets a specified cell to a specified state.
        - set2DCACell which sets a specified cell to a specified state but for our 2DCA.
        - displayCA which outputs the current state of the ca.
        - A Main function that takes in input from user, creates, initializes, and preforms rule 110 on the ca.
        - step1DCA preforms one step of the provided rule on our 1DCA.
        - step2DCA preforms one step of the provided rule on our 2DCA.

    Makefile:
        The make file will make use of the command 'make' to compile the project

    Header file:
        ca.h contains prototypes for the project, our data structure representing the ca, and typedefs. Must be included in other parts such as main.c

    DEVELOPER file:
        contains in depth information about files, functions, their purposes, etc.

Errors and Issues:

    There were some warnings when first using make command. These warnings were in regards to returning NULL in void functions. The NULLS were for error checking and, at least on my compiler, the warnings go away after compiling once more.

    if you get weird errors when first cloning or pulling this, use rm *.o once or twice to get rid of any weird/old garbage that may have been left behind.

    NOTE:
    Depending on the size of the CA, for example the size 3 600x600, the server may take a long while to load everything in so expect lag for large CAs.

How to:

    In order to run the program, on the command line, type 'make'.
    This will compile the project and create the file you will use to run the program.

    After it is compiled, you simply need to type './gol' into the command line to execute the program AND make sure to input the command line argument as well, this being the file name. 
        For example: "./gol "input.txt""

    In order to view these in the command prompt, simply type in 'less README.md' or 'less DEVELOPER.md' and this will output either of these documents in a scrollable fashion. To quit the document view, simply press 'q'.

    When using make, if errors pop up regaring ca.o and main.o along the lines of "undefined reference to _printf, _puts, _time, _atoi, etc" then run the command "rm *.o" which will remove any file ending with .o from the current directory. Doing this will remove conflicts and you will be able to run 'make' after and all should work from then on.

Project 2 Part A/B Notes:

Graphics Client:

    A constructor with two parameters where the first parameter is the URL to connect and the second parameter is the port number to connect.

    A copy constructor that creates a new connection to the same address and port number

    A destructor that performs the appropriate operations to release all allocated resources.

    An operator = method that closes the existing connection and creates a new connection with the parameters from the right-hand side.

    setBackgroundColor - sets the background color of the associated display. The parameters are the red, green and then blue values respectively.

    setDrawingColor - set the color that objects will be drawn at until another setDrawingColor call is made. The parameters are again, red, green and blue.

    clear - clears the display to the background color

    setPixel - sets the pixel at the location given by the first two parameters to the color given by the last three parameters. The first two parameter are the location given by the x and then y coordinate. The last three parameters are the color given by red, green, and blue in that order.

    drawRectangle - draws a rectangle at the specified coordinates given by the first two parameters of the specified size given by the last two parameters. The first two parameters are again the x and y coordinate in that order, and the last two parameters are the width and height, also given in that order.

    fillRectangle - draws a filled rectangle at the position and size given by the parameters. The parameters are the same as the drawRectangle parameters.

    clearRectangle - clears (sets the pixels to the background color) at the location and size specified by the parameters. These parameters are the same as the drawRectangle parameters.

    drawOval - draws an oval at the specified location inscribed in a rectangle of the specified size. The parameters are the same as given in drawRectangle.

    fillOval - is the same as the drawOval method except the oval is filled.

    drawLine - draws a line starting a point 1 and ending at point 2. Point 1 is given by the first two parameters, x and y, and point 2 is given by the last two parameters, x followed by y.

    drawstring - draws a string of characters on the display given by the last parameter at the position given by the first two parameters, x, y.

    repaint - send the redraw (repaint) signal to the attached graphics server.

    fileRequest - asks for server to open a file loading window.

CellularAutomaton

    A constructor that takes two arguments. First, a string argument that is a name of a file. Second, an int parameter that is the quiescent state of the CA. It then reads a 2DCA.

    copy constructor, operator = , and destructor.

    step - a function that takes a single argument that is the rule function and performs one step of the 2DCA.

    display - A method that takes a single reference parameter to a GraphicsClient object and display the 2DCA on the attached graphics window associated with the GraphicsClient object. The size of the cell displayed on the window is dependent on the size of the 2DCA width and height according to the following table. 'm' is the maximum value of the width and height of the 2DCA.

    resetCA - sets ca data back to initial states.

    displayCA / display initCA - prints ca to terminal, used for sanity checking.

    changeCell - change cell state from 0 to 1 or vice versa, depending on x and y position of the mouse.

    constructor (other) - used mainly for size button functionality, takes in a width and height and sets up ca accordingly.

Others

    Makefile:
        The make file will make use of the command 'make' to compile the project

    Header file:
        CellularAutomaton.h and GraphicsClient.h contains prototypes for the project, our data structure representing the ca, and typedefs. Must be included in other parts such as main.cpp

    DEVELOPER file:
        contains in depth information about files, functions, their purposes, etc.
main

    Reads a file whose name is given in the first parameter of the command line. The file contains a 2DCA definition. Then, display the 2DCA in a display using the graphics server along with a GUI, and then waits for user input. User may select from many buttons and the program will work accordingly.
