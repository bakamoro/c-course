#ifndef FIRSTPASS_H
#define FIRSTPASS_H
#include "secondpass.h"

int getBits(char* name);


int isGuidance(char* name);



int getFunct(char* name);



int checkLimits(int num);



char getType(char* name);


int getOpcode(char* name);


int firstPass(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC, FILE* filename);


#endif
