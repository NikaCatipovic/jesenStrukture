#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
}Node;

void addB(Node* p, int x);
void ispis(Node* p);

int main() {

	struct node Head;
	Head.next = NULL;

	addB(&Head, 3);
	ispis(&Head);
	addB(&Head, 5);
	ispis(&Head);
	addB(&Head, 7);
	ispis(&Head);

	
	
	return 0;
}

void addB(Node* p, int x) {
	
	Node* q = (Node*)malloc(sizeof(Node));
	if (q == NULL) {
		printf("Error\n");
		return;
	}
	

	q->next = p->next;
	q->data = x;
	p->next = q;

}

void ispis(Node* p) {

	Node* temp = p->next;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}