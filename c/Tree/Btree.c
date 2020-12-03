#include<stdio.h>
#include<stdlib.h> // Use malloc
#include<string.h> // Use memset
#include<stdbool.h> 
#define FULL 100

typedef int element;
typedef struct Treenode {
	element *keys; // values into Array <int>
	struct Treenode **childs; // child nodes into Array <treenode>
	struct Treenode *pre; // parent node 
	
	bool leaf; //check leaf node
	int n; // count key
}treenode;


//---------------level order----------------
int front = -1, rear = -1;
treenode* Queue[FULL];
treenode*root = NULL;

void enqueue(treenode*temp) {
	if (rear + 1 == FULL) {
		fprintf(stderr, "큐포화\n");
		return;
	}
	Queue[++rear] = temp;
}

treenode* dequeue() {
	if (front == rear) {
		fprintf(stderr, "큐공백\n");
		exit(1);
	}

	return Queue[++front];
}

void printTree() {
	front = -1, rear = -1;
	enqueue(root);
	int h = -1;

	while (1) {
		if (front == rear) break;
		treenode*temp = dequeue();

		if (h != getHeight(temp))
			printf("\n");
		
		printf("[");
		for (int i = 0; i < temp->n; i++) 
			printf("%d ", temp->keys[i]);
		
		printf("]");

		printf("	");
		h = getHeight(temp);

		for (int i = 0; i < temp->n+1; i++) {
			if(temp->childs[i])
				enqueue(temp->childs[i]);
		}
			
	}
	printf("\n");
}

int getHeight(treenode*p) {
	if (p == NULL)
		return 0;
	return 1 + getHeight(p->childs[0]);
}

treenode* insertion(element data);
treenode* newNode();
treenode* getLeafNode(treenode*node, element key);
void clearOverflow(treenode*p);
int searchKeyIndex(treenode*p, treenode*parent);
int searchPosition(treenode*p, int key);
void sort(int *arr, int size);
bool rightSibling_Remain(treenode*p, int idx);
bool leftSibling_Remain(treenode*p, int idx);
bool checkOverflow(int n);
void splitChild(treenode*p);
treenode* search(treenode*node, element data);

bool checkUnderflow(int size);
void removal(treenode*node,element data);
treenode* swapLeafnode(treenode*node, element data);
bool leftSibling_Rob(treenode*p, int index);
bool rightSibling_Rob(treenode*p, int index);
void clearUnderflow(treenode*p);

const int MAX;
int main() {
	
	int no; element data;
	printf("Enter Number of Max key >>");
	scanf("%d", &MAX);

	while (1) {
		printf("1. Insertion key 2. Removal key  0.End program\n>>>");
		scanf("%d", &no);
		switch (no) {
		case 1:
			printf("Enter integer key to insert :");
			scanf("%d", &data);
			root = insertion(data);
			break;
		case 2:
			printf("Enter integer key to Delete :");
			scanf("%d", &data);
			removal(root,data);
			break;
		default:
			printf("Enter 0~2 integer number\n");
			break;
		case 0:
			return 0;
		}
		printTree(root);
	}
}

bool checkOverflow(int n) {
	return (n == MAX+1 ? true : false); 
}

treenode* insertion(element data) {
	if (root == NULL)
		root = newNode();

	treenode*curr = getLeafNode(root,data); //curr is leafnode (can't have child)
	
	curr->keys[curr->n] = data; //insert to End
	curr->n++;
	sort(curr->keys,curr->n);

	if (checkOverflow(curr->n)) 
		clearOverflow(curr);
	
	return root;
}

treenode* getLeafNode(treenode*node, element key) {
	if (!node->leaf) {
		int i;
		for (i = 0; i < node->n; i++) {
			if (key < node->keys[i])
				break;
		}
		return getLeafNode(node->childs[i], key);
	}
	return node;
}

