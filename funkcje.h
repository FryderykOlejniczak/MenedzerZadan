#ifndef FUNKCJE_H
#define FUNKCJE_H

#define MAX_ZADAN 50
#define MAX_TEKST 100

struct Zadanie {
    int numer;
    char opis[MAX_TEKST];
    int zrobione;
};

extern struct Zadanie zadania[MAX_ZADAN];
extern int ile_zadan;
extern int nastepny_numer;

void pokaz_menu();
void pokaz_liste();
void dodaj_zadanie();
void usun_zadanie();
void zmien_status();
void zapisz_plik();
void wczytaj_plik();
int znajdz_zadanie(int numer);

#endif