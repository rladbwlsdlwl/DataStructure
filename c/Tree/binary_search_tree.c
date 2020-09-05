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

Node* insert_node(Node*root,element item); //노드 삽입
Node* newNode(element item); // 새로운 노드 생성
void inorder(Node*root); // 중위순회 
Node* search_node(Node*node,element item); //재귀로 탐색
Node* search(Node*node,element item); // 반복문 탐색
Node* delete_node(Node*root,element item); //노드삭제
Node* min_value_node(Node*node); //노드의 작은 값

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

	result=search(root,20);
	if(result)
		printf("%d 를 찾았습니다!\n",result->data);
	else
		printf("NULL!\n");

	result=search(root,40);
	if(result)
		printf("%d 를 찾았습니다!\n",result->data);
	else
		printf("NULL!\n");
	
	root=insert_node(root,5); root=insert_node(root,15); root=insert_node(root,13); root=insert_node(root,14);

	root=delete_node(root,10);
	printf("10 노드 삭제 후 중위순회\n");
	inorder(root);

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

Node* search_node(Node*node,element item){
	if(!node)
		return NULL;
	else if(node->data>item)
		return search_node(node->left,item);
	else if(node->data<item)
		return search_node(node->right,item);
	else
		return node;

}

Node* search(Node*node,element item){
	while(node){
		if(node->data>item)
			node=node->left;
		else if(node->data<item)
			node=node->right;
		else 
			return node;
	}
	
	/*
	for(;node;(node->data>item)? node->left : node->right){
		if(node->data==item)
			return node;
	}
	*/

	return NULL;
}

Node* delete_node(Node*root,element item){
	if(!root)
		return root;
	
	if(root->data<item)
		root->right=delete_node(root->right,item);
	else if(root->data>item)
		root->left=delete_node(root->left,item);
	else{
		if(!root->left){
			Node*temp=root->right;
			free(root);

			return temp;
		}
		else if(!root->right){
			Node*temp=root->left;
			free(root);

			return temp;
		}
		else{
			Node*temp=min_value_node(root->right);
			root->data=temp->data;

			root->right=delete_node(root->right,temp->data);
		}

	}

	return root;
}

Node* min_value_node(Node*node){
	while(node->left)
		node=node->left;
	return node;
}

void inorder(Node*root){
	if(root){
		inorder(root->left);
		printf("%d -> ",root->data);
		inorder(root->right);
	}
}

