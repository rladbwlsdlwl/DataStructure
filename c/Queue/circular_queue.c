#include<stdio.h>
#include<stdlib.h>
#define MAX 5

typedef int element;
typedef struct {
	element data[MAX];
	int front,rear;
}Queue;

void error(char*message){
	fprintf(stderr,"%s\n",message);
	exit(1);
}

void init(Queue*q){
	q->rear=q->front=0;
}

int is_full(Queue*q){
	return (q->rear+1)%MAX==q->front;
}

int is_empty(Queue*q){
	return q->front==q->rear;
}

void enqueue(Queue*q,element item){
	if(is_full(q))
		error("큐 포화 에러\n");
	
	q->rear=(q->rear+1)%MAX;
	q->data[q->rear]=item;
}

element dequeue(Queue*q){
	if(is_empty(q))
		error("큐 공백 에러\n");
	
	q->front=(q->front+1)%MAX;
	return q->data[q->front];
}

int main (void){
	Queue*q=malloc(sizeof(Queue));
	init(q);
	for(int i=1;i<5;i++)
		enqueue(q,i*10);
	//enqueue(q,50); //큐 포화
	while(!is_empty(q))
		printf("dequeue %d\n",dequeue(q));
	
	for(int i=1;i<5;i++)
		enqueue(q,i*10);


	while(!is_empty(q))
		printf("dequeue %d\n",dequeue(q));
	
	free(q);
	return 0;
}

