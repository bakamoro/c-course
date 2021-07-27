#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_SIZE 81
#define MAX_WORD_SIZE 81
int check_rest_of_line(char line[MAX_LINE_SIZE],int index){
	while(line[index] == ' ' || line[index] == '\t'){
        index++;
    }
	if(line[index] == '\n'){
		return 0;
	}
	return 1;
}
int operand_chack(char * op,int line_num){
	int i = 1;
    if(op[0] != '$'){
		printf("ERROR LINE : %d - ILLEGLE HOARDER",line_num);
		return 0;
	}
    while(i < strlen(op) && op[i] != ' ' && op[i] != '\t' && op[i] != '\n'){
        if(!isdigit(op[i])){
            printf("ERROR LINE : %d - ILLEGLE HOARDER",line_num);
		    return 0;
        }
        i++;
    }
	if(atoi((op+1)) > 31){
		printf("ERROR LINE : %d - ILLEGLE HOARDER",line_num);
		return 0;
	}
	return 1;
}
//make a word from array of chasrs.
int bilt_array(char p[],char p3[],int i){
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