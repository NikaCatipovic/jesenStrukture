/*Napisati program koji iz datoteke "studenti.txt" cita prezime
i ime studenta kao i njegov ID, te kreira vezanu listu sortiranu
po prezimenu i imenu studenta.
Nakon toga iz datoteka "predmet1.txt" i "predmet2.txt" se cita
ID studenta, ocjena i datum polaganja predmeta. Procitane podatke
je potrebno unijeti u postojecu vezanu listu. Ispisati listu.
Student je definirana strukturom:
--------------------------------
#define MAX_NAME_LEN (32)
struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char ID[10];
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	int grade[2];
	Date date[2];
}Student;
Datum je definiran strukturom:
-----------------------------
struct _date;
typedef struct _date {
	int year;
	int month;
	int day;
} Date;

OCJENA 2: Unijeti jedan datum i izbrisati iz liste sve one osobe
koje su polozile bilo koji od predmeta na taj datum. Ispisati 
novu vezanu listu.
OCJENA 3: Pronaci za svaki predmet osobe koje su ga polozile na
najraniji datum i prebaciti ih na kraj liste. Pri tome treba
voditi racuna da je vise osoba polozilo svaki pojedini predmet
na taj datum. Ispisati novu vezanu listu.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN (32)

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char ID[10];
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	int grade[2];
	Date date[2];
	StudentP next;  //ja dodala
}Student;

struct _date;
typedef struct _date {
	int year;
	int month;
	int day;
} Date;

void otvaranje(const char* dat, Student* p);
void sortiraniStudenti(Student* p, char* prezime, char* ime, char* JMBS);
void ispis(Student* p);

int main() {

	struct _student Head;
	Head.next = NULL;

	const char* dat = "studenti.txt";
	otvaranje(dat, &Head);
	ispis(&Head);

	return 0;
}

void otvaranje(const char* dat, Student* p) {
	FILE* fp = fopen(dat, "r");
	if (fp == NULL) {
		printf("Datoteka nije otvorena!\n");
		exit(1);
	}
	char buffer[255];
	char JMBS, ime, prezime;
	while (fgets(buffer, 255, fp) != NULL) {
		sscanf(buffer, "%s %s %s", prezime, ime, JMBS);
		sortiraniStudenti(p, prezime, ime, JMBS);
	}

	fclose(fp);
}

void sortiraniStudenti(Student* p, char* prezime, char* ime, char* JMBS) {
	Student* prev = p;
	Student* curr = p->next;
	
	while (curr != NULL && (strcmp(curr->lastName, prezime) < 0 || strcmp(curr->lastName, prezime) ==0 && strcmp(curr->firstName, ime) < 0)) {

		prev = curr;
		curr = curr->next;

	}

	Student* q = malloc(sizeof(Student));
	if (q == NULL) {
		printf("Neuspjesna alokacija memorije\n");
		exit(2);
	}
	strcpy(q->lastName, prezime);
	strcpy(q->firstName, ime);
	strcpy(q->ID, JMBS);
	prev->next = q;
	q->next = curr;

}

void ispis(Student* p) {
	Student* curr = p->next;
	while (curr != NULL) {
		printf("%s %s %s\n", curr->lastName, curr->firstName, curr->ID);
		curr = curr->next;
	}
	printf("\n");
} 