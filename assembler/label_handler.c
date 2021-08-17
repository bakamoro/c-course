#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read.h"
#include "line_handler.h"
#define MAX_LABLE_SIZE 31
size_t index_lable = 0;
/*
called / need_called - can be :
    1.'n' - for entry
    2.'x' - for external
    3.'N' - for NULL
*/
typedef struct lablea
{
    char name[MAX_LABLE_SIZE];
    char called;
    char need_called;
    int *line;
    int line_size;
}lable;
lable * lable_table;
/*chack if the lable is legal meens that :
    1.the label start with a letter (bid or small)
    2.the number of characters is smaller then 31
    3.if the label in the start of the line the label end with - ':'
    4.that all of the caracters are digit/letter
    if the label is not legal print why and return 0;
*/
int legal_label(char *name,char file_name[],int line_num,char start_line){
    int i = 1;
    if ((name[0] < 65 || name[0] > 122) || (name[0] > 90 && name[0] < 97))
    {
        printf("ERROR - file : %s - line : %d - illegal label not start with a letter : %s\n",file_name,line_num,name);
        return 0;
    }
    if(start_line == 'y'){
        if(strlen(name)-1 > MAX_LABLE_SIZE){
            printf("ERROR - file : %s - line : %d - illegal label : to many characters : %s\n",file_name,line_num,name);
            return 0;
        }
    }
    else if(strlen(name) > MAX_LABLE_SIZE){
        printf("ERROR - file : %s - line : %d - illegal label : to many charcters : %s\n",file_name,line_num,name);
        return 0;
    }
    if(in_comands_I(name)){
        printf("ERROR - file : %s - line : %d - illegal label : type comand I - %s\n",file_name,line_num,name);
        return 0;
    }
    if(in_comands_J(name)){
        printf("ERROR - file : %s - line : %d - illegal label : type comand J - %s\n",file_name,line_num,name);
        return 0;
    }
    if(in_comands_R(name)){
        printf("ERROR - file : %s - line : %d - illegal label : type comand R - %s\n",file_name,line_num,name);
        return 0;
    }
    if(in_instructions_1(name)){
        printf("ERROR - file : %s - line : %d - illegal label : type intruction - %s\n",file_name,line_num,name);
        return 0;
    }
    if(in_instructions_2(name)){
        printf("ERROR - file : %s - line : %d - illegal label : type intruction - %s\n",file_name,line_num,name);
        return 0;
    }
    while(i<strlen(name) && name[i] != '\n'){
        if(start_line == 'y'){
            if(i == strlen(name)-1){
                break;
            }
        }
        if((!isdigit(name[i])) && ((name[i] < 65 || name[i] > 122) || (name[i] > 90 && name[i] < 97))){
            printf("ERROR - file : %s - line : %d - illegal label : %s\n",file_name,line_num,name);
            return 0;
        }
        i++;
    }
    if(start_line == 'y'){
        if (name[strlen(name)-1] != ':')
        {
            printf("ERROR - file : %s - line : %d - illegal label : %s\n",file_name,line_num,name);
            return 0;
        }
    }
    return 1;
}
/*search if the label is in the lable_table if true return his index*/
int search_lable(char name[],char called,char need_called,int line_num){
    int i = 0;
    while (i < index_lable)
    {
        if(comper_words(name,lable_table[i].name)){
            if(line_num != 0){
                lable_table[i].line = realloc(lable_table[i].line,sizeof(int));
                lable_table[i].line[lable_table[i].line_size] =  line_num;
                lable_table[i].line_size++;
            }
            if(lable_table[i].need_called != 'N'){
                if(need_called == 'n')
                    lable_table[i].need_called = need_called;
            }
            if(called == 'n' || lable_table[i].called == 'N'){
                lable_table[i].called = called;
            }
            return 1;
        }
        i++;
    }
    return 0;
}
/*add label to the lable_table*/
void add_lable(char *name,char called,char need_called,int index,int line_num){
    static lable temp;
    if(index_lable == 0){
       lable_table = malloc(sizeof(lable));
    }
    else {
        lable_table = (lable *) (realloc(lable_table,sizeof(lable)*(index_lable+1)));
    }
    temp.line = malloc(sizeof(int));
    temp.line[0] = line_num;
    temp.line_size = 1;
    strcpy(temp.name,name);
    temp.called = called;
    temp.need_called = need_called;
    lable_table[index] = temp;
    index_lable++;
}
int find_label(char name[]){
    int i = 0;
    while(!comper_words(name,lable_table[i].name))i++;
    return 1;
}