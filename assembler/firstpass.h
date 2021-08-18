#pragma once
#include "secondpass.h"

/*
 *This Method is proccesing guidance commands and adding their binary code to the Machine code Table
 *This @param token is the command
 *This @param DC is the Data counter
 *This @param LC is the line counter
 *This @param ptr is a pointer to the machine code Table
 *This param machCode is the array of the binary string to be added to the machine code table
 */


void proccessGuidance(char* token ,int* DC,int* LC,nodeMachine** ptr,char* machCode);

/*
 * this method is proccesing Instructions commands and adding their binary code to the machine code table
 */
int proccessInstruction(char* token ,int* LC ,int* IC , nodeSymbol** head,nodeMachine** ptr,char* machCode);

/*
 * first pass on the input file , setting all the labels in the symbol table , creating the machine code table
 * counts the instructions and the data .
 * @param head is a pointer to the Symbol table
 * @param ptr is a pointer to Machine code table
 * @param e_node is a pointer to the Externs Table
 * @param DC is the Data counter
 * @param Ic is the instruction counter
 * param filename is the pointer to the input file
 */



int firstPass(nodeSymbol** head, nodeMachine** ptr, nodeExtern** e_node, int* DC, int* IC, FILE* filename);
