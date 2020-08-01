#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 30

typedef char element;
typedef struct node{
	element data[MAX];
	struct node*link;
}Node;

//원형연결리스트이므로 head노드가 마지막 노드를 가르키고있다
void print_list(Node*head); //원형연결리스트이므로 처음에 조건을 검사하지 않는 do while을 사용
Node* insert_last(Node*head,char *item);
Node* insert_first(Node*head,char *item);
void delete(Node*head,Node*pre);
Node* search(Node*head,char *item);
int node_count(Node*head,Node*temp);

int main (void){
	Node* head1=NULL;
	head1=insert_first(head1,"Red");
	head1=insert_first(head1,"Green");
	head1=insert_first(head1,"Blue");

	print_list(head1);

	head1=insert_last(head1,"is");
	head1=insert_last(head1,"RGB");

	print_list(head1);

	if(search(head1,"Blue"))
		printf("%s 노드를 찾았습니다!\n",search(head1,"Blue")->data);
	else
		printf("노드가 존재하지 않습니다\n");

	delete(head1,head1); //head의 다음노드를 삭제 == 첫노드 삭제

	if(search(head1,"Blue"))
		printf("%s 노드를 찾았습니다!\n",search(head1,"Blue")->data);
	else
		printf("노드가 존재하지 않습니다\n");

	printf("노드의 개수는 %d\n",node_count(head1,head1->link));

	for(int i=0;i<10;i++){
		head1=head1->link;
		printf("%s -> ",head1->data);
	}

	
	return 0;

}
int node_count(Node*head,Node*temp){
	if(temp==head)
		return 1;
	else
		return 1+node_count(head,temp->link);
}
Node* insert_first(Node*head,element item[MAX]){
	Node*newNode=malloc(sizeof(Node));
	strcpy(newNode->data,item);

	if(!head){
		head=newNode;
		newNode->link=newNode;
	}
	else{
		newNode->link=head->link;
		head->link=newNode;
	}

	return head;
}

Node* insert_last(Node*head,element item[MAX]){ //맨 뒤에 삽입 후 head노드의 위치를 변경
	Node*newNode=malloc(sizeof(Node));
	strcpy(newNode->data,item);

	if(!head){
		head=newNode;
		newNode->link=newNode;
	}
	else{
		newNode->link=head->link;
		head->link=newNode;
		head=newNode;
	}

	return head;
}

void print_list(Node*head){
	if(!head){
		printf("출력할 노드가 존재하지 않습니다!\n");
		return;
	}
	Node*curr=head;
	do{
		curr=curr->link;
		printf("%s -> ",curr->data);
	}while(curr!=head);
	printf("\n\n");
}

Node* search(Node*head,element item[MAX]){
	Node*curr=head;
	do{
		curr=curr->link;
		if(strcmp(curr->data,item)==0)
			return curr;
	}while(curr!=head);

	return NULL;
}

void delete(Node*head,Node*pre){ //삭제할 노드의 전노드 주소
	if(!head || !pre){
		printf("삭제실패!\n");
		return;
	}

	Node*remove=pre->link;
	pre->link=remove->link;

	free(remove);
	printf("삭제완료!\n");

}
