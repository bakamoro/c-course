#include <stdio.h>

void buffer(char *p){
	char c;
	int i = 0;
	printf("please write your text"):
	while((scanf("%c",&c)) != EOF && p != NULL){
		p[i] = c;
		++i;
		if(i%60 == 0)
			realloc(p,60*sizeof(char));
	}
	return;
}
void linked_list(int *p){
	
}
void readText(int a , char *p){
	if(a == 1){
                *p = (char *)calloc(60,sizeof(char));
                if(!p){
                        printf("ERROR");
                        exit(0);
                }
                buffer(a,p);
                if(p == NULL){
                        printf("ERROR");
                        exit(0);
                }
        }
        else{ 
                if(a == 2){

                }
                else printf("ERROR you didn't entered 1 or 2");
        }
}
void printText(int a,*p){
	
}
void main (){
	printf ("Please select the desired database type:\nfor a buffer : enter 1\nfor a linked list : enter 2");
	int a;
	char *p;
	scanf("%d",&a);
	readText(a,*p);
	if(!p) 
		return;
	printText(a,*p);
}
