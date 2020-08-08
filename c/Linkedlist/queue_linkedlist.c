#include<stdio.h>
#include<stdlib.h>

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
	newNode->link=NULL;

	if(is_empty(q))
		q->rear=q->front=newNode;
	else{
		q->rear->link=newNode;
		q->rear=newNode;
	}
}
element dequeue(LinkedQueueType*q){
	if(is_empty(q)){
		fprintf(stderr,"큐공백에러\n");
		exit(1);
	}
	Node*remove=q->front;
	q->front=q->front->link;
	element temp=remove->data;
	free(remove);

	return temp;
}
void print_queue(LinkedQueueType*q);

int main(void){
	LinkedQueueType*q=malloc(sizeof(LinkedQueueType)); init(q);
	for(int i=0;i<5;i++)
		enqueue(q,i+1);
	print_queue(q);
	while(!is_empty(q))
		printf("dequeue %d\n",dequeue(q));

	return 0;
}
void print_queue(LinkedQueueType*q){
	Node*curr=q->front;
	while(curr){
		printf("[%d]->",curr->data);
		curr=curr->link;
	}

	printf("\n");
}


		
