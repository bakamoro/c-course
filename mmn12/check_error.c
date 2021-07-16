#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void read_word(FILE *fd,char *p){
	int i = 0;
	char c = fgetc(fd);
	while(c != ' ' && (!feof(fd))){
		*(p + i) = c;
		i++;
		c = fgetc(fd);
	}
}
void read_line(FILE *fd,char p[]){
	int i = 0;
	char c = fgetc(fd);
	while(c != '\n' && (!feof(fd))){
                p[i] = c;
                i++;
                c = fgetc(fd);
        }
}
void main_check(char s[]){
	FILE *fd = fopen(s,"r");
	char p[81];
	if(fd == NULL){
		printf("ERROR - can't open the file - ");
		printf("%s\n",s);
		exit(0);
	}
	
	fclose(fd);
}
int main(){
	main_check("hucvcm");
}
