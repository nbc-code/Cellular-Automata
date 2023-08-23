#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <sys/ioctl.h>
#include "CellularAutomaton.h"

unsigned char gameOfLife(CellularAutomaton* ca, int x, int y)
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

void makeGUI(GraphicsClient* gc)
{
    gc->setDrawingColor(0,0,0);
    // Draw GUI border
    gc->drawRectangle(600,0,199,599);

        // Draw STEP Button
        gc->fillRectangle(620,20,159,40);
        // Draw RUN Button
        gc->fillRectangle(620,80,159,40);
        // Draw PAUSE Button
        gc->fillRectangle(620,140,159,40);
        // Draw QUIT Button
        gc->fillRectangle(620,200,159,40);
        // Draw RESET Button
        gc->fillRectangle(620,260,159,40);
        // Draw LOAD Button
        gc->fillRectangle(620,320,159,40);
        // Draw RANDOMIZE Button
        gc->fillRectangle(620,380,159,40);
        // Size 1 box
        gc->fillRectangle(620, 535, 40, 39);
        // Size 2 box
        gc->fillRectangle(680, 535, 40, 39);
        // Size 3 box
        gc->fillRectangle(740, 535, 40, 39);
        // Draw CLEAR Button
        gc->fillRectangle(620, 440, 159, 40);

    gc->setDrawingColor(0,255,0);
        // Draw STEP button label
        gc->drawString(687,45,"STEP");
        // Draw button label
        gc->drawString(687,105,"RUN"); 
        // Draw button label
        gc->drawString(680,165,"PAUSE");
        // Draw button label
        gc->drawString(687,225,"QUIT");
        // Draw button label
        gc->drawString(680,285,"RESET");
        // Draw button label
        gc->drawString(687,345,"LOAD");
        // Draw button label
        gc->drawString(670,405,"RANDOMIZE");
        // Draw button label
        gc->drawString(640,560,"1"); 
        // Draw button label
        gc->drawString(697,560,"2");
        // Draw button label
        gc->drawString(757,560,"3");
        // Draw Button label
        gc->drawString(682, 465, "CLEAR");

    gc->setDrawingColor(0,0,0);
        // Draw Button Label
        gc->drawString(662, 520, "SELECT SIZE");
}

int conv(unsigned char* msg, int len)
{
    //convert starting from the last nibble
    int result = 0;
    int base = 1;

    for(int i = 0; i > -len; i--)
    {
        int var = msg[i];
        result += var * base;
        base *= 16;
    }
    return result;
}

