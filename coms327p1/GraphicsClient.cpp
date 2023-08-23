#include"GraphicsClient.h"

GraphicsClient::GraphicsClient(std::string URL, int port)
{
    this->port = port;
    this->URL = URL;
    connect(this->URL.c_str(), this->port);
}

GraphicsClient::~GraphicsClient()
{
    disconnect();
    close(soc);
}

GraphicsClient& GraphicsClient::operator=(const GraphicsClient& objToCopy)
{
    disconnect();
    connect(objToCopy.URL.c_str(), objToCopy.port);
    return *this;
}

void GraphicsClient::setBackgroundColor(int r, int g, int b)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x00;
    arr[4] = 0x07;

    // CHAR VAL FOR SET_BACKGROUND_COLOR
    arr[5] = 0x02;

    // NIBBLES
    arr[6] = (r & 0xF0) >> 4;
    arr[7] = (r & 0x0F) >> 0;
    arr[8] = (g & 0xF0) >> 4;
    arr[9] = (g & 0x0F) >> 0;
    arr[10] = (b & 0xF0) >> 4;
    arr[11] = (b & 0x0F) >> 0;

    // SEND
    ::send(soc, arr, 12, 0);
}

void GraphicsClient::setDrawingColor(int r, int g, int b)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x00;
    arr[4] = 0x07;

    // CHAR VAL FOR SET_DRAW_COLOR
    arr[5] = 0x06;

    // RGB NIBBLES
    arr[6] = (r & 0xF0) >> 4;
    arr[7] = (r & 0x0F) >> 0;
    arr[8] = (g & 0xF0) >> 4;
    arr[9] = (g & 0x0F) >> 0;
    arr[10] = (b & 0xF0) >> 4;
    arr[11] = (b & 0x0F) >> 0;

    // SEND
    ::send(soc, arr, 12, 0);
}

void GraphicsClient::clear()
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x00;
    arr[4] = 0x01;

    // CHAR VAL FOR CLEAR
    arr[5] = 0x01;

    // SEND
    ::send(soc, arr, 6, 0);
}

void GraphicsClient::setPixel(int x, int y, int r, int g, int b)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH 
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x00;
    arr[4] = 0x0F;

    // CHAR VAL FOR SET_PIXEL
    arr[5] = 0x03;

    // NIBBLES
        // X
        arr[6] = (x & 0xF000) >> 12;
        arr[7] = (x & 0x0F00) >> 8;
        arr[8] = (x & 0x00F0) >> 4;
        arr[9] = (x & 0x000F) >> 0;

        // Y
        arr[10] = (y & 0xF000) >> 12;
        arr[11] = (y & 0x0F00) >> 8;
        arr[12] = (y & 0x00F0) >> 4;
        arr[13] = (y & 0x000F) >> 0;

        // R
        arr[14] = (r & 0xF0) >> 4;
        arr[15] = (r & 0x0F) >> 0;

        // G
        arr[16] = (g & 0xF0) >> 4;
        arr[17] = (g & 0x0F) >> 0;

        // B
        arr[18] = (b & 0xF0) >> 4;
        arr[19] = (b & 0x0F) >> 0;

    ::send(soc, arr, 20, 0);
}

void GraphicsClient::drawRectangle(int x, int y, int w, int h)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x01;
    arr[4] = 0x01;

    // CHAR VAL FOR DRAW_RECTANGLE
    arr[5] = 0x07;

    // NIBBLES
        // X
        arr[6] = (x & 0xF000) >> 12;
        arr[7] = (x & 0x0F00) >> 8;
        arr[8] = (x & 0x00F0) >> 4;
        arr[9] = (x & 0x000F) >> 0;

        // Y
        arr[10] = (y & 0xF000) >> 12;
        arr[11] = (y & 0x0F00) >> 8;
        arr[12] = (y & 0x00F0) >> 4;
        arr[13] = (y & 0x000F) >> 0;

        // W
        arr[14] = (w & 0xF000) >> 12;
        arr[15] = (w & 0x0F00) >> 8;
        arr[16] = (w & 0x00F0) >> 4;
        arr[17] = (w & 0x000F) >> 0;

        // H
        arr[18] = (h & 0xF000) >> 12;
        arr[19] = (h & 0x0F00) >> 8;
        arr[20] = (h & 0x00F0) >> 4;
        arr[21] = (h & 0x000F) >> 0;

    ::send(soc, arr, 22, 0);
}

