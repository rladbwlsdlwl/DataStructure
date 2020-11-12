#include<stdio.h>
#include<stdlib.h>

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
		if (temp->left) enqueue(temp->left);
		if (temp->right) enqueue(temp->right);

		printf("%d %c  ", temp->val,temp->c);
	}

	printf("\n\n");
}

//-------------------------------------------------

treenode* insertion(treenode*root, element val, treenode *pre);
treenode* newNode(treenode*root, element val, treenode*parent);
treenode* searchNode(treenode*root, element val);
void fixup(treenode*root, treenode*temp);
void rightRotate(treenode*temp);
void leftRotate(treenode*temp);

//pre is NULL, this node is root
treenode *root = NULL;
int main() {
	int n; int data;
	while (1) {
		printf("------------------------------------\n");
		printf("1. insertion node  2. removal node  0. end program\n>>>");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("Enter integer value to insert :");
			scanf("%d", &data);
			root=insertion(root, data, root);
			fixup(root, searchNode(root,data));
			break;
		/*case 2:
			printf("Enter integer value to delete :");
			scanf("%d", &data);
			root=removal(root, data);
			break;*/
		case 0:
			printf("EXIT PROGRAM\n");
			return 0;
		default:
			printf("Enter 0~2 integer number\n");
			break;
		}

		printTree(root);
	}
}

treenode* searchNode(treenode*root, element val) {
	if (!root)
		return NULL;
	else if (root->val > val)
		return searchNode(root->left, val);
	else if (root->val < val)
		return searchNode(root->right, val);
	else
		return root;
}
treenode* insertion(treenode*root, element val,treenode *pre) {
	if (!root)
		return newNode(root, val,pre);
	else if (root->val > val) 
		root->left = insertion(root->left, val, root);
	else 
		root->right = insertion(root->right, val, root);

	return root;
}

treenode* newNode(treenode*root, element val, treenode*parent) {
	treenode*temp = malloc(sizeof(treenode));
	temp->val = val;
	temp->left = temp->right = NULL;
	temp->pre = parent;

	if (root == parent)  // if empty node, root node is black
		temp->c = 'B';
	else
		temp->c = 'R'; // else, new node is red node

	return temp;
}

void leftRotate(treenode*temp) {
	treenode*p = temp->right;
	temp->right = p->left; 
	if (temp->right)
		temp->right->pre = temp;
	p->pre = temp->pre;
	if (!temp->pre)
		root = p;
	else if (temp->pre->left == temp)
		temp->pre->left = p;
	else
		temp->pre->right = p;

	p->left = temp;
	temp->pre = p;

}

void rightRotate(treenode*temp) {
	treenode*p = temp->left;
	temp->left = p->right;
	if (temp->left) 
		temp->left->pre = temp;
	p->pre = temp->pre;
	if (!temp->pre)
		root = p;
	else if (temp->pre->left == temp)
		temp->pre->left =p;
	else
		temp->pre->right = p;

	p->right = temp;
	temp->pre = p;

}

void fixup(treenode*root, treenode*temp) {
	treenode *parent = temp->pre;
	treenode *grand = NULL;
	treenode *brother = NULL;
	if (parent != NULL && parent->c == 'R') {  // Exist temp of parent node , this parent node color is RED
		grand = parent->pre; //also color of parent node is RED , Exist parent node of parent node
		if (grand->left == parent)
			brother = grand->right;
		else
			brother = grand->left;

		if (brother!=NULL && brother->c == 'R') {
			brother->c = parent->c = 'B';
			grand->c = 'R';
			if (grand == root)
				grand->c = 'B'; //root color is always BLACK
			else
				fixup(root, grand);
		}
		else { // color of brother node is BLACK 
			if (grand->left == parent) { 
				if (parent->right == temp) //rotate LR to LL
					leftRotate(parent);
				rightRotate(grand);
				int color=grand->c;
				grand->c = parent->c;
				parent->c = color;
			}
			else {
				if (parent->left == temp) // RL to RR
					rightRotate(parent);
				leftRotate(grand);
				int color = grand->c;
				grand->c = parent->c;
				parent->c = color;
			}
		}
	}

}