int main(int argc, char **argv)
{
    GraphicsClient* graphicsClient = new GraphicsClient("10.64.212.218", 7777);
    graphicsClient->clear();
    graphicsClient->setBackgroundColor(90,242,161);

    // Display original CA
    CellularAutomaton* myCA = new CellularAutomaton(argv[1], 0);
    graphicsClient->clear();
    makeGUI(graphicsClient);
    myCA->display(*graphicsClient);
    graphicsClient->repaint();

    bool quit = false;
    bool running = false;

    while(!quit)
    {
        if(running)
        {
            myCA->step(gameOfLife);
            myCA->display(*graphicsClient);
            graphicsClient->repaint();
        }

        // Check bytes
        int count;
        ioctl(graphicsClient->soc, FIONREAD, &count);

        if(count >= 6)
        {
            // Read from server
            unsigned char *servMsg = new unsigned char[count];
            read(graphicsClient->soc, servMsg, count);

            for(int i = 0; i < count; i++)
            {
                // Start
                if(servMsg[i] & 0xFF == 255)
                {
                    // Get mouse type
                    int msgType = conv(&servMsg[i+5], 1);

                    //Mouse type is click
                    if(msgType == 3)
                    {
                        // Get x and y values from mouse position
                        int x = conv(&servMsg[i+10], 4);
                        int y = conv(&servMsg[i+14], 4);

                        // Cell toggle
                        myCA->changeCell(x, y, graphicsClient);

                        // STEP button
                        if((x >= 620 && x < 780) && (y >= 20 && y <= 60))
                        {
                            myCA->step(gameOfLife);
                            myCA->display(*graphicsClient);
                            graphicsClient->repaint();
                        }
                        // RUN button
                        if((x >= 620 && x < 780) && (y >= 80 && y <= 120))
                        {
                            running = true;
                        }
                        // PAUSE button
                        if((x >= 620 && x < 780) && (y >= 140 && y <= 180))
                        {
                            running = false;
                        }
                        // QUIT button
                        if((x >= 620 && x < 780) && (y >= 200 && y <= 240))
                        {
                            delete(myCA);
                            delete(graphicsClient);
                            exit(1);
                        }
                        // RESET button
                        if((x >= 620 && x < 780) && (y >= 260 && y <= 300))
                        {
                            myCA->resetCA();
                            myCA->display(*graphicsClient);
                            graphicsClient->repaint();
                        }
                        // LOAD button
                        if((x >= 620 && x < 780) && (y >= 320 && y <= 360))
                        {
                            graphicsClient->fileRequest();
                        }
                        // RANDOMIZE button
                        if((x >= 620 && x < 780) && (y >= 380 && y <= 420))
                        {
                            // Rand seed
                            srand(time(NULL));
    
                            // For each cell, set to either 0 or 1
                            for(int i = 0; i < myCA->height; i++)
                            {
                                for(int j = 0; j < myCA->width; j++)
                                {
                                    myCA->cadata[(i*myCA->width)+j] = rand()%(2);
                                }
                            }

                            myCA->display(*graphicsClient);
                            graphicsClient->repaint();
                        }
                        // CLEAR button
                        if((x >= 620 && x < 780) && (y >= 440 && y <= 480))
                        {
                            // Set each cell to 0
                            for(int i = 0; i < myCA->height; i++)
                            {
                                for(int j = 0; j < myCA->width; j++)
                                {
                                    myCA->cadata[(i*myCA->width)+j] = 0;
                                }
                            }

                            myCA->display(*graphicsClient);
                            graphicsClient->repaint();
                        }
                        // SIZE 1 button
                        if((x >= 620 && x < 660) && (y >= 535 && y <= 574))
                        {
                            // Clear display, make new CA with new width / height
                            graphicsClient->clearRectangle(0,0,599,600);
                            myCA = new CellularAutomaton(40, 40);
                            myCA->display(*graphicsClient);
                            graphicsClient->repaint();
                        }
                        // SIZE 2 button
                        if((x >= 680 && x < 720) && (y >= 535 && y <= 574))
                        {
                            // Clear display, make new CA with new width / height
                            graphicsClient->clearRectangle(0,0,599,600);
                            myCA = new CellularAutomaton(150, 150);
                            myCA->display(*graphicsClient);
                            graphicsClient->repaint();
                        }
                        // SIZE 3 button
                        if((x >= 740 && x < 780) && (y >= 535 && y <= 574))
                        {
                            // Clear display, make new CA with new width / height
                            graphicsClient->clearRectangle(0,0,599,600);
                            myCA = new CellularAutomaton(600, 600);
                            myCA->display(*graphicsClient);
                            graphicsClient->repaint();
                        }
                    }
                }
                // Check file request
                if(((servMsg[i] & 0xFF) == 255) && ((servMsg[i+5] & 0xFF) == 10))
                {
                    // Get file size, add 5 because of offset in loop
                    int fileSize = conv(&servMsg[i+4],4) + 5;

                    std::string filePath = "";

                    // offset to start at correct place in message, += 2 because of each nibble
                    for(int j = i + 7; j < i + fileSize; j+=2)
                    {
                        // Convert hex numbers into filepath
                        int val = conv(&servMsg[j], 2);
                        filePath += (char) val;
                    }

                    // Make new CA based on file
                    delete(myCA);
                    myCA = new CellularAutomaton(filePath, 0);
                    graphicsClient->clearRectangle(0,0,599,600);
                    myCA->display(*graphicsClient);
                }
            }
            
        }

        // ZZzzz
        usleep(100*1000);
    }

}