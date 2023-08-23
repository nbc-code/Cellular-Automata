#ifndef CA_H
#define CA_H
typedef struct ca_data CA_DATA;

    /* Struct representation of a 1DCA*/
    struct ca_data 
    {
        unsigned char *cells;
        int size;
        unsigned char wrapflag;
        unsigned char qstate;
        int numStates;
    };

    void init1DCA(CA_DATA* , int);

    int set1DCACell(CA_DATA* , unsigned int, unsigned char);
    
    void display1DCA(CA_DATA* );
    
    CA_DATA*  create1DCA(unsigned int, unsigned char);
    
    void stepCA(CA_DATA* , unsigned char (*)(CA_DATA* , int), int);

#endif