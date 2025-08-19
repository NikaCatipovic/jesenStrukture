#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct number;
typedef struct _number* NumberP;
typedef struct _number {
	int value;
	int no_repeats;
	NumberP next;
}Number;

void addEnd(Number* p);


int main() {

	struct _number Head;
	Head.next = NULL;

	return 0;
}

void addEnd(Number* p) {

	Number* q = malloc(sizeof(Number));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		exit(1);
	}

	Number* prev = p;
	Number* curr = p->next;

	while(curr!=NULL && curr->value >  prev->value)

	
	
	
	//q->next = NULL;
	//q->value = rand() % (130 - 160 + 1) + 130;

}