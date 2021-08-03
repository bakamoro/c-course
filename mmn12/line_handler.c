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
    int i = 0;  
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
    int i = 0;
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
    int i = 0;
    char * instructions_1[4] = {".dw",".db",".dh",".asciz"};
    while(i < 5){
        if(comper_words(word,instructions_1[i])){
            return 1;
        }
        i++;
    }
    return 0;
}
int in_instructions_2(char word[]){
    int i = 0;
    char * instructions_2[2] = {".entry",".extern"};
    while(i < 2){
        if(comper_words(word,instructions_2[i])){
            return 1;
        }
        i++;
    }
    return 0;
}

int main_line(char *line,char *label,char file_name[],int line_num,int index,int a){
    char word[MAX_WORD_SIZE];
    if(a == 2){
        return 0;
    }
    index = bilt_array(line,word,index);
    if (a == 1 && !in_instructions_2(word))
    {
        label[strlen(label)-1] = '\0';
        if(!search_lable(label,'N',line_num)){
            label[strlen(label)] = ':';
            if(legal_label(label,file_name,line_num,'y')){
                add_lable(label,'N','N',index_lable,line_num);
            }
        }
    }
    if(in_comands_R(word)){
        //לשלוח לפונקציה שתאמת מספר אופרנדים וסוג
        incomand_R(line,word,file_name,line_num,index);
        return 1;
    }
    else if (in_comands_I(word)){
        incomand_I(line,word,file_name,line_num,index);
        return 1;
    }
    else if (in_comands_J(word)){
        incomand_J(line,word,file_name,line_num,index);
        return 1;
    }
    else if (in_instructions_1(word)){
        instructions_1(line,word,file_name,line_num,index);
        return 1;
    }
    else if (in_instructions_2(word)){
        instructions_2(line,word,file_name,line_num,index);
        return 1;
    }
    else return main_line(line,word,file_name,line_num,index,(++a));
}