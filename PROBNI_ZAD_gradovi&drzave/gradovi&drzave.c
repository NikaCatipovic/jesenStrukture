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

void readingTravel(char* dat, Visit* p);
void addEnd(Visit* p, int dan, int misec, int godina, char* grad);
void printList(Visit* p);
void readingCities(char* dat, Visit* p);
void findCity(Visit* p, char* grad, char* drzava);
void deleteDate(Visit* p);
void freeList(Visit* p);


int main() {

	struct _cvisit Head;
	Head.Next = NULL;

	const char* data = "travel_data.txt";
	const char* cit = "cities.txt";

	readingTravel(data, &Head);
	readingCities(cit, &Head);
	printList(&Head);
	deleteDate(&Head);
	freeList(&Head);
	
	



	return 0;
}

void readingTravel(char* dat, Visit* p) {
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
		addEnd(p, dan, misec, godina, grad);

	}

	fclose(fp);
}

void addEnd(Visit* p, int dan, int misec, int godina, char* grad) {
	Visit* q = malloc(sizeof(Visit));
	if (q == NULL) {
		printf("Pogresna alokacija memorije!\n");
		exit(2);
	}
	strcpy(q->cityname, grad);
	q->visitDate.day = dan;
	q->visitDate.month = misec;
	q->visitDate.year = godina;
	Visit* curr = p;
	while (curr->Next != NULL) {
		curr = curr->Next;
	}
	curr->Next = q;
	q->Next = NULL;

}

void printList(Visit* p) {
	Visit* curr = p->Next;
	while (curr != NULL) {
		
		printf("%d.%d.%d	%s %s\n", curr->visitDate.day, curr->visitDate.month, curr->visitDate.year, curr->cityname, curr->Country);
		curr = curr->Next;
	}
	printf("\n");
}

void readingCities(char* dat, Visit* p) {
	FILE* f = fopen(dat, "r");
	if (f == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		exit(3);
	}
	char buffer[255];
	char drzava[20];
	char grad[20];
	while (fgets(buffer, 255, f) != NULL) {
		sscanf(buffer,"%s %s", drzava, grad);
		findCity(p, grad, drzava);


	}
}

void findCity(Visit* p, char* grad, char* drzava) {
	Visit* curr = p->Next;
	while (curr != NULL) {
		if (strcmp(curr->cityname, grad) == 0) {

			strcpy(curr->Country, drzava);
		}


		curr = curr->Next;
	}

}

void deleteDate(Visit* p) {
	int d_dan, d_misec, d_godina;
	printf("Unesi datum: \n");
	scanf("%d.%d.%d", &d_dan, &d_misec, &d_godina);

	Visit* curr = p->Next;
	Visit* prev = p;

	while (curr != NULL) {
		if (curr->visitDate.day == d_dan && curr->visitDate.month == d_misec && curr->visitDate.year == d_godina) {
			printf("Odabran let za brisanje je	 %s %s\n", curr->cityname, curr->Country);
			Visit* temp=curr;
			curr = curr->Next;
			prev->Next = curr;
			
			free(temp);
			continue; //bez ovoga ne radi ispravno
		}
		prev = curr;
		curr = curr->Next;
		
	}

	printf("------------------------------\n");
	
	printf("NOVA LISTA: \n");
	printList(p);
}

void freeList(Visit* p) {
	Visit* curr = p->Next;
	Visit* temp;
	while (curr != NULL) {
		temp = curr;
		curr = curr->Next;
		free(temp);
	}
}