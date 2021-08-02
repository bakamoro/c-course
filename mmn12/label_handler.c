#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read.h"
#define MAX_LABLE_SIZE 31
int index_lable = 0;
typedef struct lablea
{
    char name[MAX_LABLE_SIZE];
    char called;
    char ex;
    int *line;
    int line_size;
}lable;
lable * lable_table;
int legal_label(char *name,int line_num,char start_line){
    int i = 1;
    if ((name[0] < 65 || name[0] > 122) || (name[0] > 90 && name[0] < 97))
    {
        printf("ERROR - line : %d - illegal label not start with a letter : %s\n",line_num,name);
        return 0;
    }
    if(start_line == 'y'){
        if(strlen(name)-1 > MAX_LABLE_SIZE){
            printf("ERROR - line : %d - illegal label : to many letters : %s\n",line_num,name);
            return 0;
        }
    }

    else if(strlen(name) > MAX_LABLE_SIZE){
        printf("ERROR - line : %d - illegal label : to many letters : %s\n",line_num,name);
        return 0;
    }
    while(i<strlen(name) && name[i] != '\n'){
        if(start_line == 'y'){
            if(i == strlen(name)-1){
                return 1;
            }
        }
        if((!isdigit(name[i])) && ((name[i] < 65 || name[i] > 122) || (name[i] > 90 && name[i] < 97))){
            printf("ERROR - line : %d - illegal label : %s\n",line_num,name);
            return 0;
        }
        if(name[i] != '\0' && name[i] != '\n'){
            return 1;
        }
        i++;
    }
    if(start_line == 'y'){
        if (name[strlen(name)-1] != ':')
        {
            printf("ERROR - line : %d - illegal label : %s\n",line_num,name);
            return 0;
        }
    }
    return 1;
}
int legal_label_binar(char *name){
    int i = 1;
    if ((name[0] < 65 || name[0] > 122) || (name[0] > 90 && name[0] < 97))
    {
        return 0;
    }
    else if(strlen(name) > MAX_LABLE_SIZE){
        return 0;
    }
    while(i<strlen(name)){
        if((!isdigit(name[i])) && ((name[i] < 65 || name[i] > 122) || (name[i] > 90 && name[i] < 97))){
            return 0;
        }
        if(name[i] != '\0' && name[i] != '\n'){
            return 1;
        }
        i++;
    }
    return 1;
}
int search_lable(char name[],int line_num){
    int i = 0;
    while (i < index_lable)
    {
        if(comper_words(name,lable_table[i].name)){
            lable_table[i].line = realloc(lable_table->line,sizeof(int));
            lable_table[i].line[lable_table->line_size] =  line_num;
            lable_table[i].line_size++;
            return i;
        }
        i++;
    }
    return 0;
}
void add_lable(char *name,char called,int index,int line_num){
    if(index_lable == 0){
       lable_table = malloc(sizeof(lable)); 
    }
    else {
        lable_table = reallocarray(lable_table,sizeof(lable),index_lable+1);
    }
    static lable temp;
    name[strlen(name)-1] = '\0';
    temp.line = malloc(sizeof(int));
    temp.line[0] = line_num;
    temp.line_size = 1;
    strcpy(temp.name,name);
    temp.called = called;
    lable_table[index] = temp;
    index_lable++;
}