treenode* newNode() {
	treenode* temp = malloc(sizeof(treenode));
	temp->keys = malloc(sizeof(int)*(MAX + 1)); //After insertion , check Fulled array
	temp->childs = malloc(sizeof(treenode)*(MAX + 1)); //because of included edge
	temp->pre = NULL;
	temp->leaf = true;

	memset(temp->childs, NULL, sizeof(treenode)*(MAX + 1)); // initialize child's node
	temp->n = 0;

	return temp;
}


bool leftSibling_Remain(treenode*p,int idx) {
	if (p->pre && idx>0 && p->pre->childs[idx-1]->n<MAX)
		return true;
	else
		return false;
}

bool rightSibling_Remain(treenode*p, int idx) {
	if (p->pre && idx<p->pre->n && p->pre->childs[idx + 1]->n <MAX)
		return true;
	else
		return false;
}

void clearOverflow(treenode*p) {
	if (p->pre == NULL) { // number of node is 1,root 
		splitChild(p);
		return;
	}
	
	int index = searchKeyIndex(p, p->pre);
	//printf("%d\n", index);
	if (index == -1) {
		printf("Insertion Error!\n");
		return;
	}

	if (leftSibling_Remain(p,index)) {
		int temp1 = p->keys[0];
		for (int i = 1; i < p->n; i++)
			p->keys[i - 1] = p->keys[i];
		p->n--;

		int temp2 = p->pre->keys[index - 1];
		p->pre->keys[index - 1] = temp1;
		insertion(temp2);
	}
	else if (rightSibling_Remain(p,index)) {
		int temp1 = p->keys[MAX];
		p->n--;
		
		int temp2 = p->pre->keys[index];
		p->pre->keys[index] = temp1;
		insertion(temp2,root);
	}
	else { // split 2 node
		printf("HERE!!\n");
		splitChild(p);
		if (checkOverflow(p->pre->n)) {//check parent node because parent node +1  
			printf("come in!\n");
			clearOverflow(p->pre);
		}
	}

}

void splitChild(treenode*p) {
	int mid=p->keys[MAX/2];
	treenode*sibling = newNode();
	
	int j = 0;
	for (int i = MAX/2+1; i <= MAX; i++) {
		sibling->keys[j++] = p->keys[i];
	}
	
	sibling->n = j;
	p->n = MAX/2;
	if (p->pre == NULL) {
		treenode*parent = newNode();
		parent->keys[0] = mid;
		parent->n = 1;
		parent->leaf = false;

		parent->childs[0] = p;
		parent->childs[1] = sibling;
		root = parent;
		sibling->pre = root;
		
		p->pre = root;
	}
	else {
		int i = searchPosition(p->pre, mid);
		//printf("%d\n", i);

		if (i == p->pre->n) {
			p->pre->childs[i+1] = sibling;
			p->pre->keys[i] = mid;
		}
		else {
			treenode*temp1 = p->pre->childs[i+1];
			int temp2=p->pre->keys[i];
			p->pre->keys[i] = mid;
			p->pre->childs[i + 1] = sibling;

			for (int j = i + 1; j < p->pre->n+1; j++) {
				p->pre->keys[j] = temp2;
				p->pre->childs[j + 1] = temp1;
				
				if (j + 1 == p->pre->n + 1) break;
				temp2 = p->pre->keys[j + 1];
				temp1 = p->pre->childs[j + 2];
			}
		}

		sibling->pre = p->pre;
		p->pre->n++;
		
	}
	

}

int searchPosition(treenode*p, int key) {
	int i;
	for (i = 0; i < p->n; i++) {
		if (p->keys[i] >= key)
			return i;
	}
	return i;
}

int searchKeyIndex(treenode*p, treenode*parent) {
	for (int i = 0; i <= MAX+1; i++) {
		if (parent->childs[i] == p)
			return i;
	}

	return -1;
}


void sort(int*arr ,int size) {
	for (int i = 1; i < size; i++) {
		int j,key = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (key < arr[j])
				arr[j + 1] = arr[j];
			else
				break;
		}
		arr[j+1] = key;
	}
}

