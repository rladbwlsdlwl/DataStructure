#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100


typedef int element;
typedef int color;
typedef struct Treenode {
	element val;
	color c; // node color <black red>
	struct Treenode*left;
	struct Treenode*right;
	struct Treenode*pre; // before node
}treenode;

//--------------level order queue-------------------
treenode* Queue[MAX]; //linear queue
int front = -1, rear = -1;

void enqueue(treenode*temp) {
	if (rear + 1 == MAX) {
		fprintf(stderr, "큐포화\n");
		exit(1);
	}
	Queue[++rear] = temp;
}

treenode* dequeue() {
	if (front == rear) {
		fprintf(stderr, "큐공백\n");
		return;
	}
	return Queue[++front];
}

void printTree(treenode*root) {

	front = -1, rear = -1;
	enqueue(root);
	while (1) {
		if (front == rear) break;
		treenode*temp = dequeue();

		if (temp) {
			enqueue(temp->left);
			enqueue(temp->right);
			printf("[%d %c] ", temp->val, temp->c);
		}
		else
