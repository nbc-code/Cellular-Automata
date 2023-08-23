#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"ca.h"

void display1DCA(CA_DATA* ca)
{
    for(int i = 0; i < ca->size; i++)
    {
        printf("%u ", ca->cells[i]);
    }
    printf("\n");
}

int set1DCACell(CA_DATA* ca, unsigned int arrIndex, unsigned char cellState)
{
    if(arrIndex < 0)
    {
        printf("Array index is negative.\n");
        return 0;
    }
    else if(arrIndex > ca->size)
    {
        printf("Array index is larger than Array Size.\n");
        return 0;
    }
    if(!ca)
    {
        printf("CA is NULL.\n");
        return 0;
    }

    ca->cells[arrIndex] = cellState;

    return 1;
}

void init1DCA(CA_DATA* ca, int numCells)
{
    srand(time(NULL));

    if(!ca)
    {
        printf("CA is NULL.\n");
        return NULL;
    }
    else if(ca->qstate == (unsigned char)-1)
    {
        for(int i = 0; i < numCells; i++)
        {
            ca->cells[i] = rand()%(ca->numStates);
        }

        ca->qstate = (unsigned char)0;
    }
    else
    {
        for(int i = 0; i < numCells; i++)
        {
            ca->cells[i] = ca->qstate;
        }  
    }
    
}

CA_DATA* create1DCA(unsigned int numCells, unsigned char initState)
{
    CA_DATA* ca = malloc(sizeof(CA_DATA));

    if(!ca)
    {
        printf("CA is NULL.\n");
        return NULL;
    }

    ca->cells = malloc(numCells);
    ca->size = numCells;
    ca->qstate = initState;

    return ca;
}

void stepCA(CA_DATA* ca, unsigned char (*func)(CA_DATA* , int) , int wrapRule)
{
    if(!ca)
    {
        printf("CA is NULL.\n");
        return NULL;
    }
    ca->wrapflag = wrapRule;

    unsigned char* tempArr = malloc(sizeof(unsigned char) * ca->size);

    if(!tempArr)
    {
        printf("Issue with allocating memory.\n");
        return NULL;
    }
    else
    {
        for(int i = 0; i < ca->size; i++)
        {
            tempArr[i] = func(ca, i);
        }
        ca->cells = tempArr;
    }
}