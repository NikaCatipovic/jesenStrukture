/*Napisati program koji generira slucajne brojeve u opsegu
130-160. Ukoliko broj ne postoji u vezanoj listi dodaje se
sortirano po vrijednosti, a ukoliko broj vec postoji u
vezanoj listi samo se uvecava broj ponavljanja tog broja.
Ispisati listu (vrijednost i broj ponavljanja).

OCJENA 2:Pronaci broj/brojeve koji su se ponovili najmanje puta i ispisati ih.*/

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


	int br = rand() % (130 - 160 + 1) + 130; 

	Number* prev = p;
	Number* curr = p->next;

	while(curr!=NULL && curr->value <  br){
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL && curr->value == br) {
		
		curr->no_repeats = curr->no_repeats + 1;
		return;
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
	
	
	
	
	//q->next = NULL;
	

}