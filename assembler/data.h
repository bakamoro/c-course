#ifndef DATA_H
#define DATA_H
typedef struct nodeMachine {

    int address;
    char code[33];
    struct nodeMachine* next;
}nodeMachine;




void addMachineNode(nodeMachine** ptr_head, int memValue, char* machineCode);




int checkIfMissing(nodeMachine** ptr, int Address);


char* getString(nodeMachine** ptr, int Address);



void InitMachCode(char mach[]);

#endif
