#pragma once
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
    char name[LABEL_MAX_LEN];
    struct nodeExtern* next;



}nodeExtern;
/*
 * Adds commands which is using extern values
 * @param p_head is pointer to the extern table
 * @param name is the extern name
 * @param memValue is the Address of the command which used the extern
 */

void addNodeExtern(nodeExtern** p_head, char* name, int memValue);
/*
 * check if a label is extern label
 * @param p_head points to the symbol tabel
 * @param name is the label to be checked
 */


int isExtern(nodeSymbol** p_head, char* name);
/*
 *checks if there is entry label already exist
 *@param p_head points to the symbol tabel
 *@param name is the label to be checked
 */


int checkDuplAddressateExtern(nodeSymbol** p_head, char* name);
/*
 * The seconds pass on the input
 * @param head is the pointer to the Symbol Table
 * @param ptr is the pointer to the Code Machine table
 * @param e_node is the pointer to the externs table
 * @param filename is pointer to the input file
 */


int secondPass(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, FILE* filename);
