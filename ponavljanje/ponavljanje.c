#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
}Node;

void upisiP(Node* p, int x);
void ispisiListu(Node* p);

int main() {

	struct node Head;
	Head.next = NULL;

	upisiP(&Head, 5);
	ispisiListu(&Head);
	upisiP(&Head, 9);
	ispisiListu(&Head);
	upisiP(&Head, 0);
	ispisiListu(&Head);

	return 0;
}

void upisiP(Node* p, int x) {
	Node* q = (Node*)malloc(sizeof(Node));
	if (q == malloc) {
		printf("Neuspjela alokacija memorije!\n");
	}
	q->data = x;
	q->next = p->next;
	p->next = q;
}

void ispisiListu(Node* p) {
	
	while (p->next != NULL) {
		printf("%d ", p->next->data);
		p = p->next;
	}
	    
	printf("\n");
}