#ifndef CA_H
#define CA_H
typedef struct ca_data CA_DATA;

    /*  Struct representation of a CA   */
    struct ca_data 
    {
        unsigned char wrapflag;
        int numStates;
        unsigned char qstate;
        unsigned char *cadata;
        unsigned char dimension;
        unsigned char wrap;
        int width;
        int height;
    };

    // Initialize CA
    void initCA(CA_DATA* , int);

    // Set specified cell to specified state
    int set1DCACell(CA_DATA* , unsigned int, unsigned char);

    // Set specified cell to specified state (but for 2! D!!!)
    int set2DCACell(CA_DATA*, unsigned int, unsigned int, unsigned char);
    
    // Print out each cell in CA
    void displayCA(CA_DATA* );
    
    // Create our 1DCA
    CA_DATA* create1DCA(int, unsigned char);
    
    // Create our 2DCA
    CA_DATA* create2DCA(int, int, unsigned char);

    // Preform one iteration of a given rule on our 1DCA
    void step1DCA(CA_DATA* , unsigned char (*)(CA_DATA* , int));

    // Preform one iteration of a given rule on our 2DCA
    void step2DCA(CA_DATA*, unsigned char (*)(CA_DATA*, int, int));

#endif