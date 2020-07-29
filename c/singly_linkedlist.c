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

Node* insert_sort(Node*head,char item[MAX]); //오름차순 연결
Node* insert_last(Node*head,char item[MAX]); //맨 뒤에 연결
Node* insert_first(Node*head,char item[MAX]);//맨 앞에 연결
Node* insert(Node*head,Node*pre,char item[MAX]);//pre노드 뒤에 연결
Node* search(Node*head,char find[MAX]);
Node* delete(Node*head,char find[MAX]);
void print_reverse(Node*head);
int main (void){

	int n; bool answer=true;
	char find[MAX];
	Node*head=NULL;

	while(answer){
		printf("1.끝에 연결  2.첨에 연결 3.오름차순연결  0.종료\n==>");
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
			case 3:
				head=NULL;
				head=insert_sort(head,"hello");
				head=insert_sort(head,"my");
				head=insert_sort(head,"name");
				head=insert_sort(head,"is");
				head=insert_sort(head,"yujin");
				break;
			case 0:
				answer=false;
				break;
			default:
				return 0;	
		}

		for(Node*curr=head; curr; curr=curr->link)
			printf("%s ",curr->data.string);
		printf("\n");
		print_reverse(head); printf("\n");
	}

	answer=true;

	scanf("%s",find);
	
	if(search(head,find))
		printf("%s 노드를 찾았습니다!\n", search(head,find)->data.string);
	else
		printf("노드를 찾지 못했습니다\n");

	head=delete(head,find);

	if(search(head,find))
		printf("%s 노드를 찾았습니다!\n", search(head,find)->data.string);
	else
		printf("노드를 찾지 못했습니다\n");

	return 0;
}

Node* insert_sort(Node*head,char item[MAX]){
	Node*newNode=malloc(sizeof(Node));
	strcpy(newNode->data.string,item);

	if(head==NULL)
		head=newNode;
	else{
		if(strcmp(head->data.string,newNode->data.string)==1){ //노드 맨앞에 연결
			newNode->link=head;
			head=newNode;
		}
		else{
			Node*curr=head;
			while(curr->link){ 
				if(strcmp(curr->link->data.string,newNode->data.string)>0){
					newNode->link=curr->link;
					curr->link=newNode;
					return head; //오름차순 삽입 
				}
				curr=curr->link;
			}
			curr->link=newNode; //노드 맨뒤에 삽입 
			newNode->link=NULL;
		}
	}	
	return head;
}

void print_reverse(Node*head){
	if(head==NULL)
		printf("NULL->");
	else{
		print_reverse(head->link);
		printf("%s->",head->data.string);
	}
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

Node* delete(Node*head,char find[MAX]){
	if(head==NULL)
		printf("삭제오류!\n");
	else{
		if(!strcmp(head->data.string,find)){
			Node*temp=head;
			head=head->link;
			free(temp);
			printf("삭제완료!\n");
		}
		else{
			Node*curr=head;
			while(curr->link){
				if(!strcmp(curr->link->data.string,find)){
					Node*temp=curr->link;
					curr->link=temp->link;
					free(temp);
					printf("삭제완료!\n");
					return head;
				}
				curr=curr->link;
			}
			printf("삭제오류! 존재하지않는 노드!\n");
		}
	}
	return head;
}

Node* search(Node*head,char find[MAX]){
	if(!head)
		return NULL;
	if(!strcmp(head->data.string,find))
		return head;
	else 
		return search(head->link,find);
}