void GraphicsClient::fillRectangle(int x, int y, int w, int h)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x01;
    arr[4] = 0x01;

    // CHAR VAL FOR DRAW_RECTANGLE
    arr[5] = 0x08;

    // NIBBLES
        // X
        arr[6] = (x & 0xF000) >> 12;
        arr[7] = (x & 0x0F00) >> 8;
        arr[8] = (x & 0x00F0) >> 4;
        arr[9] = (x & 0x000F) >> 0;

        // Y
        arr[10] = (y & 0xF000) >> 12;
        arr[11] = (y & 0x0F00) >> 8;
        arr[12] = (y & 0x00F0) >> 4;
        arr[13] = (y & 0x000F) >> 0;

        // W
        arr[14] = (w & 0xF000) >> 12;
        arr[15] = (w & 0x0F00) >> 8;
        arr[16] = (w & 0x00F0) >> 4;
        arr[17] = (w & 0x000F) >> 0;

        // H
        arr[18] = (h & 0xF000) >> 12;
        arr[19] = (h & 0x0F00) >> 8;
        arr[20] = (h & 0x00F0) >> 4;
        arr[21] = (h & 0x000F) >> 0;

    ::send(soc, arr, 22, 0);
}

void GraphicsClient::clearRectangle(int x, int y, int w, int h)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x01;
    arr[4] = 0x01;

    // CHAR VAL FOR DRAW_RECTANGLE
    arr[5] = 0x09;

    // NIBBLES
        // X
        arr[6] = (x & 0xF000) >> 12;
        arr[7] = (x & 0x0F00) >> 8;
        arr[8] = (x & 0x00F0) >> 4;
        arr[9] = (x & 0x000F) >> 0;

        // Y
        arr[10] = (y & 0xF000) >> 12;
        arr[11] = (y & 0x0F00) >> 8;
        arr[12] = (y & 0x00F0) >> 4;
        arr[13] = (y & 0x000F) >> 0;

        // W
        arr[14] = (w & 0xF000) >> 12;
        arr[15] = (w & 0x0F00) >> 8;
        arr[16] = (w & 0x00F0) >> 4;
        arr[17] = (w & 0x000F) >> 0;

        // H
        arr[18] = (h & 0xF000) >> 12;
        arr[19] = (h & 0x0F00) >> 8;
        arr[20] = (h & 0x00F0) >> 4;
        arr[21] = (h & 0x000F) >> 0;

    ::send(soc, arr, 22, 0);
}

void GraphicsClient::drawOval(int x, int y, int w, int h)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x01;
    arr[4] = 0x01;

    // CHAR VAL FOR DRAW_RECTANGLE
    arr[5] = 0x0A;

    // NIBBLES
        // X
        arr[6] = (x & 0xF000) >> 12;
        arr[7] = (x & 0x0F00) >> 8;
        arr[8] = (x & 0x00F0) >> 4;
        arr[9] = (x & 0x000F) >> 0;

        // Y
        arr[10] = (y & 0xF000) >> 12;
        arr[11] = (y & 0x0F00) >> 8;
        arr[12] = (y & 0x00F0) >> 4;
        arr[13] = (y & 0x000F) >> 0;

        // W
        arr[14] = (w & 0xF000) >> 12;
        arr[15] = (w & 0x0F00) >> 8;
        arr[16] = (w & 0x00F0) >> 4;
        arr[17] = (w & 0x000F) >> 0;

        // H
        arr[18] = (h & 0xF000) >> 12;
        arr[19] = (h & 0x0F00) >> 8;
        arr[20] = (h & 0x00F0) >> 4;
        arr[21] = (h & 0x000F) >> 0;

    ::send(soc, arr, 22, 0);
}

