#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ca.h"

const int MIN_NUM = 10;
const int MAX_NUM = 100;

unsigned char aRule(CA_DATA * ca, int index)
{
    unsigned char current = ca->cells[index];
    unsigned char leftOfCell, rightOfCell;

    if(ca->wrapflag == 0)
    {
        if((index - 1) < 0)
        {
            leftOfCell = ca->qstate;
        }
        else
        {
            leftOfCell = ca->cells[index - 1];
        }
        if((index + 1) > (ca->size-1))
        {
            rightOfCell = ca->qstate;
        }
        else
        {
            rightOfCell = ca->cells[index + 1];
        }
    }
    else
    {
        if((index - 1) < 0)
        {
            leftOfCell = ca->cells[ca->size - 1];
        }
        else
        {
            leftOfCell = ca->cells[index - 1];
        }
        if((index + 1) > (ca->size - 1))
        {
            rightOfCell = ca->cells[ca->size - index];
        }
        else
        {
            rightOfCell = ca->cells[index + 1];
        }
    }

    unsigned char threeCells[3] = {leftOfCell, current, rightOfCell};
    if(threeCells[0] == 0 && threeCells[1] == 0 && threeCells[2] == 0){return 0;}
    else if(threeCells[0] == 0 && threeCells[1] == 0 && threeCells[2] == 1){return 1;}
    else if(threeCells[0] == 0 && threeCells[1] == 1 && threeCells[2] == 0){return 1;}
    else if(threeCells[0] == 0 && threeCells[1] == 1 && threeCells[2] == 1){return 1;}
    else if(threeCells[0] == 1 && threeCells[1] == 0 && threeCells[2] == 0){return 0;}
    else if(threeCells[0] == 1 && threeCells[1] == 0 && threeCells[2] == 1){return 1;}
    else if(threeCells[0] == 1 && threeCells[1] == 1 && threeCells[2] == 0){return 1;}
    else{return 0;}

}

int main(int argc, char **argv)
{
    int numberOfCells = atoi(argv[1]);
    if(numberOfCells < MIN_NUM || numberOfCells > MAX_NUM)
    {
        printf("number of cells out of bounds.\n");
        exit(1);
    }

    int numberOfStatesPerCell = atoi(argv[2]);
    if(numberOfStatesPerCell < 0)
    {
        printf("States per cell out of bounds.\n");
        exit(1);
    }

    int cellWrapFlag;
    if(strcmp(argv[3], "wrap") == 0)
    {
        cellWrapFlag = 1;
    }
    else if(strcmp(argv[3], "nowrap") == 0)
    {
        cellWrapFlag = 0;
    }
    else
    {
        printf("Incorrect wrap flag input.\n");
        exit(1);
    }

    int initialCellState = atoi(argv[4]);
    if(initialCellState < -1)
    {
        printf("Initial cell state must be between 0 and number of states - 1, or be -1.\n");
        exit(1);
    }
    else if(initialCellState > (numberOfStatesPerCell - 1))
    {
        printf("Initial cell state must be between 0 and number of states - 1, or be -1.\n");
        exit(1);
    }


    int numberOfSteps = atoi(argv[5]);
    CA_DATA* myCA;

    myCA = create1DCA(numberOfCells, initialCellState);
    myCA->numStates = numberOfStatesPerCell;
    init1DCA(myCA, numberOfCells);
    printf("Initial State - ");
    display1DCA(myCA);

    for(int i = 0 ; i < numberOfSteps; i++)
    {
        stepCA(myCA, aRule, cellWrapFlag);
        display1DCA(myCA);
    }

    return 0;
}