#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void error(int e)
{
	switch (e)
	{
	case 1:
	{
		printf("Brak studentow do pobrania w bazie.\n");
		break;
	}
	case 2:
	{
		printf("Wcisnij ENTER, aby zamknac program\n");
		getchar();
		exit(2);
	}
	case 3:
	{
		printf("Blad alokacji pamieci. Koncze dzialanie programu...\n");
		printf("Wcisnij ENTER, aby zamknac program\n");
		getchar();
		exit(3);
	}
	case 4:
	{
		printf("Wczytano znak zamiast liczby. Koncze dzialanie programu...\n");
		printf("Wcisnij ENTER, aby zamknac program\n");
		getchar();
		exit(4);
	}
	case 5:
	{
		printf("Nie udalo sie otworzyc pliku.\n");
		break;
	}
	case 6:
	{
		printf("Blad zapisu do pliku.\n");
		break;
	}
	}
}