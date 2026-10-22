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
    return 0;
}
