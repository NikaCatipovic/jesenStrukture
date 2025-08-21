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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_NAME (64)

struct  _item;
typedef struct _item* ItemP;
typedef struct _item {
    char name[MAX_NAME];
    int quantity;
    ItemP next;
} Item;

void reading(const char* dat, Item* p);
void sortedList(Item* p, char* naziv);
void printList(Item* p);
void freeList(Item* p);


int main() {

    const char* dat = "inventura.txt";
    struct _item Head;
    Head.next = NULL;

    reading(dat, &Head);
    printList(&Head);
    freeList(&Head);



    return 0;
}

void reading(const char* dat, Item* p) {
    FILE* fp = fopen(dat, "r");
    if (fp == NULL) {
        printf("Datoteka nije otovrena!\n");
        exit(1);
    }
    char buffer[255];
    char naziv[MAX_NAME];
    while(fgets(buffer, 255, fp) != NULL) {
        sscanf(buffer, "%s", naziv);
        sortedList(p, naziv);

    }

    fclose(fp);
}

void sortedList(Item* p, char* naziv) {
    Item* prev = p;
    Item* curr = p->next;

    while (curr != NULL && strcmp(curr->name, naziv) < 0) {
        prev = curr;
        curr = curr->next;
    }
    if ((curr != NULL) && strcmp(curr->name, naziv) == 0) {
        curr->quantity += 1;
        return;
        
    }

    Item* q = malloc(sizeof(Item));
    if (q == NULL) {
        printf("Neuspjela alokacija memorije!\n");
        exit(2);
    }
    strcpy(q->name, naziv);
    q->quantity = 1;
    prev->next = q;
    q->next = curr;
}

void printList(Item* p) {
    Item* curr = p->next;
    while (curr != NULL) {
        printf("%s %d\n", curr->name, curr->quantity);
        curr = curr->next;
    }
}

void freeList(Item* p) {
    Item* curr = p->next;
    Item* temp;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
}