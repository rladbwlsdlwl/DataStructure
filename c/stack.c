#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef int element;
typedef struct stack{
	element data[MAX];
	int top;
}Stack;

void init(Stack*s){
	s->top=-1;
}

int is_full(Stack*s){
	return s->top==MAX-1;
}

int is_empty(Stack*s){
	return s->top==-1;
}

void push(Stack*s,element data){
	if(is_full(s)){
		fprintf(stderr,"스택포화에러\n");
		return;
	}
	else
		s->data[++s->top]=data;
}

element pop(Stack*s){
	if(is_empty(s)){
		fprintf(stderr,"스택공백에러\n");
		exit(1);
	}
	else
		return s->data[s->top--];
}

element peek(Stack*s){
	if(is_empty(s)){
		fprintf(stderr,"스택공백에러\n");
		exit(1);
	}
	return s->data[s->top];
}

int main (void){
	Stack*p=malloc(sizeof(Stack));
	init(p);
	push(p,10); push(p,20); push(p,30);

	while(!is_empty(p))
		printf("pop %d\n",pop(p));

	free(p);	
	return 0;
}

