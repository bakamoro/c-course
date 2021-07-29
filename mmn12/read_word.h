#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_SIZE 81
#define MAX_WORD_SIZE 81
int check_rest_of_line(char line[MAX_LINE_SIZE],int index){
	while(line[index] == ' ' || line[index] == '\t');
	if(line[index] == '\n'){
		return 1;
	}
	return 0;
}
int operand_chack(char * op,int line_num){
	if(op[0] != '$'){
		printf("ERROR LINE : %d - ILLEGLE HOARDER",line_num);
		return 0;
	}
	if(atoi(strstr(op,'$')) > 31){
		printf("ERROR LINE : %d - ILLEGLE HOARDER",line_num);
		return 0;
	}
	
}
//make a word from array of chasrs
int bilt_array(char p[],char p3[81],int i){
	int j = 0;
    while(i < MAX_WORD_SIZE && p[i] == ' ' || p[i] == '\n' || p[i] == '\t'){
        i++;
    }
	while(i < MAX_WORD_SIZE && p[i] != ' ' && p[i] != '\n' && p[i] != '\t'){
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
