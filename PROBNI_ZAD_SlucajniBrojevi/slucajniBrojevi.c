/*Napisati program koji generira slucajne brojeve u opsegu
130-160. Ukoliko broj ne postoji u vezanoj listi dodaje se
sortirano po vrijednosti, a ukoliko broj vec postoji u
vezanoj listi samo se uvecava broj ponavljanja tog broja.
Ispisati listu (vrijednost i broj ponavljanja).

OCJENA 2:Pronaci broj/brojeve koji su se ponovili najmanje puta i ispisati ih.*/

#define _CRT_SECURE_NO_WARNINGS
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
void printList(Number* p);
void freeList(Number* p);
int findMin(Number* p);
void printMin(Number* p);


int main() {

	struct _number Head;
	Head.next = NULL;

	srand((unsigned)time(NULL));  //NIKA NE SMIS OVO ZABORAVIT!
	addEnd(&Head);
	printList(&Head);

	printf("------------------\n");
	printf("Broj/evi koji (su) se najmanje puta pojavio/li: \n");
	printMin(&Head);

	freeList(&Head);

	return 0;
}

void addEnd(Number* p) {
	
	int i;
	for (i = 0; i < 100; i++) {
	int br = rand() % (160 - 130 + 1) + 130;
	Number* prev = p;
	Number* curr = p->next;

	while (curr != NULL && curr->value < br) {
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL && curr->value == br) {

		curr->no_repeats = curr->no_repeats + 1;
		continue; //ako je return onda ne radi ispravno
	}
	Number* q = malloc(sizeof(Number));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		exit(1);
	}
	q->value = br;
	q->no_repeats = 1;
	q->next = curr;
	prev->next = q;

	}
}

void printList(Number* p) {
	Number* curr = p->next;
	while (curr != NULL) {
		printf("%d %d\n", curr->value, curr->no_repeats);
		curr = curr->next;
		
	}
	
	printf("\n");
}

void freeList(Number* p) {
	Number* curr = p->next;
	Number* temp;
	while (curr != NULL) {
		temp = curr;
		curr = curr->next;
		free(temp);
	}

	p->next = NULL;
}

int findMin(Number* p) {
	Number* curr = p->next;
	int min = curr->no_repeats;
	curr = curr->next;

	while (curr != NULL) {
		if (curr->no_repeats < min)
			min = curr->no_repeats;
		curr = curr->next;
	
	}
	return min;

}

void printMin(Number* p) {
	int min = findMin(p);

	Number* curr = p->next;

	while (curr != NULL) {
		if (curr->no_repeats == min)
			printf("%d %d\n", curr->value, curr->no_repeats);

		curr = curr->next;

	}
}