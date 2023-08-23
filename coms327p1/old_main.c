#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "ca.h"

// Constants needed for first input variable
const int MIN_NUM = 10;
const int MAX_NUM = 100;

// Function for rule 110
unsigned char aRule(CA_DATA * ca, int index)
{
    // Variables used to calculate the result of rule 110
    unsigned char current = ca->cadata[index];
    unsigned char leftOfCell, rightOfCell;

    // Check for wrapping condition and assign variables as needed
    if(ca->wrapflag == 0)
    {
        if((index - 1) < 0)
        {
            leftOfCell = ca->qstate;
        }
        else
        {
            leftOfCell = ca->cadata[index - 1];
        }
        if((index + 1) > (ca->width-1))
        {
            rightOfCell = ca->qstate;
        }
        else
        {
            rightOfCell = ca->cadata[index + 1];
        }
    }
    else
    {
        if((index - 1) < 0)
        {
            leftOfCell = ca->cadata[ca->width - 1];
        }
        else
        {
            leftOfCell = ca->cadata[index - 1];
        }
        if((index + 1) > (ca->width - 1))
        {
            rightOfCell = ca->cadata[ca->width - index];
        }
        else
        {
            rightOfCell = ca->cadata[index + 1];
        }
    }

    unsigned char threeCells[3] = {leftOfCell, current, rightOfCell};

    // Checking and returning result of rule110
    if(threeCells[0] == 0 && threeCells[1] == 0 && threeCells[2] == 0){return 0;}
    else if(threeCells[0] == 0 && threeCells[1] == 0 && threeCells[2] == 1){return 1;}
    else if(threeCells[0] == 0 && threeCells[1] == 1 && threeCells[2] == 0){return 1;}
    else if(threeCells[0] == 0 && threeCells[1] == 1 && threeCells[2] == 1){return 1;}
    else if(threeCells[0] == 1 && threeCells[1] == 0 && threeCells[2] == 0){return 0;}
    else if(threeCells[0] == 1 && threeCells[1] == 0 && threeCells[2] == 1){return 1;}
    else if(threeCells[0] == 1 && threeCells[1] == 1 && threeCells[2] == 0){return 1;}
    else{return 0;}

}

// Simulate Conway's Game of Life
unsigned char gameOfLife(CA_DATA* ca, int x, int y)
{
    int neighbors = 0;
    int newX, newY;

    // Loop to get next index
    // The newX and newY will represent the indicies of the current index's neighbors, even if out of bounds.
    for(int rows = -1; rows <= 1; rows++)
    {
        for(int columns = -1; columns <= 1; columns++)
        {
            newX = ((x + rows + ca->width) % ca->width);
            newY = ((y + columns + ca->height) % ca->height);
            neighbors += ca->cadata[(newY * ca->width) + newX];
        }
    }

    // Don't count current cell
    int current = ca->cadata[(y * ca->width) + x];
    neighbors -= current;

    // General rules for if current cell lives or dies......
    if(current == 1 && (neighbors == 2 || neighbors == 3))
    {
        return 1;
    }
    else if(current == 0 && (neighbors == 3))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char **argv)
{
    // Command line input for the dimension of the CA
    int dimension = atoi(argv[1]);
    if(dimension != 2)
    {
        printf("Please choose 2 2D.\n");
        exit(1);
    }
    CA_DATA* myCA;
    int rows, columns;
    int temp;

    // Command line input for file name
    FILE* inFile = NULL;
    inFile = fopen(argv[2], "r");

    // Error checking, file not found
    if(inFile == NULL)
    {
        printf("Could not open file", inFile);
        exit(1);
    }
    else
    {
        // Scan in width and height
        fscanf(inFile, "%d", &rows);
        printf("Height: %d\n", rows);
        fscanf(inFile, "%d", &columns);
        printf("Width: %d\n", columns);

        // Create 2DCA
        myCA = create2DCA(columns, rows, 0);
        
        // Set each cell in 2DCA based on rest of the file's contents
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                fscanf(inFile, "%d", &temp);
                set2DCACell(myCA, j, i, (unsigned char)temp);
            }
        }
    }
    printf("\nOriginal from file: \n");
    displayCA(myCA);

    // Run game of life rule for each press of the enter key, any other key ends program.
    int aBool = 1;
    while(aBool)
    {
        // Check character
        if(getchar() != '\n')
        {
            aBool = 0;
        }
        // Do rule
        else
        {
            step2DCA(myCA, gameOfLife);
            displayCA(myCA);   
        }
    }

    return 0;
}