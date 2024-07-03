#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#include "options.h"
#include "menu.h"
extern void error(int n);
struct student *students = NULL;
int size = 0;

void get_option()
{
	while (true)
	{
		printf("\n");
		menu_display();
		printf("Wybierz jedna z dostepnych opcji : \n");
		if(scanf("%d", &c)!=1)
			error(4);
		getchar();
		switch (c-1)
		{
		case add_stack_element: add();
			break;
		case get_stack_element: get();
			break;
		case find_particular_element: find();
			break;
		case print_stack_elements: print();
			break;
		case check_sizeof_stack: check();
			break;
		case delete_stack: erase();
			break;
		case exit_program: my_exit();
			break;
		case bin_input: bin_in();
			break;
		case bin_output: bin_out();
			break;
		default:
			printf("Podano bledna opcje.\n");
		};
	}
}

void add()
{
	if (students == NULL)
		students = (struct student*)malloc(sizeof(struct student));
	else
		students = (struct student*)realloc(students, (size + 1)*sizeof(struct student));
	if (students == NULL)
		error(3);
	printf("Podaj imie : \n");
	fgets(students[size].name, sizeof(students[size].name), stdin);
	strtok(students[size].name, "\n");
	printf("Podaj nazwisko : \n");
	fgets(students[size].surname, sizeof(students[size].surname), stdin);
	strtok(students[size].surname, "\n");
	printf("Podaj rok urodzenia : \n");
	if(scanf("%d", &students[size].born)!=1)
		error(4);
	size++;
	printf("Dodano element : %s %s %d\n", students[size-1].name, students[size-1].surname, students[size-1].born);
}
void get()
{
	if (size == 0)
	{
		error(1);
		return;
	}
	printf("Pobrano element : %s %s %d\n", students[size-1].name, students[size-1].surname, students[size-1].born);
	struct student* students2 = (struct student*)malloc((size - 1) * sizeof(struct student));
	if (students2 == NULL)
		error(3);

	for (int i = 0; i < size-1; i++)
		students2[i] = students[i];
	size--;
	free(students);
	students = students2;
}
int cmp(void* i, void* s, int dataType)
{
	if (dataType == 1)
	{
		char* ii = (char*)i;
		char* ss = (char*)s;
		return strcmp(ii, ss) == 0;
	}
	else
	{
		int ii = *(int*)i;
		int ss = *(int*)s;
		return ii == ss;
	}
}
void find()
{
	int c, ile=0, *ind= (int*)malloc(size * sizeof(int));
	printf("1. Wyszukaj po imieniu.\n2. Wyszukaj po nazwisku.\n3. Wyszukaj po roku urodzenia.\n");
	printf("Wybierz opcje : \n");
	if (scanf("%d", &c) != 1)
		error(4);
	getchar();

	switch (c)
	{
		case 1:
		{
			char name[30];
			printf("Podaj imie : \n");
			fgets(name, sizeof(name), stdin);
			strtok(name, "\n");
			for (int i = 0; i < size; i++)
				if (cmp(name, students[i].name, 1))
				{
					ind[ile] = i;
					ile++;
				}	
			if (!ile)
			{
				printf("Brak studentow o imieniu %s.\n", name);
				break;
			}
			else
			{
				printf("Studenci o imieniu %s : \n", name);
				for (int i = 0; i < ile; i++)
					printf("%s %s %d \n", students[ind[i]].name, students[ind[i]].surname, students[ind[i]].born);
			}
			break;
		}
		case 2:
		{
			char surname[30];
			printf("Podaj nazwisko : \n");
			fgets(surname, sizeof(surname), stdin);
			strtok(surname, "\n");
			for(int i = 0; i<size; i++)
				if (cmp(surname, students[i].surname, 1))
				{
					ind[ile] = i;
					ile++;
				}
			if (!ile)
			{
				printf("Brak studentow o nazwisku %s.\n", surname);
				break;
			}
			else
			{
				printf("Studenci o nazwisku %s : \n", surname);
				for (int i = 0; i < ile; i++)
					printf("%s %s %d \n", students[ind[i]].name, students[ind[i]].surname, students[ind[i]].born);
			}
			break;
		}
		case 3:
		{
			int year;
			printf("Podaj rok : \n");
			if (scanf("%d", &year) != 1)
				error(4);
			for(int i =0; i<size; i++)
				if (cmp(&year, &students[i].born, 2))
				{
					ind[ile] = i;
					ile++;
				}
			if (!ile)
			{
				printf("Brak studentow urodzonych w %d roku.\n", year);
				break;
			}
			else
			{
				printf("Studenci urodzeni w %d roku : \n", year);
				for (int i = 0; i < ile; i++)
					printf("%s %s %d \n", students[ind[i]].name, students[ind[i]].surname, students[ind[i]].born);
			}
			break;
		}
		default:
			printf("Podano bledna opcje.\n");
		free(ind);
	}
}
void print()
{
	if (students != NULL)
	{
		printf("Aktualna zawartosc stosu : \n");
		for (int i = size-1; i >=0; i--)
			printf("%s %s %d \n", students[i].name, students[i].surname, students[i].born);
	}
	else
		printf("Brak studentow w bazie.\n");
}
void check()
{
	printf("Rozmiar stosu = %d\n", size);
}
void erase()
{
	free(students);
	size = 0;
	students = NULL;
	printf("Usunieto dane ze stosu.\n");
}
void my_exit()
{
	printf("Dziekuje za korzystanie z programu. Koncze dzialanie...\n");
	error(2);
}
void bin_in()
{
	FILE* file = fopen("dane.txt", "rb");
	//FILE* file = fopen("dane.bin", "rb");
	//FILE* file = fopen("kolejka.txt", "rb");
	if (file == NULL)
		error(5);
	if (students == NULL)
		students = (struct student*)malloc(sizeof(struct student));  
	else
		students = (struct student*)realloc(students, (size + 1) * sizeof(struct student));
	while (fscanf(file, "%s %s %d", students[size].name, students[size].surname, &students[size].born) == 3)
	{
		size++;
		students = (struct student*)realloc(students, (size + 1) * sizeof(struct student));
	}
	printf("Dane zostaly wczytane poprawnie.\n");
	fclose(file);
}
void bin_out()
{
	FILE* file = fopen("stos.bin", "wb");
	if (file == NULL)
		error(5);
	if (fwrite(&size, sizeof(int), 1, file) != 1)
		error(6);
	if (fwrite(students, sizeof(struct student), size, file) != size)
		error(6);
	printf("Dane zostaly zapisane poprawnie.\n");
	fclose(file);

}


