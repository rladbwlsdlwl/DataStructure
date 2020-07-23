#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX 50

typedef struct{
	char string[MAX];
}element;

typedef struct Node{
	element data;
	struct Node*link;
}Node;

Node* insert_last(Node*head,char item[MAX]); //맨 뒤에 연결
Node* insert_first(Node*head,char item[MAX]);//맨 앞에 연결
Node* insert(Node*head,Node*pre,char item[MAX]);//pre노드 뒤에 연결

int main (void){
	int n; bool answer=true;
	Node*head=NULL;

	while(answer){
		printf("1.끝에 연결  2.첨에 연결  0.종료\n==>");
		scanf("%d",&n);

		switch(n){
			case 1:
				head=NULL;
				head=insert_last(head,"hello");
				head=insert_last(head,"my");
				head=insert_last(head,"name");
				head=insert_last(head,"is");
				head=insert_last(head,"yujin");
				break;

			case 2:	
				head=NULL;	
				head=insert_first(head,"hello"); 
				head=insert_first(head,"my");
				head=insert_first(head,"name");
				head=insert_first(head,"is");
				head=insert_first(head,"yujin");
				break;
			
			case 0:
				answer=false;
				break;	
		}

		for(Node*curr=head; curr; curr=curr->link)
			printf("%s ",curr->data.string);
		printf("\n");
	}

	answer=true;
	delete_first(

	return 0;
}

Node* insert_last(Node*head,char item[MAX]){
	Node*newNode=malloc(sizeof(Node)); 
	newNode->link=NULL;
	strcpy(newNode->data.string,item);

	if(!head)
		head=newNode;
	else{	
		Node*curr=head;
		while(curr->link)
			curr=curr->link;
		
		curr->link=newNode;
	}

	return head;
}

Node* insert_first(Node*head,char item[MAX]){
	Node*newNode=malloc(sizeof(Node)); 
	strcpy(newNode->data.string,item);
	newNode->link=head;

	return newNode;
}

Node* insert(Node*head,Node*pre,char item[MAX]){
	Node*newNode=malloc(sizeof(Node));
	strcpy(newNode->data.string,item);
	newNode->link=pre->link;
	pre->link=newNode;

	return head;
}






