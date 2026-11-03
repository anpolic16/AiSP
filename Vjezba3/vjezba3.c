#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct osoba* Pozicija;
struct osoba {
    char ime[20];
    char prezime[20];
    int godina;
    Pozicija next;
};
int Citaj(const char* imeDat, Pozicija head) {
    FILE* fp = fopen(imeDat, "r");
    if (fp == NULL) {
        printf("Datoteka se ne moze otvoriti!\n");
        return -1;
    }
    struct osoba covjek;
    while (fscanf(fp, "%s %s %d", covjek.ime, covjek.prezime, &covjek.godina) == 3) {
        UnosK(&covjek, head);
    }
    fclose(fp);
    return 0;
}
void UnosP(struct osoba* covjek, Pozicija P) {
    Pozicija novi = (Pozicija)malloc(sizeof(struct osoba));
    if (novi == NULL) {
        printf("\nAlokacija nije uspjela!");
    }
    strcpy(novi->ime, covjek->ime);
    strcpy(novi->prezime, covjek->prezime);
    novi->godina = covjek->godina;
    novi->next = P->next;
    P->next = novi;
}
void Ispis(Pozicija P) {
    printf("\nElementi liste su: ");
    while (P != NULL) {
        printf("%s %s %d,", P->ime, P->prezime, P->godina);
        P = P->next;
    }
}
int UnosK(struct osoba* covjek, Pozicija P) {
    Pozicija novi = (Pozicija)malloc(sizeof(struct osoba));
    if (novi == NULL) {
        printf("\nAlokacija nije uspjela!");
    }
    strcpy(novi->ime, covjek->ime);
    strcpy(novi->prezime, covjek->prezime);
    novi->godina = covjek->godina;
    while (P->next != NULL) {
        P = P->next;
    }
    novi->next = NULL;
    P->next = novi;
    return 0;
}
Pozicija Trazi(Pozicija P, char prezime[]) {
    P = P->next;
    while (P->next != NULL && strcmp(P->prezime, prezime) != 0)
        P = P->next;
    if (P->next == NULL) {
        printf("\nElement nije pronadjen!");
        return NULL;
    }
    else
        printf("\nElement je pronadjen sa %s prezimenom.", P->prezime);
    return P;
}
void Brisi(Pozicija P, char prezime[]) {
    while (P->next != NULL && strcmp(P->next->prezime, prezime) != 0) {
        P = P->next;
    }
    if (P->next == NULL) {
        printf("\nElement nije pronadjen!");
        return;
    }
    Pozicija temp = P->next;
    P->next = temp->next;
    free(temp);
}
int UnosIza(Pozicija P,Pozicija novi, char prezime[]) {
    while (P != NULL && strcmp(P->prezime,prezime) != 0) {
        P = P->next;
    }
    if (P == NULL) {
        printf("Greska!");
        return -1;
    }
    Pozicija nov = (Pozicija)malloc(sizeof(struct osoba));
    strcpy(nov->ime,novi->ime);
    strcpy(nov->prezime, novi->prezime);
    nov->godina = novi->godina;
    nov->next = P->next;
    P->next = nov;
    return 0;
}
int UnosIspred(Pozicija P, Pozicija novi, char prezime[]) {
    while (P->next != NULL && strcmp(P->next->prezime, prezime) != 0) {
        P = P->next;
    }
    if (P->next == NULL) {
        printf("Element s prezimenom %s nije pronadjen!\n", prezime);
        return -1;
    }
    Pozicija nov = (Pozicija)malloc(sizeof(struct osoba));
    strcpy(nov->ime, novi->ime);
    strcpy(nov->prezime, novi->prezime);
    nov->godina = novi->godina;
    nov->next = P->next;
    P->next = nov;

    return 0;
}

void Sort(Pozicija P)
{
    Pozicija j, prev_j, temp, end;
    end = NULL;
    while (P->next != end) {
        prev_j = P;
        j = P->next;
        while (j->next != end) {
            if (strcmp(j->prezime, j->next->prezime) > 0) {
                temp = j->next;
                prev_j->next = temp;
                j->next = temp->next;
                temp->next = j;
                j = temp;
            }
            prev_j = j;
            j = j->next;
        }
        end = j;
    }
}
int UpisiUDatoteku(Pozicija P)
{
    FILE* fp = fopen("datoteka.txt", "w");
    if (fp == NULL) {
        printf("Datoteka nije nadjena!");
        return -1;
    }
    P = P->next;
    while (P != NULL) {
        fprintf(fp, "%s %s %d", P->ime, P->prezime, &P->godina);
        P = P->next;
    }
    fclose(fp);
    return 0;
}
int ProcitajIzDatoteke(Pozicija P)
{
    FILE* fp = fopen("datoteka.txt", "r");
    if (fp == NULL) {
        printf("Datoteke nema!");
        return -1;
    }
    struct osoba covjek;
    while (fscanf(fp, "%49s %49s %d", covjek.ime, covjek.prezime, &covjek.godina) == 3)
        UnosK(&covjek, P);
    fclose(fp);
    return 0;
}
int main()
{
    struct osoba head = { " " };
    struct osoba covjek;
    strcpy(covjek.ime, "Ivan");
    strcpy(covjek.prezime, "Ivic");
    covjek.godina = 2004;
    struct osoba covjek2;
    strcpy(covjek2.ime, "Ante");
    strcpy(covjek2.prezime, "Antic");
    covjek2.godina = 2001;
    struct osoba covjek3;
    strcpy(covjek3.ime, "Niko");
    strcpy(covjek3.prezime, "Nikic");
    covjek3.godina = 2004;
    UnosP(&covjek, &head);
    Ispis(head.next);
    UnosK(&covjek2, &head);
    Ispis(head.next);
    UnosP(&covjek3, &head);
    Trazi(&head, "Evanic");
    Ispis(head.next);
    Brisi(&head, "Ivic");
    Ispis(head.next);
    struct osoba covjek4 = { "Mate","Matic",1999 };
    UnosIza(&head, &covjek4,"Nikic");
    Ispis(head.next);
    struct osoba covjek5 = { "Slobodan","Slobic",1999 };
    UnosIspred(&head, &covjek5, "Nikic");
    Ispis(head.next);
    Sort(&head);
    Ispis(head.next);
    UpisiUDatoteku(&head);
    ProcitajIzDatoteke(&head);

   
    return 0;
}
