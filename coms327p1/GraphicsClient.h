#ifndef GRAPHICS_CLIENT_H
#define GRAPHICS_CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>

class GraphicsClient
{
    public:
        // Constructor
        GraphicsClient(std::string , int);

        // Copy Constructor
        GraphicsClient(GraphicsClient &other):GraphicsClient(other.URL, other.port)
        {
        }

        // Destructor
        ~GraphicsClient();

        // Operator =
        GraphicsClient& operator=(const GraphicsClient&);

        // Set background color
        void setBackgroundColor(int, int, int);

        // Set drawing color
        void setDrawingColor(int, int, int);

        // clear display
        void clear();

        // Set pixel
        void setPixel(int, int, int, int, int);

        // Draw rectangle
        void drawRectangle(int, int, int, int);

        // Fill rectangle
        void fillRectangle(int, int, int, int);

        // Clear rectangle
        void clearRectangle(int, int, int, int);

        // Draw Oval
        void drawOval(int, int, int, int);

        // Fill oval
        void fillOval(int, int, int, int);

        // Draw line
        void drawLine(int, int, int, int);

        // Draw string
        void drawString(int, int, std::string);

        // Repaint
        void repaint();

        // File Request
        void fileRequest();

        std::string URL;
        int port;
        char arr[16353];
        int soc;
        

    private:
        void connect(std::string, int);
        void disconnect();
};

#endif