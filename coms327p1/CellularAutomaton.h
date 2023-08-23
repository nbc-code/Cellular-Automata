#ifndef CELLULAR_AUTOMATON_H
#define CELLULAR_AUTOMATON_H
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<fstream>
#include"GraphicsClient.h"

class CellularAutomaton
{
    public:
        CellularAutomaton(int, int);
        CellularAutomaton(std::string, int);
        CellularAutomaton(const CellularAutomaton& origObj);
        ~CellularAutomaton();
        CellularAutomaton& operator=(const CellularAutomaton& objToCopy);
        void changeCell(int, int, GraphicsClient*);
        void displayInitCA();
        void resetCA();
        void step(unsigned char (*)(CellularAutomaton*, int, int));
        void display(GraphicsClient& obj);
        void step2DCA(CellularAutomaton*, unsigned char (*)(CellularAutomaton*, int, int));
        void displayCA();

        std::string file;
        int qstate;

        // working ca data
        unsigned char *cadata;
        // initial ca data
        unsigned char *initCADATA;
        int width;
        int height;

    private:
};

#endif