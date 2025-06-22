#include "funkcje.h"
#include <string.h>
#include <stdio.h>
struct Zadanie zadania[MAX_ZADAN];
int ile_zadan = 0;
int nastepny_numer = 1;

void pokaz_menu() {
    printf("\n--- MENEDZER ZADAN ---\n");
    printf("1. Pokaz liste zadan\n");
    printf("2. Dodaj zadanie\n");
    printf("3. Usun zadanie\n");
    printf("4. Zmien status zadania\n");
    printf("5. Wyjscie\n");
    printf("Twoj wybor: ");
}

void pokaz_liste() {
    printf("\n--- LISTA ZADAN ---\n");

    if (ile_zadan == 0) {
        printf("Brak zadan!\n");
        return;
    }

    for (int i = 0; i < ile_zadan; i++) {
        printf("%d. %s [%s]\n",
               zadania[i].numer,
               zadania[i].opis,
               zadania[i].zrobione ? "ZROBIONE" : "NIE ZROBIONE");
    }
}

void dodaj_zadanie() {
    if (ile_zadan >= MAX_ZADAN) {
        printf("Za duzo zadan!\n");
        return;
    }

    printf("Wpisz zadanie: ");
    getchar();
    fgets(zadania[ile_zadan].opis, MAX_TEKST, stdin);

    int len = strlen(zadania[ile_zadan].opis);
    if (zadania[ile_zadan].opis[len-1] == '\n') {
        zadania[ile_zadan].opis[len-1] = '\0';
    }

    zadania[ile_zadan].numer = nastepny_numer;
    zadania[ile_zadan].zrobione = 0;

    ile_zadan++;
    nastepny_numer++;

    printf("Zadanie dodane!\n");
    zapisz_plik();
}
int znajdz_zadanie(int numer) {
    for (int i = 0; i < ile_zadan; i++) {
        if (zadania[i].numer == numer) {
            return i;
        }
    }
    return -1;
}

void usun_zadanie() {
    if (ile_zadan == 0) {
        printf("Brak zadan do usuniecia!\n");
        return;
    }

    int numer;
    printf("Podaj numer zadania do usuniecia: ");
    scanf("%d", &numer);

    int pozycja = znajdz_zadanie(numer);

    if (pozycja == -1) {
        printf("Nie ma takiego zadania!\n");
        return;
    }

    struct Zadanie *wsk_zadania = zadania;

    for (int i = pozycja; i < ile_zadan - 1; i++) {
        *(wsk_zadania + i) = *(wsk_zadania + i + 1);
    }

    ile_zadan--;
    printf("Zadanie usuniete!\n");
    zapisz_plik();
}
void zmien_status() {
    if (ile_zadan == 0) {
        printf("Brak zadan!\n");
        return;
    }

    int numer;
    printf("Podaj numer zadania: ");
    scanf("%d", &numer);

    int pozycja = znajdz_zadanie(numer);

    if (pozycja == -1) {
        printf("Nie ma takiego zadania!\n");
        return;
    }

    struct Zadanie *wsk_zadanie = &zadania[pozycja];

    char wybor;
    printf("Obecny status: %s\n", wsk_zadanie->zrobione ? "ZROBIONE" : "NIE ZROBIONE");
    printf("Status (z-zrobione, n-nie zrobione): ");
    scanf(" %c", &wybor);

    if (wybor == 'z') {
        wsk_zadanie->zrobione = 1; // -> to jak . ale dla wskaznikow
        printf("Zadanie oznaczone jako zrobione!\n");
    } else if (wybor == 'n') {
        wsk_zadanie->zrobione = 0;
        printf("Zadanie oznaczone jako nie zrobione!\n");
    } else {
        printf("Zly wybor!\n");
        return;
    }

    zapisz_plik();
}

void zapisz_plik() {
    FILE *plik = fopen("zadania.txt", "w");
    if (plik == NULL) {
        printf("Nie mozna zapisac pliku!\n");
        return;
    }

    fprintf(plik, "%d %d\n", ile_zadan, nastepny_numer);

    for (int i = 0; i < ile_zadan; i++) {
        fprintf(plik, "%d %d %s\n",
                zadania[i].numer,
                zadania[i].zrobione,
                zadania[i].opis);
    }

    fclose(plik);
}
void wczytaj_plik() {
    FILE *plik = fopen("zadania.txt", "r");
    if (plik == NULL) {
        printf("Brak zapisanego pliku - zaczynamy od nowa.\n");
        return;
    }

    fscanf(plik, "%d %d", &ile_zadan, &nastepny_numer);

    for (int i = 0; i < ile_zadan; i++) {
        fscanf(plik, "%d %d ", &zadania[i].numer, &zadania[i].zrobione);
        fgets(zadania[i].opis, MAX_TEKST, plik);

        int len = strlen(zadania[i].opis);
        if (zadania[i].opis[len-1] == '\n') {
            zadania[i].opis[len-1] = '\0';
        }
    }

    fclose(plik);
    printf("Wczytano %d zadan.\n", ile_zadan);
}