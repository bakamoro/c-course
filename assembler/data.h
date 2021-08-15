#pragma once
#include "globals.h"



typedef struct nodeMachine {

    int address;
    char code[MACH_CODE_SIZE];
    char type;
    struct nodeMachine* next;
}nodeMachine;


/*
 * *adds a new machine code word
 * @param ptr_head is pointer to to machine code table
 * @param memValue is the address of the command
 * @param machineCode is the binary num to be inserted
 * @param type determines if the command is instruction or data command
*/
void addMachineNode(nodeMachine** ptr_head, int memValue, char* machineCode,char type);

/*
 * Checks if a command has 32bits
 * @param ptr is pointer to the Machine Code Table
 * @param Address is the address of the command
 *
 */

int checkIfMissing(nodeMachine** ptr, int Address);

/*
 * returns a code machine of a given string
 * @param ptr is pointer to the machine code table
 * @param Address is the address of the needed machine code
 */


char* getString(nodeMachine** ptr, int Address);

/*
 * Initiallizing the machineCode collector
 * @param mach is array of the code
 */

void InitMachCode(char mach[]);


