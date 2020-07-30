#include<stdio.h>
#include<stdlib.h>
#define MAX 20

typedef int element;
typedef struct queue{
	element data[MAX];
	int front;
	int rear;
}Queue;

void error(char*message){
	fprintf(stderr,"%s\n",message);
	exit(1);
}

void init(Queue*q){
	q->rear=q->front=0;
}

int is_full(Queue*q){
	return q->rear==MAX-1;
}

int is_empty(Queue*q){
	return q->rear==q->front;
}

void enqueue(Queue*q,element item){
	if(is_full(q))
		error("큐 포화에러");
	else
		q->data[++q->rear]=item;
}

element dequeue(Queue*q){
	if(is_empty(q))
		error("큐 공백에러");
	else
		return q->data[++q->front];
}

int main (void){
	Queue*q=malloc(sizeof(Queue));
	init(q);
	enqueue(q,10); enqueue(q,20); enqueue(q,30);
	
	while(!is_empty(q))
		printf("dequeue %d\n",dequeue(q));

	free(q);
	return 0;
}




