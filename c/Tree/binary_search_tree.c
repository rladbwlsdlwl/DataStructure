//이진탐색트리 
#include<stdio.h>
#include<stdlib.h>
#include<string.h> //문자열 비교시 사용

typedef int element;
typedef struct node{
	element data;
	struct node*left;
	struct node*right;
}Node;

Node* insert_node(Node*root,element item);
Node* newNode(element item);
void inorder(Node*root);

int main (void){
	Node*root=NULL;
	Node*result=NULL; //이진탐색트리 탐색 결과 저장

	root=insert_node(root,30);
	root=insert_node(root,20);
	root=insert_node(root,40);
	root=insert_node(root,10);
	root=insert_node(root,50);

	inorder(root);
	printf("\n이진탐색트리를 탐색합니다\n");

	result=search(root,10);
	if(result)
		printf("%d 를 찾았습니다!\n",result->data);
	else
		printf("NULL!\n");

	result=search(root,60);
	if(result)
		printf("%d 를 찾았습니다!\n",result->data);
	else
		printf("NULL!\n");


	return 0;
}

Node* insert_node(Node*root,element item){
	if(!root)
		return newNode(item);

	if(root->data>item)
		root->left=insert_node(root->left,item);
	else
 		root->right=insert_node(root->right,item);

	return root;
}

Node* newNode(element item){
	Node*temp=malloc(sizeof(Node));
	temp->data=item;
	temp->left=temp->right=NULL;

	return temp;
}

Node* search(Node*root,element item){

void inorder(Node*root){
	if(root){
		inorder(root->left);
		printf("%d -> ",root->data);
		inorder(root->right);
	}
}