treenode* search(treenode*node,element data) {
	if (node == NULL)
		return NULL;
	int i;
	for (i = 0; i < node->n; i++) {
		if (node->keys[i] == data)
			return node;
		else if (node->keys[i] > data)
			break;
	}

	return search(node->childs[i],data);
}

bool checkUnderflow(int size) {
	return size <= MAX / 2 - 1 ? true : false;
}

void removal(treenode*node,element data) {
	treenode*leafnode = swapLeafnode(search(root, data),data);
	
	for (int i = searchPosition(leafnode,data)+1; i < leafnode->n; i++)
		leafnode->keys[i - 1] = leafnode->keys[i];
	leafnode->n--;

	if (root->n == 0)
		return;
	if (checkUnderflow(leafnode->n))
		clearUnderflow(leafnode);

}

treenode* swapLeafnode(treenode*node, element data) {
	if (!node->leaf) {
		for (int i = 0; i < node->n; i++) {
			if (node->keys[i] == data) {
				node->keys[i] = node->childs[i + 1]->keys[0];
				node->childs[i + 1]->keys[0] = data;
				return swapLeafnode(node->childs[i + 1], data);
			}
		}
	}

	return node;
}
bool leftSibling_Rob(treenode*p, int index) {
	if (p->pre && index > 0 && p->pre->childs[index - 1]->n - 1 >= MAX / 2)
		return true;
	else
		return false;
}

bool rightSibling_Rob(treenode*p, int index) {
	if (p->pre && index < p->pre->n && p->pre->childs[index + 1]->n - 1 >= MAX / 2)
		return true;
	else
		return false;
}

void clearUnderflow(treenode*p) {
	if (p->n == 0) {
		treenode*temp = root;
		root = p->childs[0];
		root->pre = NULL;
		free(temp);
		return;
	}
	if (p->pre == NULL)
		return;
	
	int index = searchKeyIndex(p, p->pre);
	if (index == -1) {
		printf("Delete Error!\n");
		return;
	}
	
	if (leftSibling_Rob(p, index)) {
		int temp = p->pre->keys[index - 1]; //left
		p->pre->keys[index - 1] = p->pre->childs[index - 1]->keys[p->pre->childs[index-1]->n-1];
		p->pre->childs[index - 1]->n--;
		insertion(temp);
	}
	else if (rightSibling_Rob(p, index)) {
		int temp = p->pre->keys[index]; //right
		p->pre->keys[index] = p->pre->childs[index + 1]->keys[0];
		insertion(temp);
		removal(p, p->pre->keys[index]);
	}
	else { //merge with sibling node and key 
		if (index > 0) { //merge left sibling
			treenode*sibling = p->pre->childs[index - 1];
			sibling->keys[sibling->n++] = p->pre->keys[index - 1];
			for (int i = 0; i < p->n; i++)
				sibling->keys[sibling->n++] = p->keys[i];

			for (int i = index - 1; i < p->pre->n-1; i++) {
				p->pre->keys[i] = p->pre->keys[i+1];
				p->pre->childs[i + 1] = p->pre->childs[i + 2];
			}

			p->pre->childs[p->pre->n] = NULL;
			p->pre->n--;

			free(p);
			clearUnderflow(sibling->pre);
		}
		else { //merge right sibling (index==0)
			treenode*remove = p->pre->childs[index + 1];
			treenode*sibling = p->pre->childs[index];
			sibling->keys[sibling->n++] = sibling->pre->keys[index];
			for (int i = 0; i < remove->n; i++)
				sibling->keys[sibling->n++] = remove->keys[i];

			for (int i = 0; i < p->pre->n-1; i++) {
				p->pre->keys[i] = p->pre->keys[i + 1];
				p->pre->childs[i + 1] = p->pre->childs[i + 2];
			}

			p->pre->childs[p->pre->n] = NULL;
			p->pre->n--;

			free(remove);
			clearUnderflow(sibling->pre);
		}
		
	}
}
