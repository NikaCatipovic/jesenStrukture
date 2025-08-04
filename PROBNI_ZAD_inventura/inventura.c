/* Napisati program koji iz datoteke „inventura.txt“ cita 
podatke o tehnoloskoj opremi u ucionici u formatu :
<naziv> <cijena>
Procitane podatke potrebno je ucitati u vezanu listu 
sortiranu po nazivu opreme, na nacin da se ne smije 
ponavljati oprema istog naziva (npr.Ako postoji vise tipkovnica
u datoteci, vezana lista treba sadrzavati jedan cvor naziva 
tipkovnica s kolicinom koja predstavlja kolicinu svih tipkovnica)

Cvor vezane liste definiran je strukturom :
#define MAX_NAME (64)
struct  _item;
typedef struct _item* ItemP;
typedef struct _item {
    char name[MAX_NAME];
    int quantity;
    ItemP next;
} Item;

Ocjena 2: ispisati ucitanu vezanu listu u formatu :
Tipkovnica 3
Miš 2
Zvucnik 1
…
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME (64)

struct _item;
typedef struct _item* ItemP;
typedef struct _item {
    char name[MAX_NAME];
    int quantity;
    ItemP next;
} Item;

void otvaranje(char* dat, Item* p);
void lista(Item* p, char* naziv, int kolicina);
void printList(Item* p);
void freeList(Item* p);

int main() {

    struct _item Head;
    Head.next = NULL;

    otvaranje("inventura.txt", &Head);
    printList(&Head);
    freeList(&Head);

    return 0;
}

void otvaranje(char* dat, Item* p) {

    char naziv[MAX_NAME];
    int kolicina;
    
    FILE* fp = fopen(dat, "r");
    if (fp == NULL) {
        printf("Datoteka nije otvorena!\n");
        exit(1);
    }
    char buffer[255];
    while (fgets(buffer, 255, fp) != NULL) {
        sscanf(buffer,"%s %d", naziv, &kolicina);
        lista(p, naziv, kolicina);
    }

    fclose(fp);
}

void lista(Item* p, char* naziv, int kolicina) {
    
    Item* prev = p;
    Item* curr = p->next;

    while (curr != NULL && strcmp(curr->name, naziv) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL && strcmp(curr->name, naziv) == 0) {
        curr->quantity = curr->quantity + kolicina;
        return;
    }
    
    Item* q = malloc(sizeof(Item));
    if (q == NULL) {
        printf("Pogresna alokacija memorije!\n");
        exit(2);
    }
    
    strcpy(q->name, naziv);
    q->quantity = kolicina;

    q->next = curr;
    prev->next = q;
}

void printList(Item* p) {
    Item* curr = p->next;
    while (curr != NULL) {
        printf("%s %d\n", curr->name, curr->quantity);
        curr = curr->next;
    }
    printf("\n");
}

void freeList(Item* p) {
    Item* curr = p->next;
    Item* temp;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    p->next = NULL;
}