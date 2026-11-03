#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct Polinom* Pozicija;
struct Polinom {
    int baza;
    int eksponent;
    Pozicija next;
};
Pozicija dodaj(Pozicija P, int baza, int eksponent) {
    if (baza == 0)
        return P;
    if (P == NULL || P->eksponent < eksponent) {
        Pozicija novi = (Pozicija)malloc(sizeof(struct Polinom));
        novi->baza = baza;
        novi->eksponent = eksponent;
        novi->next = P;
        return novi;
    }
    
    if (P->eksponent == eksponent) {
        P->baza += baza;
        if (P->baza == 0) {
            Pozicija temp = P;
            P = P->next;
            free(temp);
        }
        return P;
    }
    Pozicija trenutni = P;
    while (trenutni->next != NULL && trenutni->next->eksponent > eksponent) {
        trenutni = trenutni->next;
    }

    if (trenutni->next != NULL && trenutni->next->eksponent == eksponent) {
        trenutni->next->baza += baza;
        if (trenutni->next->baza == 0) {
            Pozicija temp = trenutni->next;
            trenutni->next = trenutni->next->next;
            free(temp);
        }
    } else {
        Pozicija novi = (Pozicija)malloc(sizeof(struct Polinom));
        novi->baza = baza;
        novi->eksponent = eksponent;
        novi->next = trenutni->next;
        trenutni->next = novi;
    }
    return P;
}
Pozicija ucitaj(const char* imeDatoteke) {
    FILE* f = fopen(imeDatoteke, "r");
    if (f == NULL) {
        printf("Greska kod otvaranja datoteke!\n");
        return NULL;
    }
    Pozicija P = NULL;
    int baza, eksponent;
    while (fscanf(f, "%d %d", &baza, &eksponent) == 2) {
        P = dodaj(P, baza, eksponent);
    }
    fclose(f);
    return P;
}
Pozicija zbrojiPol(Pozicija p1, Pozicija p2) {
    Pozicija rezultat = NULL;
    
    Pozicija temp = p1;
    while (temp != NULL) {
        rezultat = dodaj(rezultat, temp->baza, temp->eksponent);
        temp = temp->next;
    }

    temp = p2;
    while (temp != NULL) {
        rezultat = dodaj(rezultat, temp->baza, temp->eksponent);
        temp = temp->next;
    }
    return rezultat;
}
Pozicija mnoziPol(Pozicija p1, Pozicija p2) {
    Pozicija rezultat = NULL;
    Pozicija i = p1;
    
    while (i != NULL) {
        Pozicija j = p2;
        while (j != NULL) {
            int novaBaza = i->baza * j->baza;
            int noviEks = i->eksponent + j->eksponent;
            rezultat = dodaj(rezultat, novaBaza, noviEks);
            j = j->next;
        }
        i = i->next;
    }
    return rezultat;
}
void ispis(Pozicija P) {
    if (P == NULL) {
        printf("0\n");
        return;
    }
    Pozicija temp = P;
    while (temp != NULL) {
        printf("%dx^%d", temp->baza, temp->eksponent);
        if (temp->next != NULL)
            printf(" + ");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Pozicija p1 = ucitaj("Polinom1.txt");
    Pozicija p2 = ucitaj("Polinom2.txt");

    printf("Prvi polinom: ");
    ispis(p1);
    printf("Drugi polinom: ");
    ispis(p2);

    Pozicija zbroj = zbrojiPol(p1, p2);
    printf("Zbroj je: ");
    ispis(zbroj);

    Pozicija umnozak = mnoziPol(p1, p2);
    printf("Umnozak je: ");
    ispis(umnozak);

    return 0;
}