void GraphicsClient::fillOval(int x, int y, int w, int h)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x01;
    arr[4] = 0x01;

    // CHAR VAL FOR DRAW_RECTANGLE
    arr[5] = 0x0B;

    // NIBBLES
        // X
        arr[6] = (x & 0xF000) >> 12;
        arr[7] = (x & 0x0F00) >> 8;
        arr[8] = (x & 0x00F0) >> 4;
        arr[9] = (x & 0x000F) >> 0;

        // Y
        arr[10] = (y & 0xF000) >> 12;
        arr[11] = (y & 0x0F00) >> 8;
        arr[12] = (y & 0x00F0) >> 4;
        arr[13] = (y & 0x000F) >> 0;

        // W
        arr[14] = (w & 0xF000) >> 12;
        arr[15] = (w & 0x0F00) >> 8;
        arr[16] = (w & 0x00F0) >> 4;
        arr[17] = (w & 0x000F) >> 0;

        // H
        arr[18] = (h & 0xF000) >> 12;
        arr[19] = (h & 0x0F00) >> 8;
        arr[20] = (h & 0x00F0) >> 4;
        arr[21] = (h & 0x000F) >> 0;

    ::send(soc, arr, 22, 0);
}

void GraphicsClient::drawLine(int x1, int y1, int x2, int y2)
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x01;
    arr[4] = 0x01;

    // CHAR VAL FOR DRAW_RECTANGLE
    arr[5] = 0x0D;

    // NIBBLES
        // X
        arr[6] = (x1 & 0xF000) >> 12;
        arr[7] = (x1 & 0x0F00) >> 8;
        arr[8] = (x1 & 0x00F0) >> 4;
        arr[9] = (x1 & 0x000F) >> 0;

        // Y
        arr[10] = (y1 & 0xF000) >> 12;
        arr[11] = (y1 & 0x0F00) >> 8;
        arr[12] = (y1 & 0x00F0) >> 4;
        arr[13] = (y1 & 0x000F) >> 0;

        // W
        arr[14] = (x2 & 0xF000) >> 12;
        arr[15] = (x2 & 0x0F00) >> 8;
        arr[16] = (x2 & 0x00F0) >> 4;
        arr[17] = (x2 & 0x000F) >> 0;

        // H
        arr[18] = (y2 & 0xF000) >> 12;
        arr[19] = (y2 & 0x0F00) >> 8;
        arr[20] = (y2 & 0x00F0) >> 4;
        arr[21] = (y2 & 0x000F) >> 0;

    ::send(soc, arr, 22, 0);
}

void GraphicsClient::drawString(int x, int y, std::string str)
{
    int strVar = (str.length() * 2);

    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = ((strVar+9) & 0xF000) >> 12;
    arr[2] = ((strVar+9) & 0x0F00) >> 8;
    arr[3] = ((strVar+9) & 0x00F0) >> 4;
    arr[4] = ((strVar+9) & 0x000F) >> 0;

    // CHAR VAL FOR DRAW_STRING
    arr[5] = 0x05;

    //NIBBLES
        // X
        arr[6] = (x & 0xF000) >> 12;
        arr[7] = (x & 0x0F00) >> 8;
        arr[8] = (x & 0x00F0) >> 4;
        arr[9] = (x & 0x000F) >> 0;

        // Y
        arr[10] = (y & 0xF000) >> 12;
        arr[11] = (y & 0x0F00) >> 8;
        arr[12] = (y & 0x00F0) >> 4;
        arr[13] = (y & 0x000F) >> 0;

        // STRING
        for(int i = 0, j = 0; i < str.length(); i++)
        {
            arr[14+j] = (str[i] & 0xF0) >> 4;
            arr[14+j+1] = (str[i] & 0x0F) >> 0;
            j+=2;
        }

        // SEND
        ::send(soc, arr, 14 + strVar, 0);
}

void GraphicsClient::repaint()
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x00;
    arr[4] = 0x01;

    // CHAR VAL FOR CLEAR
    arr[5] = 0x0C;

    // SEND
    ::send(soc, arr, 6, 0);
}

void GraphicsClient::fileRequest()
{
    // SYNC
    arr[0] = 0xFF;

    // LENGTH
    arr[1] = 0x00;
    arr[2] = 0x00;
    arr[3] = 0x00;
    arr[4] = 0x01;

    // CHAR VAL FOR CLEAR
    arr[5] = 0x0E;

    // SEND
    ::send(soc, arr, 6, 0);
}

void GraphicsClient::connect(std::string URL, int port)
{
    soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc < 0)
    {
        fprintf( stderr, "Error creating socket\n");
        exit(-1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, URL.c_str(), &serv_addr.sin_addr)<=0)
    {
        fprintf(stderr, "Invalid address/ Address not supported \n");
        return;
    }

    if (::connect(soc, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        fprintf(stderr, "Connection Failed \n");
        return;
    }
}

void GraphicsClient::disconnect()
{
    ::close(soc);
}