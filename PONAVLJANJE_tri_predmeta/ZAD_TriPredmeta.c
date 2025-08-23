/*Napisati program koji za tri razlièita predmeta èita ime i prezime studenta te njegovu ocjenu.Podaci o
svakom predmetu se nalaze u odvojenoj datoteci i iz svake datoteke je potrebno kreirati vezanu listu i
ispisati je.
a) Nakon toga potrebno je kreirati novu listu koja sadrži imena studenata koji su položili sva tri
predmeta.
b) Nadopuniti zadatak pod a) tako da se ispiše nova vezana lista koja osim što sadrži imena
studenata, sadrži i njihovu prosjeènu ocjenu iz ta tri predmeta.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _student {
	char ime[20];
	char prezime[20];
	int ocjena;
	struct _student* next;
}student;

void otvaranjeDatoteke(const char* dat, student* p);
void stvoriListu(student* p, char* sime, char* sprezime, int socjena);
void ispisListe(student* p);
void freeList(student* p);
int pronadiStudenta(student* p,char* sime, char* sprezime);
void prosliSve(student* p1, student* p2, student* p3, student* r);

int main() {

	struct _student Head1;
	Head1.next = NULL;
	struct _student Head2;
	Head2.next = NULL;
	struct _student Head3;
	Head3.next = NULL;
	struct _student Headr;
	Headr.next = NULL;

	const char* pred1 = "matematika.txt";
	const char* pred2 = "fizika.txt";
	const char* pred3 = "elektronika.txt";

	otvaranjeDatoteke(pred1, &Head1);
	otvaranjeDatoteke(pred2, &Head2);
	otvaranjeDatoteke(pred3, &Head3);

	printf("MATEMATIKA: \n");
	ispisListe(&Head1);
	printf("---------------------------\n");
	printf("FIZIKA: \n");
	ispisListe(&Head2);
	printf("---------------------------\n");
	printf("ELEKTRONIKA: \n");
	ispisListe(&Head3);
	printf("---------------------------\n");

	prosliSve(&Head1, &Head2, &Head3, &Headr);
	printf("PROSLI SVE:\n");
	ispisListe(&Headr);

	freeList(&Head1);
	freeList(&Head2);
	freeList(&Head3);
	freeList(&Headr);


	return 0;
}

void otvaranjeDatoteke(const char* dat, student* p) {
	FILE* fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Datoteka nije otvorena!\n");
		exit(1);
	}
	char sime[20];
	char sprezime[20];
	int socjena;
	char buffer[255];
	while (fgets(buffer, 255, fp) != NULL) {
		sscanf(buffer, "%s %s %d", sime, sprezime, &socjena);
		stvoriListu(p, sime, sprezime, socjena);
	}

	fclose(fp);
}

void stvoriListu(student* p, char* sime, char* sprezime, int socjena) {
	student* prev = p;
	student* curr = p->next;
	
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
	}
	student* q = malloc(sizeof(student));
	if (q == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		exit(2);
	}
	strcpy(q->ime, sime);
	strcpy(q->prezime, sprezime);
	q->ocjena = socjena;
	q->next = curr;
	prev->next = q;
}

void ispisListe(student* p) {
	student* curr = p->next;
	while (curr != NULL) {
		if (curr->ocjena > 0)
			printf("%s %s %d\n", curr->ime, curr->prezime, curr->ocjena); //objasnjenje uvjeta u funkciji prosliSve
		else
			printf("%s %s\n", curr->ime, curr->prezime);
		curr = curr->next;
	}
	printf("\n");
}

void freeList(student* p) {
	student* curr = p->next;
	student* temp;
	while (curr != NULL) {
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	p->next = NULL;
}

int pronadiStudenta(student* p, char* sime, char* sprezime) {
	student* curr = p->next;
	while (curr != NULL) {
		if (strcmp(curr->ime, sime) == 0 && strcmp(curr->prezime, sprezime) == 0)
			return curr->ocjena >= 2;
		curr = curr->next;
	}

	return 0;
}

void prosliSve(student* p1, student* p2, student* p3, student* r) {
	student* curr1 = p1->next;
	while (curr1 != NULL) {
		if (curr1->ocjena >= 2 && pronadiStudenta(p2, curr1->ime, curr1->prezime) && pronadiStudenta(p3, curr1->ime, curr1->prezime)) {
			stvoriListu(r, curr1->ime, curr1->prezime, 0); /*ocjena je 0 tako da zbog uvjeta u funkciji ispisListe
		                                                     kod ispisivanja studenata koji su prosli sve prikaze samo
															 ime i prezime BEZ OCJENE*/
		}

		curr1 = curr1->next;
	}
}
