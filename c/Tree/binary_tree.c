//차수가 최대 2인 이진트리
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100

typedef int element;
typedef struct node{
	element data;
	struct node*left;
	struct node*right;
}Node;

//각 트리의 노드를 스택방식으로 추가
typedef struct stacknode{
	Node*stack[MAX];
	int top;
}StackNode;

void init(StackNode*s){
	s->top=-1;
}
void push(StackNode*s,Node*t){
	if(s->top<MAX-1)
		s->stack[++s->top]=t;
}
Node* pop(StackNode*s){
	if(s->top>=0)
		return s->stack[s->top--];
	else
		return NULL;
}

/*완전 이진트리 생성
 		1
           2	     3
        4    5	   6

*/
Node n6={6,NULL,NULL};
Node n5={5,NULL,NULL};
Node n4={4,NULL,NULL};
Node n3={3,&n6,NULL};
Node n2={2,&n4,&n5};
Node n1={1,&n2,&n3};
Node*root=&n1;

bool menu(StackNode*s);
void preorder(Node*root);
void inorder(Node*root);
void postorder(Node*root);
void preorder_iter(StackNode*s);//전위순회 출력 스택이용 
void inorder_iter(StackNode*s); //중위순회출력 스택이용 

int main (void){
	StackNode *s=malloc(sizeof(StackNode)); init(s);

	bool stopped=false;
	while(!stopped)
		stopped=menu(s);
	free(s);
	return 0;
}

bool menu(StackNode*s){
	int ans;
	while(1){
		printf("0.end 1.preorder 2.inorder 3.postorder\n>>> ");
		scanf("%d",&ans);
		switch(ans){
			case 1:
				preorder(root);
				preorder_iter(s);
				break;
			case 2:
				inorder(root);
				inorder_iter(s);
				break;
			case 3:
				postorder(root);
				//postorder_iter(s);
				break;
			case 0:
				return true;
			default:
				break;
		}
	}
}

void preorder(Node*root){
	if(root!=NULL){
		printf("preorder: %d\n",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(Node*root){
	if(root!=NULL){
		inorder(root->left);
		printf("inorder: %d\n",root->data);
		inorder(root->right);
	}
}

void postorder(Node*root){
	if(root!=NULL){
		postorder(root->left);
		postorder(root->right);
		printf("postorder: %d\n",root->data);
	}
}

void preorder_iter(StackNode*s){
	Node*curr=root;
	while(1){
		for(; curr; curr=curr->left){
			push(s,curr);
			printf("preorder_stack: %d\n",curr->data);
		}
		curr=pop(s);
		if(!curr) break;

		curr=curr->right;
	}
}

void inorder_iter(StackNode*s){
	Node*curr=root;
	while(1){
		for(; curr; curr=curr->left)
			push(s,curr);
		
		curr=pop(s);
		if(!curr) break;

		printf("inorder_stack: %d\n",curr->data);
		curr=curr->right;
	}
}

