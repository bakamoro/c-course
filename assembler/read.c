#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_SIZE 81
#define MAX_WORD_SIZE 81

double power(int num,double po){
	int i = 1;
	double sum = 1;
	while (i < po)
	{
		sum *= num;
		i++;
	}
	return sum;
}
/*check if the string is liglle number.
הודק האם המספר שלם ועשוי כולו מספרות ויכול להיכנס ל -16 סיביות בשיטת המשלים. */
int number_check(char s[],char file_name[],int line_number,int bit){
	int i = 0;
	if(s[0] == '+' || s[0] == '-'){
		i++;
	}
	while(i < strlen(s)){
		if(s[i] == '.'){
			printf("ERROR - file : %s - line : %d - the asembler does not support decimal numbers\n",file_name,line_number);
			return 0;
		}
		if(!(isdigit(s[i])) && s[i] != '\n'){
			printf("ERROR - file : %s - line : %d - illegil number\n",file_name,line_number);
			return 0;
        }
		i++;
	}
    if(atol(s) > power(2,bit)){
        printf("ERROR - file : %s - line : %d - number too big - %s\n",file_name,line_number,s);
        return 0;
    }
    if(atol(s) < -1*(power(2,bit))){
        printf("EORROR - file : %s - line : %d - number too small - %s\n",file_name,line_number,s);
        return 0;
    }
    return 1;
}
/*check if the rest of the line is not empty*/
int check_rest_of_line(char line[MAX_LINE_SIZE],int index){
	while(line[index] == ' ' || line[index] == '\t'){
        index++;
    }
	if(line[index] == '\n'){
		return 0;
	}
	return 1;
}
/*check if the register is liggle*/
int operand_chack(char op[4],char file_name[],int line_num){
	int i = 1;
    if(strlen(op) < 2 || op[1] == '\n'){
        printf("ERROR - file : %s - line : %d - ILLEGLE register - %s\n",file_name,line_num,op);
		return 0;
    }
    if(op[0] != '$'){
		printf("ERROR - file : %s - line : %d - ILLEGLE register - %s\n",file_name,line_num,op);
		return 0;
	}
    while(i < strlen(op) && op[i] != ' ' && op[i] != '\t' && op[i] != '\n'){
        if(!isdigit(op[i])){
            printf("ERROR - file : %s - line : %d - ILLEGLE register - %s\n",file_name,line_num,op);
		    return 0;
        }
        i++;
    }
	if(atoi((op+1)) > 31 && atoi((op+1)) < 0){
		printf("ERROR - file : %s - line : %d - ILLEGLE register - %s\n",file_name,line_num,op);
		return 0;
	}
	return 1;
}

int string_check(char *string){
	if(string[0] == '"' && string[strlen(string)-1]){
		return 1;
	}
	return 0;
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
/*read word from line*/
int bilt_array(char p[],char p3[],int i){
	int j = 0;
    while(i < MAX_WORD_SIZE && (p[i] == ' ' || p[i] == '\n' || p[i] == '\t')){
        i++;
    }
	if(p[i] == '"'){
		while(p[i] != '\n' && p[i] != '"'){
			p3[j] = p[i];
			i++;
			j++;
		}
	}
	while(i < MAX_WORD_SIZE && p[i] != ' ' && p[i] != '\n' && p[i] != '\t'){
		if(p[i] == ','){
			if(j == 0){
				p3[j] = p[i];
				i++;
				j++;
			}
			break;
		}
		p3[j] = p[i];
		j++;
		i++;
	}
	if (p[i] == '\n')
	{
		p3[j] = p[i];
		j++;
	}
	p3[j] = '\0';
	return i;
}
void subtract_space(char file_name[],char FILE_NAME[]){
	FILE * fd_one = fopen(file_name,"r");
	FILE * fd_two = fopen(FILE_NAME,"w");
	int num_space = 0,start_line = 1;
	int line_num = 1;
	int dequmention_line = 0;
	int comma = 0;
	char c;
	while((!feof(fd_one))){
		c = fgetc(fd_one);
		if(start_line == 1 && c == ';'){
			dequmention_line = 1;
		}
		if(dequmention_line == 1){
			if(c == '\n'){
				dequmention_line = 0;
			}
			continue;
		}
		if(c == ','){
			comma = 1;
		}
		else{
			if(c != ' ' && c != '\t'){
				comma = 0;
			}
		}
		if(c == '\n'){
			start_line = 1;
			line_num++;
		}
		if(c == '\t' || c == ' '){
			if(comma == 1){
				continue;
			}
			num_space++;
		}
		else num_space = 0;
		if(num_space >= 2 || (num_space == 1 && start_line == 1)){
			continue;
		}
		fprintf(fd_two,"%c",c);
		if(start_line == 1){
			if(c != ' ' && c != '\t'){
				start_line = 0;
			}
		}
	}
	fclose(fd_one);
	fclose(fd_two);
}