#include <stdio.h>
#include <string.h>
#include "read.h"
#include "label_handler.h"
#include "parameters_hundler.h"
#define MAX_WORD_SIZE  81
extern int index_lable;
int in_comands_R(char word[]){
    int i = 0;
    char * comands_R[8] = {"add","sub","and","or","nor","move","mvhi","mvlo"};
    while(i < 8){
        if(comper_words(word,comands_R[i])){
            return 1;
        }
        i++;
    }
    return 0;
}
int in_comands_I(char word[]){
    int i = 0,j = 0;
    char * comands_I[15] = {"addi","subi","andi","ori","nori","bne","beq","blt","bgt","lb","sb","lw","sw","lh","sh"};
    while(i < 15){
        if(comper_words(word,comands_I[i])){
            return 1;
        }
        i++;
    }
    return 0;
}
int in_comands_J(char word[]){
    int i = 0,j = 0;
    char * comands_J[4] = {"jmp","la","call","stop"};
    while(i < 4){
        if(comper_words(word,comands_J[i])){
            return 1;
        }
        i++;
    }
    return 0;
}
int in_instructions_1(char word[]){
    int i = 0,j = 0;
    char * instructions_1[5] = {".dd",".dw",".db",".dh",".asciz"};
    while(i < 5){
        if(comper_words(word,instructions_1[i])){
            return 1;
        }
        i++;
    }
    return 0;
}
int in_instructions_2(char word[]){
    int i = 0,j = 0;
    char * instructions_2[2] = {".entry",".extern"};
    while(i < 2){
        if(comper_words(word,instructions_2[i])){
            return 1;
        }
        i++;
    }
    return 0;
}

int main_line(char *line,char *label,int line_num,int index,int a){
    char word[MAX_WORD_SIZE];
    if(index > 0 && a == 2){
        return 0;
    }
    if (a == 1)
    {
        if(!search_lable(label,line_num)){
            if(legal_label(label,line_num,'y')){
                add_lable(label,'n',index_lable,line_num);
            }
        }
    }
    index = bilt_array(line,word,index);
    if(in_comands_R(word)){
        //לשלוח לפונקציה שתאמת מספר אופרנדים וסוג
        incomand_R(line,word,line_num,index);
        return 1;
    }
    else if (in_comands_I(word)){
       
        
        return 1;
    }
    else if (in_comands_J(word)){
        

        return 1;
    }
    else if (in_instructions_1(word)){
        

        return 1;
    }
    else if (in_instructions_2(word)){
        instructions_2(line,word,line_num,index);
        return 1;
    }
    else return main_line(line,word,line_num,index,(++a));
}