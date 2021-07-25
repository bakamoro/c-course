#include <stdio.h>
#include <string.h>
#include "read_word.h"
#include "label_handler.h"
#define MAX_WORD_SIZE  81
int in_comands_R(char word[]){
    int i = 0,j = 0;
    char * comands_R[8] = {"add","sub","and","or","nor","move","mvhi","mvlo"};
    while(i < 8){
        while(j<MAX_WORD_SIZE && word[j] == comands_R[i][j] && word[j] != '\0' && word[j] != '\n'){
            j++;
            if (j == MAX_WORD_SIZE)
            {
                return 1;
            }
        }
        i++;
    }
    return 0;
}
int in_comands_I(char word[]){
    int i = 0,j = 0;
    char * comands_I[15] = {"addi","subi","andi","ori","nori","bne","beq","blt","bgt","lb","sb","lw","sw","lh","sh"};
    while(i < 15){
        while(j < MAX_WORD_SIZE && word[j] == comands_I[i][j] && word[j] != '\0' && word[j] != '\n'){
            j++;
            if (j == MAX_WORD_SIZE)
            {
                return 1;
            }
        }
        i++;
    }
    return 0;
}
int in_comands_J(char word[]){
    int i = 0,j = 0;
    char * comands_J[4] = {"jmp","la","call","stop"};
    while(i < 4){
        while(j < MAX_WORD_SIZE && word[j] == comands_J[i][j] && word[j] != '\0' && word[j] != '\n'){
            j++;
            if (word[j] == '\0')
            {
                return 1;
            }
        }
        i++;
    }
    return 0;
}
int in_instructions_1(char word[]){
    int i = 0,j = 0;
    char * instructions[5] = {".dd",".dw",".db",".dh",".asciz"};
    while(i < 7){
        while(j < MAX_WORD_SIZE && word[j] == instructions[i][j] && word[j] != '\0' && word[j] != '\n'){
            j++;
            if ('\0' == word[j])
            {
                return 1;
            }
        }
        i++;
    }
    return 0;
}
int in_instructions_2(char word[]){
    int i = 0,j = 0;
    char * instructions[2] = {".entry",".extern"};
    while(i < 7){
        while(j < MAX_WORD_SIZE && word[j] == instructions[i][j] && word[j] != '\0' && word[j] != '\n'){
            j++;
            if ('\0' == word[j])
            {
                return 1;
            }
        }
        i++;
    }
    return 0;
}

int main_line(char *line,int line_num,int index,int a){
    char word[MAX_WORD_SIZE];
    if(index > 0 && a == 2){
        return 0;
    }
    index = bilt_array(line,word,index);
    if(in_comands_R(word)){
        if (a == 1)
        {
            if(!search_lable(word)){
                add_lable(word,'n',index_lable,line_num);
                index_lable++;
            }
        }
        //לשלוח לפונקציה שתאמת מספר אופרנדים וסוג
        
        return 1;
    }
    else if (in_comands_I(word)){
       if (a == 1)
        {
            if(!search_lable(word)){
                add_lable(word,'n',index_lable,line_num);
                index_lable++;
            }
        }

        return 1;
    }
    else if (in_comands_J(word)){
        if (a == 1)
        {
            if(!search_lable(word)){
                add_lable(word,'n',index_lable,line_num);
                index_lable++;
            }
        }

        return 1;
    }
    else if (in_instructions_1(word)){
        if (a == 1)
        {
            if(!search_lable(word)){
                add_lable(word,'n',index_lable,line_num);
                index_lable++;
            }
        }
        return 1;
    }
    else if (in_instructions_2(word)){
        if (a == 1)
        {
            if(!search_lable(word)){
                add_lable(word,'n',index_lable,line_num);
                index_lable++;
            }
        }
        
        return 1;
    }
    else main_line(line,line_num,index,(++a));
}