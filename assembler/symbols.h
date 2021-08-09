#ifndef SYMBOLS_H
#define SYMBOLS_H


typedef struct nodeSymbol {

    char name[31];
    int memValue;
    char attributes[2][7];
    struct nodeSymbol* next;
}nodeSymbol;


void addSymbolNode(nodeSymbol** p_head, char* name, int memValue, char* attribute);



int searchSymbol(nodeSymbol** p_head, char* name);



int returnAddress(nodeSymbol** p_head, char* name);




void addAttribute(nodeSymbol** p_head, char* name, char* attribute);

#endif
