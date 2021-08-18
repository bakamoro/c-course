#pragma once
#include "secondpass.h"

void proccessGuidance(char* token ,int* Address,int* DC,int* LC,nodeMachine** ptr,char* machCode);

int proccessInstruction(char* token ,int* Address,int* LC ,nodeSymbol** head,nodeMachine** ptr,char* machCode);

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
