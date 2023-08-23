#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"ca.h"

/*  Print out each cell in CA   */
void displayCA(CA_DATA* ca)
{
    for(int i = 0; i < ca->height; i++)
    {
        for(int j = 0; j < ca->width; j++)
        {
            printf("%u ", ca->cadata[(i*ca->width)+j]);;
        }
        printf("\n");
    }
    printf("\n");
}

/*  Set cell at specified index to specified state  */
int set1DCACell(CA_DATA* ca, unsigned int x, unsigned char state)
{
    // Error checking
    if(x < 0)
    {
        printf("Array index is negative.\n");
        return 0;
    }
    else if(x > ca->width)
    {
        printf("Array index is larger than Array Size.\n");
        return 0;
    }

    if(!ca)
    {
        printf("CA is NULL.\n");
        return 0;
    }

    // Set cell state
    ca->cadata[x] = state;

    // Function finished successfully
    return 1;
}

/*  Set cell at specified index to specified state  */
int set2DCACell(CA_DATA* ca, unsigned int x, unsigned int y, unsigned char state)
{
    //Error checking
    if(x < 0)
    {
        printf("Width is negative. cmon bro");
    }
    else if(x > ca->width)
    {
        printf("You tryna set an outa bounds width");
    }

    if(y < 0)
    {
        printf("Height is negative, ah geez");
    }
    else if(y > ca->height)
    {
        printf("You tryna set an outa bounds height");
    }

    if(!ca)
    {
        printf("CA is NULL.\n");
        return 0;
    }

    ca->cadata[(y*ca->width)+x] = state;

    return 1;
}

/*  Initialize CA   */
void initCA(CA_DATA* ca, int state)
{
    // Needed for random cell initialization on cell state input of -1
    srand(time(NULL));
    
    // Error checking
    if(!ca)
    {
        printf("CA is NULL.\n");
        return NULL;
    }

    // Cells get assigned random states if cell state input was -1
    else if(ca->qstate == (unsigned char)-1)
    {
        for(int i = 0; i < ca->width; i++)
        {
            for(int j = 0; j < ca->height; i++)
            {
                ca->cadata[(i*ca->width)+j] = rand()%(ca->numStates);
            }
        }

        ca->qstate = (unsigned char)0;
    }
    // Otherwise, initialize each cell to given state
    else
    {
        for(int i = 0; i < ca->width; i++)
        {
            for(int j = 0; j < ca->height; j++)
            {
                ca->cadata[(i*ca->width)+j] = ca->qstate;
            }
        }  
    }
}

/*  Create 1DCA   */
CA_DATA* create1DCA(int w, unsigned char qstate)
{
    // Need to allocate memory
    CA_DATA* ca = malloc(sizeof(CA_DATA));

    // Error checking
    if(!ca)
    {
        printf("CA is NULL.\n");
        return NULL;
    }

    // Further allocate memory and set variables
    ca->cadata = malloc(w);
    ca->width = w;
    ca->qstate = qstate;

    return ca;
}

/*  Create 2DCA   */
CA_DATA* create2DCA(int w, int h, unsigned char qstate)
{
    CA_DATA* ca = malloc(sizeof(CA_DATA));
    
    // Error checking
    if(!ca)
    {
        printf("CA is NULL.\n");
        return NULL;
    }

    ca->cadata = malloc((w*h) * sizeof(unsigned char*));
    
    //ca->cadata = (unsigned char**)malloc((w*h) * sizeof(unsigned char*));
    ca->width = w;
    ca->height = h;
    ca->qstate = qstate;

    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            ca->cadata[(i*w)+j] = qstate;
        }
    }
    
    return ca;
}

/*  Complete one round of given rule    */
void step1DCA(CA_DATA* ca, unsigned char (*func)(CA_DATA* , int))
{
    // Error checking
    if(!ca)
    {
        printf("CA is NULL.\n");
        return NULL;
    }

    // Temporary array to store data from the rule's function
    unsigned char* tempArr = malloc(sizeof(unsigned char) * ca->width);

    // Further error checking
    if(!tempArr)
    {
        printf("Issue with allocating memory.\n");
        return NULL;
    }
    // Preform given rule and put results into the temp array
    else
    {
        for(int i = 0; i < ca->width; i++)
        {
            tempArr[i] = func(ca, i);
        }

        //Copy temp array back to our CA
        ca->cadata = tempArr;
    }
}

void step2DCA(CA_DATA* ca, unsigned char(*func)(CA_DATA*, int, int))
{
    // Error checking
    if(!ca)
    {
        printf("CA is NULL.\n");
        return NULL;
    }

    // Temporary array to store data from the rule's function
    unsigned char* tempArr = malloc(((ca->width) * (ca->height))* sizeof(unsigned char));
    
    // Further error checking
    if(!tempArr)
    {
        printf("Issue with allocating memory.\n");
        return NULL;
    }

    // Preform given rule and put results into the temp array
    else
    {
        for(int i = 0; i < ca->height; i++)
        { 
            for(int j = 0; j < ca->width; j++)
            {
               tempArr[(i*ca->width)+j] = func(ca, j, i);
            }
        }
        //Copy temp array back to our CA
        ca->cadata = tempArr;
    }
}