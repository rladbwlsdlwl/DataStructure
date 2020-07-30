#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
typedef char String[MAX];

typedef struct node{
	String data;
	struct node*llink;
	struct node*rlink;
}Node;

void init(Node*head){
	head->llink=head->rlink=head;
}

void dinsert(Node*pre,String s);
void print_list(Node*head);
void ddelete(Node*head,Node*pre);
Node* search(Node*head,String s);

int main (void){
	Node*head=malloc(sizeof(Node)); //이중연결리스트의 head는 data값이 빈노드
	init(head);
	
	dinsert(head->llink,"hello");//리스트 뒷노드에 삽입
	dinsert(head->llink,"my");
	dinsert(head->llink,"dog");
	dinsert(head->llink,"is");
	dinsert(head->llink,"cute");

	print_list(head);

	ddelete(head,search(head,"cute")); //cute문자열 탐색후 아규먼트 노드 전달 
	
	print_list(head);

	return 0;
}

void dinsert(Node*pre,String s){ //pre 노드 뒤에 삽입 
	Node*newNode=malloc(sizeof(Node));
	strcpy(newNode->data,s);

	newNode->llink=pre;
	newNode->rlink=pre->rlink;
	pre->rlink->llink=newNode;
	pre->rlink=newNode;
}

void print_list(Node*head){
	for(Node*curr=head->rlink; curr!=head; curr=curr->rlink)
		printf("%s -> ",curr->data);
	printf("NULL\n");
}

void ddelete(Node*head,Node*remove){
	if(head==remove)
		return;
	
	remove->llink->rlink=remove->rlink;
	remove->rlink->llink=remove->llink;

	free(remove);
}

Node* search(Node*head,String s){
	Node*curr=head->rlink;
	while(curr!=head){
		if(strcmp(curr->data,s)==0)
			return curr;
		curr=curr->rlink;
	}

	return head;
}
	
		
