#include <stdio.h>

void buffer(int a,char *p){
	char c;
	int i = 0;
	while((scanf("%c",&c) != EOF && p != NULL){
		p[i] = c;
		++i;
		if(i%60 == 0)
			realloc(p,60*sizeof(char));
	}
	return;
}

void main (){
	printf ("Please select the desired database type:\nfor a buffer : enter 1\nfor a linked list : enter 2");
	int a;
	scanf("%d",&a);
	char *p = (char *)calloc(60,sizeof(char));
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
