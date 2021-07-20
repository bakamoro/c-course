#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
void re_array(char p[],char **p2){
	char p1[81];
	char **p3;
	p2 = p3;
	p = p1;
}
char *  bilt_array(char *p,int i){
	char *p2;
	while(i<strlen(p) && p[i] != ' ','\n'){
		p2[i] = p[i];
		i++;
	}
	if(p[i] != '\n')
		i++;
	return p2;
}
void read_word(FILE *fd,char *p){
	int i = 0;
	char c = fgetc(fd);
	while(c != ' ' && (!feof(fd) && c != '\n')){
		*(p + i) = c;
		i++;
		c = fgetc(fd);
	}
}
void read_line(FILE *fd,char p[81]){
	int i = 0;
	char c = fgetc(fd);
	while(c != '\n' && (!feof(fd))){
                p[i] = c;
                i++;

                c = fgetc(fd);
        }
}
void number_check(char s[]){
	int i = 0;
	while(i < strlen(s)){
		if(s[i] == '.')
			
		i++;
	}
}

void main_check(char s[]){
	FILE *fd = fopen(s,"r");
	fpos_t pos;
	char p[81];
	char **p2;
	char *p3;
	int line_num = 1;
	int i = 0,j = 0;
	if(fd == NULL){
		printf("ERROR - can't open the file - ");
		printf("%s\n",s);
		exit(0);
	}
	while(!feof(fd)){
		while(!feof(fd)){
			re_array(p,p2);
			fgetpos(fd,&pos);
			if(fgetc(fd) == ';'){
				read_line(fd,p);
				line_num++;
				break;
			}
			fsetpos(fd,&pos);
			read_line(fd,p);
			line_num++;
			while(p[i] != '\n'){
				while(p[i] != '\n',' '){
					p3 = bilt_array(p,i);
					p2[j] = p3;
					j++;
				}
			}
			
		}	
	}	
	fclose(fd);
}
int main(){
	main_check("ps.as");
}
