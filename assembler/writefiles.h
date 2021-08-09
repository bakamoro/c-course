#ifndef WRITEFILES_H
#define WRITEFILES_H

#include "globals.h"
#include "firstpass.h"
#include "secondpass.h"
#include "data.h"
#include "utils.h"
#include "symbols.h"



void InitTempString(char temp[]);


void writeFiles(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC, char* filename);

void InitializeData(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC);


#endif
