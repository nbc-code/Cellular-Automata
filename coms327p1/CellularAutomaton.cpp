#include<fstream>
#include"CellularAutomaton.h"
#include"GraphicsClient.h"

CellularAutomaton::CellularAutomaton(int w, int h)
{
    // For creating new, blank CA based on width and height
    width = w;
    height = h;

    cadata = new unsigned char[width*height];
    initCADATA = new unsigned char[width*height];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cadata[(i*width)+j] = (unsigned char) 0;
            initCADATA[(i*width)+j] = (unsigned char) 0;
        }
    }

}

void CellularAutomaton::changeCell(int x, int y, GraphicsClient* graphicsClient)
{
    int m = std::max(width, height);
    int gap, cellSize;

    if(m > 200 && m <= 600)
    {
        cellSize = 1;
        gap = 0;
    }
    else if(m > 100 && m <= 200)
    {
        cellSize = 2;
        gap = 1;
    }
    else if(m > 50 && m <= 100)
    {
        cellSize = 4;
        gap = 1;
    }
    else if(m > 1 && m <= 50)
    {
        cellSize = 10;
        gap = 2;
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // check x and y position, account for cell size and gap
            if((x >= j * (cellSize + gap) && x <= (j * (cellSize + gap) + cellSize))
            && (y >= i * (cellSize + gap) && y <= (i * (cellSize + gap) + cellSize)))
            {
                // Flip the states like pancakes
                if(cadata[(i*width)+j] == 0)
                {
                    cadata[(i*width)+j] = 1;
                }
                else
                {
                    cadata[(i*width)+j] = 0;
                }
            }
            // Color based on cell state
            if(cadata[(i*width)+j] == 0)
            {
                graphicsClient->setDrawingColor(0,0,0);
            }
            else
            {
                graphicsClient->setDrawingColor(0,255,0);
            }
            // recolor cell
            graphicsClient->fillRectangle((j * (cellSize + gap)), (i * (cellSize + gap)), cellSize, cellSize);
        }
    }
    graphicsClient->repaint();
}

CellularAutomaton::CellularAutomaton(std::string fileName, int qstate)
{
    this->file = fileName;
    this->qstate = qstate;

    int rows, columns;
    int currCell;

    // Open file
    FILE* inFile = NULL;
    inFile = fopen(fileName.c_str(), "r");

    // If file not found or empty, just continue with program
    if(inFile == NULL)
    {
        return;
    }
    else
    {
        // Get width and height from file
        fscanf(inFile, "%d", &height);
        fscanf(inFile, "%d", &width);

        // Make room for data
        cadata = (unsigned char*)malloc(sizeof(unsigned char*) * (width * height));
        initCADATA = new unsigned char[width*height];

        // Set cells based on file
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                fscanf(inFile, "%d", &currCell);
                cadata[(i*width)+j] = (unsigned char) currCell;
                initCADATA[(i*width)+j] = (unsigned char) currCell;
            }
        }
    }

    // Pull the lever kronk!
    fclose(inFile);
}

CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& objToCopy)
{
    if(this != &objToCopy)
    {
        delete(cadata);
        delete(initCADATA);
        cadata = new unsigned char();
        initCADATA = new unsigned char();
        *cadata = *(objToCopy.cadata);
        *initCADATA = *(objToCopy.initCADATA);
        file = objToCopy.file;
        height = objToCopy.height;
        width = objToCopy.width;
    }
    return *this;
}

CellularAutomaton::~CellularAutomaton()
{
    delete(cadata);
    delete(initCADATA);
}

CellularAutomaton::CellularAutomaton(const CellularAutomaton& origObj)
{
    cadata = new unsigned char();
    initCADATA = new unsigned char();
    *cadata = *(origObj.cadata);
    *initCADATA = *(origObj.initCADATA);
    height = origObj.height;
    width = origObj.width;
    file = origObj.file;
}

void CellularAutomaton::step(unsigned char (*func)(CellularAutomaton*, int, int))
{
    // Temporary array to store data from the rule's function
    unsigned char tempArr[width*height];
    
    // Further error checking
    if(!tempArr)
    {
        printf("Issue with allocating memory.\n");
    }
    else
    {
        for(int i = 0; i < height; i++)
        { 
            for(int j = 0; j < width; j++)
            {
               tempArr[(i*width)+j] = func(this, j, i);
            }
        }

        for(int k = 0; k < (width*height); k++)
        {
            cadata[k] = tempArr[k];
        }
    }
}

void CellularAutomaton::display(GraphicsClient& obj)
{
    // Get cell size and gap based on CA size
    int m = std::max(width, height);
    int gap, cellSize;

    if(m > 200 && m <= 600)
    {
        cellSize = 1;
        gap = 0;
    }
    else if(m > 100 && m <= 200)
    {
        cellSize = 2;
        gap = 1;
    }
    else if(m > 50 && m <= 100)
    {
        cellSize = 4;
        gap = 1;
    }
    else if(m > 1 && m <= 50)
    {
        cellSize = 10;
        gap = 2;
    }

    // Draw each cell depending on state
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(cadata[(i*width)+j] == 1)
            {
                obj.setDrawingColor(0, 255, 0);
            }
            else
            {
                obj.setDrawingColor(0, 0, 0);
            }
            obj.fillRectangle((j * (cellSize + gap)), (i * (cellSize + gap)), cellSize, cellSize);
        }
    }
}

void CellularAutomaton::displayCA()
{
    // For sanity checking
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            printf("%u ", cadata[(i*width)+j]);;
        }
        printf("\n");
    }
    printf("\n");
}

void CellularAutomaton::displayInitCA()
{
    // For sanity checking
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            printf("%u ", initCADATA[(i*width)+j]);;
        }
        printf("\n");
    }
    printf("\n");
}

void CellularAutomaton::resetCA()
{
    // Sets ca data back to initial data
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cadata[(i*width)+j] = initCADATA[(i*width)+j];
        }
    }
}