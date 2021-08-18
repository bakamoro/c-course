#pragma once
#include "globals.h"

typedef struct nodeSymbol {

    char name[LABEL_MAX_LEN];
    int memValue;
    char attributes[2][7];
    struct nodeSymbol* next;
}nodeSymbol;

/*
 * adds a new Symbol to the Symbol table
 * @param p_head pointer to the head of the symbol table
 * @param name is the new symbol name
 * @param memValue is the Address of the new symbol
 * @param attribute is the attribute of the new symbol
 */


void addSymbolNode(nodeSymbol** p_head, char* name, int memValue, char* attribute);
/*
 * Searchers if a symbol is exist in the symbol table
 * @param p_head is a pointer to the head of the table
 * @param name is the name of the symbol that needs to be searched
 */


int searchSymbol(nodeSymbol** p_head, char* name);
/*
 * Returns the addresss of a certain symbol
 * @param p_head is pointer to the head of the table
 * @param name is the name of the symbol who's address needs to be returned
 */


int returnAddress(nodeSymbol** p_head, char* name);
/*
 * adds a attribute to symbol if needed (extern / entry)
 * @param p_head is pointer to the head of the table
 * @param attribute is the attribute added attribute
 */



void addAttribute(nodeSymbol** p_head, char* name, char* attribute);


void updateAddress(nodeSymbol** p_head , int* ICF);
