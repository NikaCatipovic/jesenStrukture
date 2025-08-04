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

typedef struct student_ {
	char name[20];
	char surname[20];
	int grade;
	struct student_* next;
}student;

void reading(char* dat, student* p);
void addE(student* p, char* ime, char* prezime, int ocjena);
void printList(student* p);
void freeList(student* p);
int findPass(student* p, char* ime, char* prezime);
void passAll(student* p1, student* p2, student* p3, student* r);



int main() {

	struct student_ Head1;
	Head1.next = NULL;
	struct student_ Head2;
	Head2.next = NULL;
	struct student_ Head3;
	Head3.next = NULL;
	struct student_ Headr;
	Headr.next = NULL;

	const char* pred1 = "predmet1.txt";
	const char* pred2 = "predmet2.txt";
	const char* pred3 = "predmet3.txt";

	reading(pred1, &Head1);
	reading(pred2, &Head2);
	reading(pred3, &Head3);

	printf("PREDMET1: \n");
	printList(&Head1);
	printf("------------------------------------------------------\n");
	printf("PREDMET2: \n");
	printList(&Head2);
	printf("------------------------------------------------------\n");
	printf("PREDMET3: \n");
	printList(&Head3);
	
	passAll(&Head1, &Head2, &Head3, &Headr);
	printf("------------------------------------------------------\n");
	printf("PROSLI SVE PREDMETE: \n");
	printList(&Headr);
	
	freeList(&Head1);
	freeList(&Head2);
	freeList(&Head3);
	freeList(&Headr);


	return 0;
}

void reading(char* dat, student* p) {
	char ime[20], prezime[20];
	int ocjena;
	FILE* fp = fopen(dat,"r");
	if (fp == NULL){
		printf("Datoteka nije otvorena!\n"); 
		exit(1);
		}
	char buffer[255];
	while(fgets(buffer, 255, fp) != NULL) {
		sscanf(buffer, "%s %s %d", ime, prezime, &ocjena);
		addE(p, ime, prezime, ocjena );
	}

	fclose(fp);
}

void addE(student* p, char* ime, char* prezime, int ocjena) {
	student* q = malloc(sizeof(student));
	if (q == NULL) {
		printf("Neuspjesna alokacija!\n");
		exit(2);
	}
	strcpy(q->name, ime);
	strcpy(q->surname, prezime);
	q->grade = ocjena;
	q->next = NULL;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = q;

}

void printList(student* p) {
	student* temp = p->next;
	while (temp != NULL) {
		if(temp->grade > 0){ printf("%s %s %d\n ", temp->name, temp->surname, temp->grade); }
		else { printf("%s %s\n", temp->name, temp->surname); }
		
		temp = temp->next;
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

int findPass(student* p, char* ime, char* prezime) {
	student* curr = p->next;
	while (curr != NULL) {
		if (strcmp(curr->name, ime) == 0 && strcmp(curr->surname, prezime) == 0) {
			return curr->grade >= 2;
		}
		//else { return 0; }
		curr = curr->next;

		
	}

	return 0; //ako uvjet od if nije ispunjen -> ako ne nade osobu
}

void passAll(student* p1, student* p2, student* p3, student* r) {
	student* curr1 = p1->next;
	while (curr1 != NULL) {
		if (curr1->grade >= 2 && findPass(p2, curr1->name, curr1->surname) && findPass(p3, curr1->name, curr1->surname)) {
			addE(r, curr1->name, curr1->surname, 0);
		}

		curr1 = curr1->next;
	}
	
}