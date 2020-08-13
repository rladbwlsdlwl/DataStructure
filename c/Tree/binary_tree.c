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
void preorder(StackNode*s,Node*root);
void inorder(StackNode*s,Node*root);
void postorder(StackNode*s,Node*root);
void show_stack(StackNode*s);
void inorder_iter(StackNode*s,Node*root); //중위순회출력 스택이용 

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
				preorder(s,root);
				show_stack(s);
				break;
			case 2:
				inorder(s,root);
				show_stack(s);
				break;
			case 3:
				postorder(s,root);
				show_stack(s);
				break;
			case 0:
				return true;
			default:
				break;
		}
	}
}

void preorder(StackNode*s,Node*root){
	if(root!=NULL){
		push(s,root);
		printf("preorder: %d\n",root->data);
		preorder(s,root->left);
		preorder(s,root->right);
	}
}

void inorder(StackNode*s,Node*root){
	if(root!=NULL){
		inorder(s,root->left);
		push(s,root);
		printf("inorder: %d\n",root->data);
		inorder(s,root->right);
	}
}

void postorder(StackNode*s,Node*root){
	if(root!=NULL){
		postorder(s,root->left);
		postorder(s,root->right);
		push(s,root);
		printf("postorder: %d\n",root->data);
	}
}
void show_stack(StackNode*s){
	printf("스택에 넣은 노드를 pop!\n");
	while(s->top>=0)
		printf("pop %d\n",pop(s)->data);
	printf("스택이 비었습니다 !\n\n");
}

void inorder_iter(StackNode*s,Node*root){
	while(1){
		for(; root; root=root->left)
			push(s,root);
		
		root=pop(s);
		if(!root) break;

		printf("inorder_stack: %d\n",root->data);
		root=root->right;
	}
}
