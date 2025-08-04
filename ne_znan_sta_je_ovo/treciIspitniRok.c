#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _date {
    int year;
    int month;
    int day;
} Date;

typedef struct _predmet {
    char naziv[30];
    int ocjena;
    Date datum;
    struct _predmet* next;
} Predmet;

typedef struct _student {
    int id;
    char prezime[50];
    char ime[50];
    Predmet* predmeti;
    struct _student* next;
} Student;

// ---------- PROTOTIPI FUNKCIJA ----------
Student* createStudent(int id, const char* prezime, const char* ime);
void insertSorted(Student** head, Student* novi);
void loadStudents(Student** head, const char* filename);
void loadPredmeti(Student* head, const char* filename, const char* nazivPredmeta);
void addPredmet(Student* head, int id, const char* naziv, int ocjena, Date datum);
void printList(Student* head);
void freeList(Student** head);
int compareDate(Date d1, Date d2);
void removeByDate(Student** head, Date target);
Date inputDate();

// ---------- IMPLEMENTACIJE FUNKCIJA ----------

Student* createStudent(int id, const char* prezime, const char* ime) {
    Student* novi = (Student*)malloc(sizeof(Student));
    if (!novi) {
        printf("Greska: Neuspjela alokacija memorije za studenta!\n");
        exit(EXIT_FAILURE);
    }
    novi->id = id;
    strcpy(novi->prezime, prezime);
    strcpy(novi->ime, ime);
    novi->predmeti = NULL;
    novi->next = NULL;
    return novi;
}

void insertSorted(Student** head, Student* novi) {
    if (*head == NULL || strcmp(novi->prezime, (*head)->prezime) < 0 ||
        (strcmp(novi->prezime, (*head)->prezime) == 0 &&
            strcmp(novi->ime, (*head)->ime) < 0)) {
        novi->next = *head;
        *head = novi;
        return;
    }
    Student* curr = *head;
    while (curr->next != NULL &&
        (strcmp(novi->prezime, curr->next->prezime) > 0 ||
            (strcmp(novi->prezime, curr->next->prezime) == 0 &&
                strcmp(novi->ime, curr->next->ime) > 0))) {
        curr = curr->next;
    }
    novi->next = curr->next;
    curr->next = novi;
}

void loadStudents(Student** head, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Greska: Ne mogu otvoriti datoteku %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int id;
    char prezime[50], ime[50];
    while (fscanf(fp, "%d %s %s", &id, prezime, ime) == 3) {
        Student* novi = createStudent(id, prezime, ime);
        insertSorted(head, novi);
    }
    fclose(fp);
}

void addPredmet(Student* head, int id, const char* naziv, int ocjena, Date datum) {
    Student* curr = head;
    while (curr != NULL) {
        if (curr->id == id) {
            Predmet* novi = (Predmet*)malloc(sizeof(Predmet));
            if (!novi) {
                printf("Greska: Neuspjela alokacija memorije za predmet!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(novi->naziv, naziv);
            novi->ocjena = ocjena;
            novi->datum = datum;
            novi->next = curr->predmeti;
            curr->predmeti = novi;
            return;
        }
        curr = curr->next;
    }
}

void loadPredmeti(Student* head, const char* filename, const char* nazivPredmeta) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Greska: Ne mogu otvoriti datoteku %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int id, ocjena;
    Date d;
    while (fscanf(fp, "%d %d %d-%d-%d", &id, &ocjena, &d.year, &d.month, &d.day) == 5) {
        addPredmet(head, id, nazivPredmeta, ocjena, d);
    }
    fclose(fp);
}

void printList(Student* head) {
    Student* curr = head;
    while (curr) {
        printf("ID: %d | %s %s\n", curr->id, curr->prezime, curr->ime);
        Predmet* p = curr->predmeti;
        while (p) {
            printf("    %s, Ocjena: %d, Datum: %04d-%02d-%02d\n",
                p->naziv, p->ocjena, p->datum.year, p->datum.month, p->datum.day);
            p = p->next;
        }
        curr = curr->next;
    }
}

void freeList(Student** head) {
    Student* curr = *head;
    while (curr) {
        Predmet* p = curr->predmeti;
        while (p) {
            Predmet* tmpP = p;
            p = p->next;
            free(tmpP);
        }
        Student* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    *head = NULL;
}

int compareDate(Date d1, Date d2) {
    return (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day);
}

void removeByDate(Student** head, Date target) {
    Student* curr = *head;
    Student* prev = NULL;

    while (curr) {
        int brisi = 0;
        Predmet* p = curr->predmeti;
        while (p) {
            if (compareDate(p->datum, target)) {
                brisi = 1;
                break;
            }
            p = p->next;
        }
        if (brisi) {
            // Brisanje studenta
            if (prev == NULL) {
                *head = curr->next;
            }
            else {
                prev->next = curr->next;
            }
            Student* tmp = curr;
            curr = curr->next;

            // Oslobaðanje predmeta
            Predmet* pp = tmp->predmeti;
            while (pp) {
                Predmet* tmpP = pp;
                pp = pp->next;
                free(tmpP);
            }
            free(tmp);
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}

Date inputDate() {
    Date d;
    printf("Unesite datum (YYYY MM DD): ");
    scanf("%d %d %d", &d.year, &d.month, &d.day);
    return d;
}

// ---------- MAIN ----------
int main() {
    Student* lista = NULL;

    // 1. Uèitavanje studenata
    loadStudents(&lista, "studenti.txt");

    // 2. Uèitavanje predmeta
    loadPredmeti(lista, "predmet1.txt", "Predmet1");
    loadPredmeti(lista, "predmet2.txt", "Predmet2");

    printf("Pocetna lista:\n");
    printList(lista);

    // 3. Unos datuma i brisanje studenata
    Date target = inputDate();
    removeByDate(&lista, target);

    printf("\nLista nakon brisanja:\n");
    printList(lista);

    // 4. Oslobodi memoriju
    freeList(&lista);
    return 0;
}
