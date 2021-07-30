#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_SIZE 81
#define MAX_WORD_SIZE 81

//check if the string is liglle number.
int number_check(char s[],int line_number){
	int i = 0;
	while(i < strlen(s)){
		if(s[i] == '.'){
			printf("ERROR - line : %d - the asembler does not support decimal numbers\n",line_number);
			return 0;
		}
		if(!(isdigit(s[i]))){
			return 0;
        }
		i++;
	}
    if(atoi(s) > 32767){
        printf("EOOR - line : %d - number too big - %s",line_number,s);
        return 0;
    }
    if(atoi(s) < 32767){
        printf("EOOR - line : %d - number too small - %s",line_number,s);
        return 0;
    }
    return 1;
}

//check if the rest of the line is not empty.
int check_rest_of_line(char line[MAX_LINE_SIZE],int index){
	while(line[index] == ' ' || line[index] == '\t'){
        index++;
    }
	if(line[index] == '\n'){
		return 0;
	}
	return 1;
}
//check if the hourder id liggle;
int operand_chack(char op[4],int line_num){
	int i = 1;
    if(strlen(op) < 2 || op[1] == '\n'){
        printf("ERROR LINE : %d - ILLEGLE HOARDER - %s\n",line_num,op);
		return 0;
    }
    if(op[0] != '$'){
		printf("ERROR LINE : %d - ILLEGLE HOARDER - %s\n",line_num,op);
		return 0;
	}
    while(i < strlen(op) && op[i] != ' ' && op[i] != '\t' && op[i] != '\n'){
        if(!isdigit(op[i])){
            printf("ERROR LINE : %d - ILLEGLE HOARDER - %s\n",line_num,op);
		    return 0;
        }
        i++;
    }
	if(atoi((op+1)) > 31){
		printf("ERROR LINE : %d - ILLEGLE HOARDER - %s\n",line_num,op);
		return 0;
	}
	return 1;
}
int operand_chack_binnar(char op[4]){
	int i = 1;
    if(strlen(op) < 2 || op[1] == '\n'){
		return 0;
    }
    if(op[0] != '$'){
		return 0;
	}
    while(i < strlen(op) && op[i] != ' ' && op[i] != '\t' && op[i] != '\n'){
        if(!isdigit(op[i])){
		    return 0;
        }
        i++;
    }
	if(atoi((op+1)) > 31){
		return 0;
	}
	return 1;
}
int comper_words(char *label1,char *label2){
    int i = 0;
    while(label1[i] == label2[i] && label2[i] != '\n' && label1[i] != '\n' && label1[i] != '\0' && label2[i] != '\0'){
        i++;
    }
    if ((label2[i] == '\n' || label2[i] == '\0') && (label1[i] == '\n' || label1[i] == '\0'))
    {
        return 1;
    }
    return 0;
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
    else p3[j] = '\0';
	return i;
}