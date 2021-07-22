#include <stdio.h>
#include <string.h>
//make a word from array of chasrs
int bilt_array(char p[],char p3[],int i){
	int j = 0;
    while(i < 81 && p[i] == ' ' || p[i] == '\n' || p[i] == '\t'){
        i++;    
    }
	while(i<81 && p[i] != ' ' && p[i] != '\n' && p[i] != '\t'){
		p3[j] = p[i];
		j++;
		i++;
	}
	if (p[i] == '\n')
	{
		p3[j] = p[i];
	}
	return i;
}

int in_comands_R(char word[]){
    int i = 0,j = 0;
    char * comands_R[8] = {"add","sub","and","or","nor","move","mvhi","mvlo"};
    while(i < 8){
        while(j<strlen(word) && word[j] == comands_R[i][j] && word[j] != '\0' && word[j] != '\n'){
            j++;
            if (j == strlen(word))
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
        while(j < 81 && word[j] == comands_I[i][j] && word[j] != '\0' && word[j] != '\n'){
            j++;
            if (j == strlen(word))
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
    while(strlen(word) == strlen(comands_J[i]) && i < 4){
        while(j < 81 && word[j] == comands_J[i][j] && word[j] != '\0' && word[j] != '\n'){
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
int in_instructions(char word[]){
    int i = 0,j = 0;
    char * instructions[7] = {".dd",".dw",".db",".dh",".asciz",".entry",".extern"};
    while(i < 7){
        while(j < 81 && word[j] == instructions[i][j] && word[j] != '\0' && word[j] != '\n'){
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
    char word[81];
    if(index > 0 && a != 0){
        return 0;
    }
    index = bilt_array(line,word,index);
    if(in_comands_R(word)){

        return 1;
    }
    else if (in_comands_I(word)){

        return 1;
    }
    else if (in_comands_J(word)){

        return 1;
    }
    else if (in_instructions(word)){

        return 1;
    }
    else main_line(line,line_num,(index+1),1);
}