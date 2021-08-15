#pragma once
#include "globals.h"
#include "firstpass.h"
#include "secondpass.h"
#include "data.h"
#include "symbols.h"

/*
 * Initialize the String which holds the binary number that converted to Hex
 * @param temp is the array of the string
 */

void InitTempString(char temp[]);
/*
 * Writing the files if there are no errors
 * @param head is the pointer to the symbol table
 * @param ptr is the pointer to the Machine code table
 * @param e_node is the pointer to the Extern table
 * @param DC is the data counter
 * @param IC the instruction counter
 * @param filename is the pointer to name of the file
 */

void writeFiles(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC, char* filename);


void InitializeData(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC);
