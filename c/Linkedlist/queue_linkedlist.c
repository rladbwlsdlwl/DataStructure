#include<stdio.h>
#include<malloc.h>

typedef int element;
typedef struct node{
	element data;
	struct node*link;
}Node;

typedef struct{
	Node*front;
	Node*rear;
}LinkedQueueType;

void init(LinkedQueueType*q){
	q->front=q->rear=NULL;
}

int is_full(LinkedQueueType*q){
	return 0;
}
int is_empty(LinkedQueueType*q){
	return q->front==NULL;
}

void enqueue(LinkedQueueType*q,element item){
	Node*newNode=malloc(sizeof(Node));
	newNode->data=item;
	
	if(is_empty(q)){
		newNode->link=NULL;
		q->rear=q->top=newNode;
	}
	else{



