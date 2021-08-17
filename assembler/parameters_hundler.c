#include <stdio.h>
#include "read.h"
#include "label_handler.h"
#include "hash_table.h"
/*get line and instruction in instruction_2 and check :
    1.the num of parameters equal 1
    2.the label is lagal
    if it's all proper : 
    activate search_label and send type of called(extern - 'x' , entry - 'n')
    if there is not such label chack thet the abel is legal with legal_label and add it to lable_tabel withe add_label
    if there is an error return 1 if not return 0
*/
    int instructions_2(char line[81],char instruction[],char file_name[],int line_num,int index){
    char label[MAX_LABLE_SIZE];
    int num_of_pa = 0;
    int i = 0;
    while(check_rest_of_line(line,index)){
        index = bilt_array(line,label,index);
        num_of_pa++;
        if(num_of_pa == 2){
            printf("ERROR - file : %s - line : %d - TO MANY PARAMETERS\n",file_name,line_num);
            return 1;
        }
        if(legal_label(label,file_name,line_num,'n')){
            if((search_lable(label,'N','N',line_num))){
                i = find_label(label);
                if(lable_table[i].called != 'N'){
                    printf("ERROR - file : %s - line : %d - label allrady called - %s\n",file_name,line_num,label);
                    return 1;
                }
                if(comper_words(instruction,".extern")){
                    lable_table[i].called = 'x';
                }
                else lable_table[i].called = 'n';
            }
            else {
                if(comper_words(instruction,".extern")){
                    add_lable(label,'x','N',index_lable,line_num);
                    index_lable++;
                }
                else {
                    add_lable(label,'n','N',index_lable,line_num);
                    index_lable++;
                }
            }
        }
        else return 1;
    }
    if(num_of_pa == 0){
        printf("ERROR - file : %s - line : %d - TO FEW PARAMETERS\n ",file_name,line_num);
        return 1;
    }
    return 0;
}
/*
get line and instruction in instruction_1 and check :
    1.if the instruction is ascis in not continue if does :
        check:
            1.the string is legal.
            2.the only paarmeter ids string.

    2.find out wich instruction is it and give the right size.

    3.there is a comma betwin parameters

    4.chack that all parameters are legal numbers -
    if does return 0,
    if not return 1.
*/
int instructions_1(char line[81],char comand_name[],char file_name[],int line_num,int index){
    char asciz[] = ".asciz";
    char string[MAX_WORD_SIZE-7];
    char operand[16];
    char * instruction[3] = {".dh",".db",".dw"};
    int size_db = 8,size_dw = 32,size_dh = 16;
    int size = 0;
    int need_coma = 0;
    if(comper_words(comand_name,asciz)){
        index = bilt_array(line,string,index);
        if(!string_check(string)){
            printf("ERROR - file : %s - line : %d - illegil string\n",file_name,line_num);
            return 1;
        }
        return 0;
    }
    if(comper_words(comand_name,instruction[0])){
        size = size_dh;
    }
    if(comper_words(comand_name,instruction[1])){
        size = size_db;
    }
    if(comper_words(comand_name,instruction[2])){
        size = size_dw;
    }
    while(check_rest_of_line(line,index)){
        index = bilt_array(line,operand,index);
        if(need_coma){
            if(operand[0] == ','){
                index = bilt_array(line,operand,index);
            }
            else{
                printf("ERROR - file : %s - line : %d - missing comma\n",file_name,line_num);
                return 1;
            }
        }
        else need_coma = 1;
        number_check(operand,file_name,line_num,size);
    }
    return 0;
}
/*
get line and command in comand R , bilt arr_comand_R and check :
    1.there is a comma betwin parameters
    2.chack that the number of parameters is same as the label tabel .
    3.check that all parameters are registers.
    4.chack that all registers are legal.
    if all this is true return 0 if not return 1.
*/
int incomand_R(char line[81],char comand_name[],char file_name[],int line_num,int index){
    int i = 0 ,need_coma = 0;
    int register_num = 0;
    char re[4];
    char * comands_R[8] = {"add","sub","and","or","nor","move","mvhi","mvlo"};
    comand_R * arr_comand_R = bilt_array_R(comands_R);
    while(check_rest_of_line(line,index) && register_num < 4){
        index = bilt_array(line,re,index);
        if(need_coma){
            if(re[0] == ','){
                index = bilt_array(line,re,index);
            }
            else{
                printf("ERROR - file : %s - line : %d - missing comma\n",file_name,line_num);
                return 1;
            }
        }
        else need_coma = 1;
        if(!operand_chack(re,file_name,line_num)){
            return 1;
        }
        register_num++;
    }
    if(register_num == 4){
        printf("ERROR - file : %s - line : %d - to many oparends\n",file_name,line_num);
        return 1;
    }
    while(!comper_words(comand_name,arr_comand_R[i].name)){
        i++;
    }
    if(arr_comand_R[i].num_of_op < register_num){
        printf("ERROR - file : %s - line : %d - to many oparends\n",file_name,line_num);
        return 1;
    }
    if(arr_comand_R[i].num_of_op > register_num){
        printf("ERROR - file : %s - line : %d - to few oparends\n",file_name,line_num);
        return 1;
    }
    return 0;
}
/*
get line and command in comand I and bilt arr_comand_I and check :
    1.there is a comma betwin parameters
    2.give type to all the parameters
    3.if there label parameter activate : sarch -> lagal -> add
    4.chck that number of parameters equal to number of parameters in arr_comand_I
    5.chck that type of parameters equal to type of parameters in arr_comand_I
    if all this is true return 0 if not return 1.
*/
int incomand_I(char line[81],char comand_name[],char file_name[],int line_num,int index){
    char * comands_I[15] = {"addi","subi","andi","ori","nori","lb","sb","lw","sw","lh","sh","bne","beq","blt","bgt"};
    comand_I * arr_comand_I = bilt_array_I(comands_I);
    char operand[MAX_LABLE_SIZE];
    char op_1[MAX_LABLE_SIZE],op_2[MAX_LABLE_SIZE],op_0[MAX_LABLE_SIZE];
    char i_0,i_1,i_2;
    int i = 0;
    int num_of_op = 0 , need_comma = 0;
    int need_label = 0;
    i = 11;
    while(i<15){
        if(comper_words(comand_name,comands_I[i])){
            need_label = 1;
            break;
        }
        i++;
    }
    i = 0;
    while(check_rest_of_line(line,index) && num_of_op < 4){
        index = bilt_array(line,operand,index);
        if(need_comma){
            if(operand[0] == ','){
                index = bilt_array(line,operand,index);
            }
            else{
                printf("ERROR - file : %s - line : %d - missing comma\n",file_name,line_num);
                return 1;
            }
        }
        else need_comma = 1;
        if(operand[0] == '$'){
            if (i == 0){
                i_0 = 'h';
                strcpy(op_0,operand);
            }
            if(i == 1){
                i_1 = 'h';
                strcpy(op_1,operand);
            }
            if(i == 2){
                i_2 = 'h';
                strcpy(op_2,operand);
            }
            operand_chack(operand,file_name,line_num);
        }
        else if(isdigit(operand[0]) || operand[0] == '+' || operand[0] == '-'){
                if (i == 0){
                    i_0 = 'n';
                    strcpy(op_0,operand);
                }
                if(i == 1){
                    i_1 = 'n';
                    strcpy(op_1,operand);
                }
                if(i == 2){
                    i_2 = 'n';
                    strcpy(op_2,operand);
                }
                number_check(operand,file_name,line_num,16);
           }
        else {
            if (i == 0){
                i_0 = 'l';
                strcpy(op_0,operand);
            }
            if(i == 1){
                i_1 = 'l';
                strcpy(op_1,operand);
            }
            if(i == 2){
                i_2 = 'l';
                strcpy(op_2,operand);
            }
            if(need_label){
                if(legal_label(operand,file_name,line_num,'n')){
                    if(!search_lable(operand,'N','n',line_num)){
                        add_lable(operand,'N','n',index_lable,line_num);
                    }
                }
            }
        }
        num_of_op++;
        i++;
    }
    if(num_of_op == 4){
        printf("ERROR - file : %s - line : %d - to many parameters\n",file_name,line_num);
        return 1;
    }
    i = 0;
    while(!comper_words(comand_name,arr_comand_I[i].name)){
        i++;
    }
    if(arr_comand_I[i].num_of_op > num_of_op){
        printf("ERROR - file : %s - line : %d - too few parameters\n",file_name,line_num);
        return 1;
    }
    if(i_0 != arr_comand_I[i].operands_type[0]){
        printf("ERROR - file : %s - line : %d - word is : %s - type is - %c , type suppose to be - %c\n",file_name,line_num,op_0,i_0,arr_comand_I[i].operands_type[0]);
        return 1;
    }
    if(i_1 != arr_comand_I[i].operands_type[1]){
        printf("ERROR - file : %s - line : %d - word is : %s - type is - %c , type suppose to be - %c\n",file_name,line_num,op_1,i_1,arr_comand_I[i].operands_type[1]);
        return 1;
    }
    if(i_2 != arr_comand_I[i].operands_type[2]){
        printf("ERROR - file : %s - line : %d - word is : %s - type is - %c , type suppose to be - %c\n",file_name,line_num,op_2,i_2,arr_comand_I[i].operands_type[2]);
        return 1;
    }
    return 0;
}
/*
get line and command in comand I and bilt arr_comand_J and :
    1.chack that there is a comma betwin parameters
    2.give type to all the parameters
    3.if there label parameter activate : sarch -> lagal -> add
    4.chck that number of parameters equal to number of parameters in arr_comand_J
    5.chck that type of parameters equal to type of parameters in arr_comand_J
    if all this is true return 0 if not return 1.
*/

