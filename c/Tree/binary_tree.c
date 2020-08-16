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

//각 트리의 노드를 스택방식으로 추가 => 반복문 노드순회 
typedef struct stacknode{
	Node*stack[MAX];
	int top;
}StackNode;

void init_stack(StackNode*s){
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
//트리노드를 넣을 원형큐 => 레벨순회 
typedef struct Queuenode{
	Node*queue[MAX];
	int front,rear;
}QueueNode;

void init_queue(QueueNode*q){
	q->front=q->rear=0;
}
void error(char*message){
	fprintf(stderr,"%s\n",message);
	exit(1);
}
int is_full(QueueNode*q){
	return (q->rear+1)%MAX==q->front;
}
int is_empty(QueueNode*q){
	return q->rear==q->front;
}

void enqueue(QueueNode*q,Node*item){
	if(is_full(q))
		error("큐 포화상태");

	q->rear=(q->rear+1)%MAX;
	q->queue[q->rear]=item;
}

Node* dequeue(QueueNode*q){
	if(is_empty(q))
		error("큐 공백에러");
	
	q->front=(q->front+1)%MAX;
	return q->queue[q->front];
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

void preorder_iter(StackNode*s); //전위순회 반복문으로 스택이용 출력 
void inorder_iter(StackNode*s); //중위순회 반복문으로 스택이용 출력

int get_node_count(Node*root); //노드의 개수 
int get_height(Node*root); //트리의 높이 
int get_leaf_count(Node*root); //트리의 단말노드 개수 
void level_order(Node*root); //큐를 이용한 레벨순회 
int get_node_sum(Node*root); //후위순회로 노드의 총 합
int get_node_max(Node*root); //후위순회로 가장 큰 노드 찾기 


int main (void){
	StackNode *s=malloc(sizeof(StackNode)); init_stack(s);

	bool stopped=false;
	while(!stopped)
		stopped=menu(s);
	free(s);

	printf("노드의 개수: %d\n",get_node_count(root));
	printf("트리의 높이: %d\n",get_height(root));
	printf("단말노드의 개수: %d\n",get_leaf_count(root));
	
	printf("트리의 레벨순회: "); level_order(root);

	printf("노드의 총 합: %d\n",get_node_sum(root));
	printf("노드의 최댓값: %d\n",get_node_max(root));
	/*
	if(balanced_tree(root))
		printf("균형트리입니다!\n");
	else
		printf("균형트리가 아닙니다!\n");
	*/
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

void level_order(Node*root){
	QueueNode *q=malloc(sizeof(QueueNode)); init_queue(q);
	if(!root) return;

	enqueue(q,root);
	while(!is_empty(q)){
		root=dequeue(q);
		printf("%d -> ",root->data);

		if(root->left)
			enqueue(q,root->left);
		if(root->right)
			enqueue(q,root->right);
	}

	free(q);
	printf("\n");
}

int get_node_count(Node*root){
	if(!root)
		return 0;
	else
		return 1+get_node_count(root->left)+get_node_count(root->right);
}

int get_height(Node*root){
	if(!root)
		return 0;
	else{
		int left=get_height(root->left);
		int right=get_height(root->right);

		if(left>right)
			return left+1;
		else
			return right+1;
	}
}

int get_leaf_count(Node*root){
	if(!root)
		return 0;
	if(!root->left && !root->right)
		return 1;
	else
		return 0+get_leaf_count(root->left)+get_leaf_count(root->right);
}

int get_node_sum(Node*root){
	if(!root)
		return 0;
	else{
		int left=get_node_sum(root->left);
		int right=get_node_sum(root->right);
		return left+right+root->data;
	}
}

int get_node_max(Node*root){
	if(!root)
		return 0;
	else{
		int left=get_node_max(root->left);
		int right=get_node_max(root->right);
		int node=root->data;

		if(left>right){
			if(left>node)
				return left;
			else
				return node;
		}
		else{
			if(right>node)
				return right;
			else
				return node;
		}
	}
}
