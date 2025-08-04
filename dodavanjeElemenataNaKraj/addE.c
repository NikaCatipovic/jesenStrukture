#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
}Node;

void addB(Node* p, int x);
void printList(Node* p);
void addE(Node* p, int x);


int main() {

	struct node Head;
	Head.next = NULL;

	addB(&Head, 3); printList(&Head);
	addB(&Head, 2); printList(&Head);
	addB(&Head, 1); printList(&Head);
	addE(&Head, 4);
	printList(&Head);
	
	
	
	return 0;
}

void addB(Node* p, int x) {
	Node* q = (Node*)malloc(sizeof(Node));
	if (q == NULL) {
		printf("Error!\n");
		return;
	}
	q->data = x;
	q->next = p->next;
	p->next = q;
		
}

void printList(Node* p) {
	Node* temp = p->next;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;//printanje iducega!!
	}
	printf("\n");
}

void addE(Node* p, int x) {
	Node* q = (Node*)malloc(sizeof(Node));
	if (q == NULL) {
		printf("Error!\n");
		return;
	}
	q->data = x;
	q->next = NULL;
	while (p->next != NULL) {
		
		p = p->next;
	}
	p->next = q;
}