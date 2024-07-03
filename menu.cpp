#include <stdio.h>
#include "menu.h"

char menu[9][30] = {
	"1. Dodawanie elementu.",
	"2. Pobieranie elementu.",
	"3. Wyszukiwanie elementu.",
	"4. Drukowanie elementow.",
	"5. Rozmiar struktury.",
	"6. Usuwanie elementow.",
	"7. Zakonczenie programu.",
	"8. Odczyt z pliku binarnego.",
	"9. Zapis do pliku binarnego."
};

void menu_display()
{
	for (int i = 0; i <= bin_output; i++)
		printf("%s\n", menu[i]);
}
