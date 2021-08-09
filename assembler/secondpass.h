#ifndef SECONDPASS_H
#define SECONDPASS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>
#include "globals.h"
#include "symbols.h"
#include "data.h"
#include "helpers.h"
#include "firstpass.h"

typedef struct nodeExtern {
    int memValue;
    char name[31];
    struct nodeExtern* next;



}nodeExtern;


void addNodeExtern(nodeExtern** p_head, char* name, int memValue);



int isExtern(nodeSymbol** p_head, char* name);




int checkDuplAddressateExtern(nodeSymbol** p_head, char* name);


int secondPass(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, FILE* filename);


#endif
