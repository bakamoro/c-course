#include <stdio.h>
#include <string.h>
#include "read.h"
#include "label_handler.h"
#include "parameters_hundler.h"
#define MAX_WORD_SIZE  81
extern size_t index_lable;
/*check if the word is type comand R if not return 0*/
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
/*check if the word is type comand I if not return 0*/
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
/*check if the word is type comand J if not return 0*/
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
/*check if the word is in instructions_1 if not return 0*/
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
/*check if the word is in instructions_2 if not return 0*/
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
/*get line check first word :
    1.if label -> sarch if label already exist if does -> breake 
      if not check -> if ligal -> add_label , if not print error.

    2.chack if command/instructoin word exist if does send to functuon if not return 0*/
int main_line(char *line,char *label,char file_name[],int line_num,int index,int a){
    char word[MAX_WORD_SIZE];
    int i;
    if(a == 2){
        printf("ERROR - file : %s - line : %d - NO INSTRUCTUON OR COMAND FOUND\n",file_name,line_num);
        return 1;
    }
    index = bilt_array(line,word,index);
    if (a == 1)
    {
        if(legal_label(label,file_name,line_num,'y')){
            label[strlen(label)-1] = '\0';
            if(!search_lable(label,'N','N',line_num)){
                if(!in_instructions_2(word))
                    add_lable(label,'n','N',index_lable,line_num);
                }
            
            else {
                i = find_label(label);
                if(lable_table[i].called == 'x'){
                        printf("ERROR - file : %s - line : %d - label allrady called as external - %s\n",file_name,line_num,label);
                        return 1;
                    }
                lable_table[i].called = 'n';
            }
        }
    }
    if(in_comands_R(word)){
        return incomand_R(line,word,file_name,line_num,index);
    }
    else if (in_comands_I(word)){
        return incomand_I(line,word,file_name,line_num,index);
    }
    else if (in_comands_J(word)){
        return incomand_J(line,word,file_name,line_num,index);
    }
    else if (in_instructions_1(word)){
        return instructions_1(line,word,file_name,line_num,index);
    }
    else if (in_instructions_2(word)){
        return instructions_2(line,word,file_name,line_num,index);
    }
    else return main_line(line,word,file_name,line_num,index,(++a));
}