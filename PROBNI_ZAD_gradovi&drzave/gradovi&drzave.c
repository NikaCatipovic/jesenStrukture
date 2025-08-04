/*Napisati program koji iz datoteke "travel_data.txt"
cita na koji datum je posjecen neki grad i podatke
sprema u vezanu listu tako da se svaki novi podatak
dodaje na kraj. Nakon toga postojeæu vezanu listu
treba nadopuniti s podacima u kojoj se drzavi nalazi
koji grad. Ti podaci se nalaze u datoteci "cities.txt"

OCJENA 2: Ispisati vezanu listu.
OCJENA 3: Unijeti neki datum i izbrisati sve posjete
koji su se dogodili na taj datum. Ispisati novu listu.
OCJENA 4: Pronaci koja je drzava posjecena najvise puta
i ispisati njen naziv i gradove koji su posjeceni.
OCJENA 5: Izbrisati cijelu listu na nacin da se uvijek
trazi koja je drzava posjecena najvise puta i onda se
iz liste brise ta drzava. Postupak se ponavlja dok se
ne izbrise cijela lista.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN (32)

typedef struct _date {
	int day;
	int month;
	int year;
}Date;

struct _visit;
typedef struct _visit* VisitP;
typedef struct _cvisit {
	char cityname[MAX_NAME_LEN];
	char Country[MAX_NAME_LEN];
	Date visitDate;
	VisitP Next;
}Visit;

void reading(char* dat, Visit* p);
void addEnd(Visit* p, int dan, int misec, int godina, char* grad);

int main() {

	struct _cvisit Head;
	Head.Next = NULL;

	FILE* fp = fopen("travel_data.txt", "r");

	char buffer[255];
	int brojac;
	while (fgets(buffer, 255, fp) != NULL) {
		brojac++;
	}
	Date* datum;
	datum = malloc(sizeof(Date)*brojac);

	return 0;
}

void reading(char* dat, Visit* p) {
	FILE* fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Neuspjesno otvaranje datoteke!\n");
		exit(1);
	}
	char buffer[255];
	int dan, misec, godina;
	char grad[20];
	while (fgets(buffer, 255, fp)!=NULL){
		sscanf(buffer, "%d.%d.%d	%s", &dan, &misec, &godina, grad);

	}


}

void addEnd(Visit* p, int dan, int misec, int godina, char* grad) {
	Visit* q = malloc(sizeof(Visit));
	if (q == NULL) {
		printf("Pogresna alokacija memorije!\n");
		exit(2);
	}
	q->Next = NULL;


}