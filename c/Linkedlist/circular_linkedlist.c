#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct node{
	char data[MAX];
	struct node*link;
}Node;

void print_list(Node*head); //원형연결리스트이므로 처음에 조건을 검사하지 않는 do while을 사용
Node* insert_last(Node*head,char *item);
Node* insert_first(Node*head,char *item);
void delete(Node*head,char *item);
Node* search(Node*head,char *item);

int main (void){
	Node*head=NULL;
	head=insert_last(head,"hello");
	head=insert_last(head,"c language");
	head=insert_last(head,"python");
	
	print_list(head);

	Node*curr=head;
	for(int i=0;i<6;i++){
		printf("%s -> ",curr->data);
		curr=curr->link;
	} //원형연결 확인
	printf("\n\nhead2리스트 만들기: ");

	Node*head2=NULL;
	head2=insert_first(head2,"hello");
	head2=insert_first(head2,"c language");
	head2=insert_first(head2,"python");

	print_list(head2);

	if(search(head2,"python"))
		printf("%s 노드 찾았습니다!\n",search(head2,"python")->data);
	else
		printf("해당하는 노드를 찾을 수 없습니다.\n");

	delete(head2,"python");//첫 노드
	print_list(head2);
	delete(head2,"hello");//마지막 노드
	
//	print_list(head2);
	
	return 0;

}

Node* insert_last(Node*head,char *item){
	Node*newNode=malloc(sizeof(Node));
	strcpy(newNode->data,item);

	if(!head){
		head=newNode;
		newNode->link=newNode;
	}
	else{
		Node*curr=head;
		while(curr->link!=head)
			curr=curr->link;

		newNode->link=curr->link;
		curr->link=newNode;

	}

	return head;
}

Node* insert_first(Node*head,char *item){
	Node*newNode=malloc(sizeof(Node));
	strcpy(newNode->data,item);

	if(!head){
		head=newNode;
		newNode->link=newNode;
	}
	else{
		newNode->link=head;

		Node*curr=head;
		while(curr->link!=head)
			curr=curr->link;
		curr->link=newNode;

		head=newNode;
	}

	return head;
}

Node* search(Node*head,char *item){
	Node*curr=head;
	do{
		if(strcmp(curr->data,item)==0)
			return curr;
		curr=curr->link;
	}while(curr!=head);

	return NULL;
}

void delete(Node*head,char *item){
	if(!head)
		printf("노드가 존재하지 않습니다!\n");
	else{
		if(strcmp(head->data,item)==0){//head노드를 지워야 한다면
			Node*remove=head;
			Node*curr=head;
			while(curr->link!=head)
				curr=curr->link;
			curr->link=remove->link;
			head=head->link;

			free(remove);
			printf("제거성공!\n");
		}
		else{
			Node*curr=head;
			while(curr->link!=head){
			
				if(strcmp(curr->link->data,item)==0){
					Node*remove=curr->link;
					curr->link=remove->link;
			
					free(remove);
					printf("제거성공!\n");
					break;
				}
				curr=curr->link;
			}
		}
	}
}

void print_list(Node*head){
	Node*curr=head;
	do{
		printf("%s -> ",curr->data);
		curr=curr->link;
	}while(curr!=head);

	printf("\n\n");
}

