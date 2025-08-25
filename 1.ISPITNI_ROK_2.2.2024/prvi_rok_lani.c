/*Napisati program koji iz datoteke "Studenti.txt" cita 
podatke o studentima i njihovim mticnim brojevima, te 
podatke sprema u vezanu listu sortiranu po prezimenu i 
imenu studenta.
Iz datoteke "Predmet1.txt" procitati maticni broj studenta
i ocjenu iz predmeta, te ih upisati u odgovarajuci element
liste. Ispisati listu.
U izradi zadatka moze se koristit struktura:
#define MAX_NAME_LEN (32)
struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	int idNumber;
	int grade;
	StudentP Next;
}Student;
OCJENA 2: Unijeti ime s tastature, te iz liste izbrisati sve
one studente koji se tako zovu. Ispisati listu.
OCJENA 3: Iz postojece liste kreirati novu listu studenata
koji su polozili predmet. Pri tome se ne smije koristiti
nova alokacija, vec se samo pomicu pokazivaci. Na kraju, u
jednoj listi su studenti koji nisu polozili predmet, a u drugoj
oni koji su ga polozili. Ispisati obje liste.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN (32)

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	int idNumber;
	int grade;
	StudentP Next;
}Student;

void citanjeDatoteke(const char* file, Student* p);
void sortiranaLista(Student* p, char* surname, char* name, int ID);
void ispisListe(Student* p);
void freeList(Student* p);
void otvaranjePredmet(const char* dat,Student* p);
void pretrazivanjeID(Student* p, int ID, int ocjena);
void ocjena2(Student* p);
void ocjena3(Student* p, Student* p1);


int main() {

	struct _student Head;
	Head.Next = NULL;
	struct _student Head1;
	Head1.Next = NULL;

	const char* file = "Studenti.txt";
	const char* dat = "Predmet1.txt";

	citanjeDatoteke(file, &Head);
	otvaranjePredmet(dat, &Head);
	ispisListe(&Head);
	printf("--------------------------\n");
	ocjena2(&Head);
	printf("NOVA LISTA: \n");
	ispisListe(&Head);
	ocjena3(&Head, &Head1);
	printf("------------------------\n");
	printf("Studenti koji su prosli: \n");
	ispisListe(&Head1);
	printf("------------------------\n");
	printf("Studenti koji nisu prosli: \n");
	ispisListe(&Head);



	return 0;
}

void citanjeDatoteke(const char* file, Student* p) {
	FILE* fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Datoteka nije otvorena!\n");
		exit(1);
	}
	char name[MAX_NAME_LEN], surname[MAX_NAME_LEN];
	int ID;
	char buffer[255];
	while (fgets(buffer, 255, fp) != NULL) {
		sscanf(buffer, "%s %s %d", surname, name, &ID);
		sortiranaLista(p, surname, name, ID);
	}
	fclose(fp);
}

void sortiranaLista(Student* p, char* surname, char* name, int ID) {
	Student* prev = p;
	Student* curr = p->Next;
	while (curr != NULL && (strcmp(curr->lastName, surname) < 0 || strcmp(curr->lastName,surname)==0 && strcmp(curr->firstName,name)<0)){
		prev = curr;
		curr = curr->Next;
	}
	
	Student* q = malloc(sizeof(Student));
	if (q == NULL) {
		printf("Alokacija nije uspjesna!\n");
		exit(2);
	}
	strcpy(q->lastName, surname);
	strcpy(q->firstName, name);
	q->idNumber = ID;
	prev->Next = q;
	q->Next = curr;

}

void ispisListe(Student* p) {
	Student* curr = p->Next;
	while (curr != NULL) {
		printf("%s %s %08d %d\n", curr->lastName, curr->firstName, curr->idNumber, curr->grade);
		curr = curr->Next;
	}
	printf("\n");
}

void freeList(Student* p) {
	Student* curr = p->Next;
	Student* temp;
	while (curr != NULL) {
		temp = curr;
		curr = curr->Next;
		free(temp);
	}
}

void otvaranjePredmet(const char* dat, Student* p) {
	FILE* f = fopen(dat, "r");
	if (f == NULL) {
		printf("Datoteka nije otvorena!\n");
		exit(3);
	}
	int ID, ocjena;
	char buffer[255];
	while (fgets(buffer, 255, f) != NULL) {
		sscanf(buffer, "%d %d", &ID, &ocjena);
		pretrazivanjeID(p, ID, ocjena);
	}
}

void pretrazivanjeID(Student* p, int ID, int ocjena) {
	Student* curr = p->Next;
	while (curr != NULL) {
		if (curr->idNumber == ID) {
			curr->grade = ocjena;
			return;
		}
		curr = curr->Next;
	}

}

void ocjena2(Student* p) {
	printf("Unesi ime koje zelis izbrisati: \n ");
	char ime[MAX_NAME_LEN];
	scanf("%s", ime);
	Student* prev = p;
	Student* curr = p->Next;
	Student* temp;
	while (curr != NULL) {
		if (strcmp(curr->firstName, ime) == 0) {
			printf("Odabrali ste %s %s\n", curr->lastName, curr->firstName);
			temp = curr;
			prev->Next = temp->Next;
			free(temp);

			return;
		}
		prev = curr;
		curr = curr->Next;

	}
	printf("Odabrani student/ica ne postoji u listi!\n");
	
}

void ocjena3(Student* p, Student* p1) {
	Student* prev = p;
	Student* curr = p->Next;
	Student* sec = p1;
	while (curr != NULL) {
		if (curr->grade >= 2) {
			prev->Next = curr->Next;
			sec->Next = curr;
			curr->Next = NULL;
			sec = sec->Next;
			curr = prev->Next;
		}
		else {
			prev = curr;
			curr = curr->Next;
		}
	}
}
	