int incomand_J(char line[81],char comand_name[],char file_name[],int line_num,int index){
    char * comands_J[4] = {"jmp","la","call","stop"};
    comand_J * arr_comand_j = bilt_array_J(comands_J);
    char operand[MAX_LABLE_SIZE],op_1[MAX_LABLE_SIZE];
    int i = 0,num_of_op = 0,need_comma = 0;
    char type = 'N';
    while(check_rest_of_line(line,index) && num_of_op < 2){
        index = bilt_array(line,operand,index);
        if(need_comma){
            if(operand[0] == ','){
                index = bilt_array(line,operand,index);
            }
            else{
                printf("ERROR - file : %s - line : %d - missing comma\n",file_name,line_num);
                return 1;
            }
        }
        else need_comma = 1;
        if(operand[0] == '$'){
            if(i == 0){
                type = 'r';
            }
        }
        else if(isdigit(operand[i])){
            if(i == 0){
                type = 'n';
            }
        }
        else{
            if(i == 0){
                type = 'l';
            }
            if(legal_label(operand,file_name,line_num,'n')){
                if(!search_lable(operand,'N','y',line_num)){
                    add_lable(operand,'N','y',index_lable,line_num);
                }
            }
        }
        if(i == 0){
            strcpy(op_1,operand);
        }
        num_of_op++;
        i++;
    }
    if(num_of_op == 2){
        printf("ERROR - file : %s - line : %d - to many parameters\n",file_name,line_num);
        return 1;
    }
    i = 0;
    while(!comper_words(comand_name,arr_comand_j[i].name))i++;
    if(arr_comand_j[i].num_of_op > num_of_op){
        printf("ERROR - file : %s - line : %d - too few parameters\n",file_name,line_num);
        return 1;
    }
    if(type != arr_comand_j[i].type_1 && type != arr_comand_j[i].type_2){
        if(arr_comand_j[i].type_2 != 'N'){
            printf("ERROR - file : %s - line : %d - word is : %s - type is - %c , type suppose to be - %c / %c\n",file_name,line_num,op_1,type,arr_comand_j[i].type_1,arr_comand_j[i].type_2);
        }
        else printf("ERROR - file : %s - line : %d - word is : %s - type is - %c , type suppose to be - %c \n",file_name,line_num,op_1,type,arr_comand_j[i].type_1);
        return 1;
    }
    return 0;
}