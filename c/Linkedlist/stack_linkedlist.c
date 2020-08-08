#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct node{
	element data;
	struct node*link;
}Node;

typedef struct{
	Node*top;
}LinkedStackType;

void init(LinkedStackType*s){
	s->top=NULL;
}
int is_full(LinkedStackType*s){
	return 0;
}
int is_empty(LinkedStackType*s){
	return s->top==NULL;
}
void push(LinkedStackType*s,element item){
	Node*newNode=malloc(sizeof(Node));
	newNode->data=item;

	newNode->link=s->top;
	s->top=newNode;
	
}
element pop(LinkedStackType*s){
	if(is_empty(s)){
		fprintf(stderr,"스택공백에러\n");
		exit(1);
	}

	Node*remove=s->top;
	element data=remove->data;
	s->top=s->top->link;
	free(remove);

	return data;
}
element peek(LinkedStackType*s){
	return s->top->data;
}

void print_stack(LinkedStackType *p);

int main(void){
	LinkedStackType s; init(&s);

	for(int i=0;i<10;i++)
		push(&s,i+1);
	print_stack(&s);
	
	while(!is_empty(&s))
		printf("pop %d\n",pop(&s));

	return 0;
}

void print_stack(LinkedStackType* p){
	Node*curr=p->top;
	while(curr){
		printf("[%d]->",curr->data);
		curr=curr->link;
	}
	printf("\n");
}

