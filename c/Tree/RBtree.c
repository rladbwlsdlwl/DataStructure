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
			printf("[NULL] ");
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
treenode* minValue(treenode*root);
bool removal(treenode*root, element val);
treenode* deleteNode(treenode*remove);
void balancify(treenode*root, treenode*child, treenode*parent, int color);
bool checkBlack(treenode*p);
void swapColor(treenode*p, treenode*q);


//pre is NULL, this node is root
treenode *root = NULL; 
int main() {
	int n; element data;

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
		case 2:
			printf("Enter integer value to delete :");
			scanf("%d", &data);
			if (removal(root, data))
				printf("DELETE SUCCESS!\n");
			else
				printf("DELETE FAILED!\N");

			break;
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

//---------------------insertion------------------------
treenode* insertion(treenode*root, element val, treenode *pre) {
	if (!root)
		return newNode(root, val, pre);
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


void fixup(treenode*root, treenode*temp) { //temp is newnode (red)
	treenode *parent = temp->pre;
	treenode *grand = NULL;
	treenode *brother = NULL;

	if (parent != NULL && parent->c == 'R') {
		grand = parent->pre; //also color of parent node is RED , Exist parent node of parent node
		if (grand->left == parent)
			brother = grand->right;
		else
			brother = grand->left;

		if (brother != NULL && brother->c == 'R') {
			brother->c = parent->c = 'B';
			grand->c = 'R';
			if (grand == root)
				grand->c = 'B'; //root color is always BLACK
			else
				fixup(root, grand);
		}
		else { // color of brother node is BLACK (include when brother node is NULL) 
			if (grand->left == parent) {
				if (parent->right == temp) { //rotate LR to LL
					leftRotate(parent);
					parent = grand->left; //change position parent newnode 
				}
				swapColor(grand, parent);
				rightRotate(grand);
			}
			else {
				if (parent->left == temp) {// RL to RR
					rightRotate(parent);
					parent = grand->right;
				}
				swapColor(grand, parent);
				leftRotate(grand);
			}
		}
	}

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
		temp->pre->left = p;
	else
		temp->pre->right = p;

	p->right = temp;
	temp->pre = p;

}

//----------------------------------------

void swapColor(treenode*p, treenode*q) {
	int temp = p->c;
	p->c = q->c;
	q->c = temp;
}

bool checkBlack(treenode*p) {
	if (!p || p->c == 'B')
		return true;
	else
		return false;
}

//-----------------Deletion--------------------
bool removal(treenode*root, element val) {
	treenode*curr = root;
	while (curr) {
		if (curr->val == val) {
			balancify(root, deleteNode(curr), curr->pre, curr->c);
			return true;
		}
		else if (curr->val < val)
			curr = curr->right;
		else
			curr = curr->left;
	}

	return false;
}


treenode* deleteNode(treenode*remove) {
	if (remove == root) {
		if (!remove->left) {
			root = remove->right;
			root->pre = NULL;
			free(remove);
			return root; //send remove node's child node
		}
		else if (!root->right) {
			root = remove->left;
			remove->pre = NULL;
			free(remove);
			return root; //send remove node's child node
		}
		else {
			root->val = minValue(remove->right)->val;
			if (removal(remove->right, remove->val)) // sucessful deletion , return true
				return; 
		}
	}

	else if (!remove->left) {
		treenode*temp = remove->right;
		if (remove->pre->left == remove)
			remove->pre->left = remove->right;
		else
			remove->pre->right = remove->right;

		if (temp)
			temp->pre = remove->pre;
		free(remove);
		return temp; //send remove node's child node
	}
	else if (!remove->right) {
		treenode*temp = remove->left;
		if (remove->pre->left == remove)
			remove->pre->left = remove->left;
		else
			remove->pre->right = remove->left;

		if (temp)
			temp->pre = remove->pre;
		free(remove);
		return temp;  //send remove node's child node
	}
	else { // child node is 2
		remove->val = minValue(remove->right)->val;
		if (removal(remove->right, remove->val)) // sucessful deletion , return true
			return; 
	}
}

void balancify(treenode*root, treenode*child, treenode*parent, int color) {
	if (root == NULL) return;
	if (root == child){
		root->c = 'B';
		return;
	}

	if (color == 'B') {
		if (checkBlack(child)==false) //child is Red
			child->c = 'B';
		else { // child is NULL  OR  child color Black
			treenode*sibling= (parent->left == child) ? parent->right : parent->left ;
			if (!sibling) return;

			//--------------case 1-1---------------
			if (parent->c == 'R' && checkBlack(sibling->left) && checkBlack(sibling->right)) //RBBB
				swapColor(parent, sibling); //swap (parent,sibling)
			
			//---------------case *-2------------------
			else if (parent->right == sibling && sibling->c=='B' && checkBlack(sibling->right)==false) { //_B_R
				swapColor(parent, sibling);
				sibling->right->c = 'B';
				leftRotate(parent);
			} //  After Rotate, swap(parent,sibling), Change sibling->right->c in B
			else if (parent->left == sibling && sibling->c=='B' && checkBlack(sibling->left) == false) { //_B_R_
				swapColor(parent, sibling);
				sibling->left->c = 'B';
				rightRotate(parent);
			} 
			
			//-----------------case *-3--------------
			else if (parent->right == sibling && checkBlack(sibling) && checkBlack(sibling->right) && checkBlack(sibling->left) == false) { //_BRB
				swapColor(sibling->left, sibling);
				rightRotate(sibling);
				balancify(root, child,parent, color);
			}
			else if (parent->left == sibling && checkBlack(sibling) && checkBlack(sibling->left) && checkBlack(sibling->right) == false) {//_BBR
				swapColor(sibling->right, sibling);
				leftRotate(sibling);
				balancify(root, child, parent, color);
			}

			//--------------case 2-1---------------
			else if (checkBlack(parent) && checkBlack(sibling) && checkBlack(sibling->left) && checkBlack(sibling->right)) {
				sibling->c = 'R';
				balancify(root, parent, parent->pre, color);
			}

			//-------------case 2-4 --------------
			else if (parent->right==sibling && checkBlack(parent) && checkBlack(sibling) == false && checkBlack(sibling->left) && checkBlack(sibling->right)) {
				swapColor(sibling, parent);
				leftRotate(parent);
				balancify(root, child, parent, color);
			}
			else if (parent->left == sibling && checkBlack(parent) && checkBlack(sibling) == false && checkBlack(sibling->left) && checkBlack(sibling->right)) {
				swapColor(sibling, parent);
				rightRotate(parent);
				balancify(root, child, parent, color);
			}
		}

	}

	if (root == child) 
		root->c = 'B';
}

//---------------------------------------

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

treenode* minValue(treenode*root) {
	if (root->left)
		return minValue(root->left);
	else
		return root;
}

