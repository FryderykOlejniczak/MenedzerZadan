#include <stdio.h>
#include "funkcje.h"
int main() {
    int wybor;

    printf("MENEDZER ZADAN\n");

    wczytaj_plik();

    while (1) {
        pokaz_menu();
        scanf("%d", &wybor);

        if (wybor == 1) {
            pokaz_liste();
        }
        else if (wybor == 2) {
            dodaj_zadanie();
        }
        else if (wybor == 3) {
            usun_zadanie();
        }
        else if (wybor == 4) {
            zmien_status();
        }
        else if (wybor == 5) {
            printf("Koniec programu!\n");
            break;
        }
        else {
            printf("Zly numer! Wybierz 1-5.\n");
        }
    }

    return 0;
}