#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct cvor {
	int info;
	struct cvor* next;
}Cvor;

void upisP(Cvor* p,int x);
void ispisListe(Cvor* p);
void upisK(Cvor* p, int x);
void upisIza(Cvor* p, int x, int y);
void upisIspred(Cvor* p, int x, int y);
void brisiEl(Cvor* p, int x);

int main() {

	struct cvor Head;
	Head.next = NULL;

	/*upisP(&Head, 4); ispisListe(&Head);
	upisP(&Head, 2); ispisListe(&Head);
	upisP(&Head, 8); ispisListe(&Head);
	upisK(&Head, 3); ispisListe(&Head);
	upisIza(&Head, 2, 7); ispisListe(&Head);
	upisIspred(&Head, 3, 9); ispisListe(&Head);
	upisIspred(&Head, 8, 1); ispisListe(&Head);
	upisIza(&Head, 3, 5); ispisListe(&Head);
	brisiEl(&Head, 7); ispisListe(&Head);
	brisiEl(&Head, 1); ispisListe(&Head);*/
	
	int funkcija,x,y;

	do {

		printf("Odaberi funkciju: \n");
		printf("1-upisi element na pocetak liste\n");
		printf("2-upisi element na kraj liste\n");
		printf("3-upisi element iza odredenog elementa\n");
		printf("4-upisi element ispred odredenog elementa\n");
		printf("5-izbrisi element\n");
		scanf("%d", &funkcija);

		switch (funkcija) {
		case 1:
			printf("Odaberi vrijednost: \n");
			scanf("%d", &x);
			upisP(&Head, x);
			ispisListe(&Head);
			break;
		case 2:
			printf("Odaberi vrijednost: \n");
			scanf("%d", &x);
			upisK(&Head, x);
			ispisListe(&Head);
			break;
		case 3:
			printf("Odaberi vrijednost iza koje se unosi novi element: \n");
			scanf("%d", &x);
			printf("Odaberi vrijednost novog elementa: \n");
			scanf("%d", &y);
			upisIza(&Head, x, y);
			ispisListe(&Head);
			break;
		case 4:
			printf("Odaberi vrijednost ispred koje se unosi novi element: \n");
			scanf("%d", &x);
			printf("Odaberi vrijednost novog elementa: \n");
			scanf("%d", &y);
			upisIspred(&Head, x, y);
			ispisListe(&Head);
			break;
		case 5:
			printf("Odaberi koji element izbrisati: \n");
			scanf("%d", &x);
			brisiEl(&Head, x);
			ispisListe(&Head);
			break;
		case 0:
			printf("Izlaz\n");
			printf("---------------------------- \n");
			ispisListe(&Head);
			break;
		default:
			printf("Nepostojeci izbor\n");

		}
	} while (funkcija != 0);


	return 0;
}

void upisP(Cvor* p, int x) {
	Cvor* q = malloc(sizeof(Cvor));
	if (q == NULL) {
		printf("Alokacija memorije nije dobra!\n");
		exit(1);
	}
	q->info = x;
	q->next = p->next;
	p->next = q;
}

void ispisListe(Cvor* p) {
	Cvor* temp;
	temp = p->next;
	while (temp != NULL) {
		printf("%d ", temp->info);
		temp = temp->next;
	}
	printf("\n");

}

void upisK(Cvor* p, int x) {
	Cvor* q = malloc(sizeof(Cvor));
	if (q == NULL) {
		printf("Alokacija memorije nije dobra!\n");
		exit(2);
	}
	
	while (p->next != NULL) {
		p = p->next;
	}
	q->info = x;
	q->next = NULL;
	p->next= q;
}

void upisIza(Cvor* p, int x, int y) {
	Cvor* q = malloc(sizeof(Cvor));
	if (q == NULL) {
		printf("Alokacija memorije nije dobra!\n");
		exit(3);
	}
	Cvor* curr = p->next;//prvi iduci element nakon Heada = prvi stvarni el
	while (curr != NULL && curr->info != x) {
		curr = curr->next;
	}
	if (curr == NULL) {
		printf("Element nije u listi!\n");
		return;
	}
	q->info = y;
	q->next =curr->next;
	curr->next = q;
}

void upisIspred(Cvor* p, int x, int y) {
	Cvor* q = malloc(sizeof(Cvor));
	if (q == NULL) {
		printf("Alokacija memorije nije dobra!\n");
		exit(4);
	}
	q->info = y;
	Cvor* prev = p;
	Cvor* curr = p->next;
	while (curr != NULL && curr->info != x) {
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL) {
		printf("Element nije u listi!\n");
		free(q);
		return;
	}
	prev->next = q;
	q->next = curr;
	

}

void brisiEl(Cvor* p, int x) {
	Cvor* curr = p->next;
	Cvor* prev = p;
	while (curr != NULL && curr->info != x) {
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL) {
		printf("Element nije u listi!\n");
		return;
	}
	prev->next = curr->next;
	free(curr);
}