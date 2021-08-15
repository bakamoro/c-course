#pragma once
#include "secondpass.h"

/*
 * retruns how many bits there are in guiadance command
 * @param name is the name of the command
 */

int getBits(char* name);

/*/
 * Check if a command is a guidance command
 * @param name is the command to be checked
 */


int isGuidance(char* name);

/*
 * returns the funct of given command
 * @param name is the name of the command
 */


int getFunct(char* name);

/*/
 * returns if the a number is out of boundry
 * @param num is the number to be checked
 */


int checkLimits(int num);

/*/
 * returns the Command Type of Instrucions
 * @param name is the instruction name
 */



char getType(char* name);

/*
 * reutrns the Opcode of instructions
 * @param name is the name of the instruction
 */


int getOpcode(char* name);

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
