#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


FILE*	fnc_v(void);
void	fnc_o(FILE *f);
char**	fnc_n(FILE *f,int *number_of_lines_P);
void	fnc_s(char **SPZarray, int number_of_lines);
void	fnc_p(char **SPZ_array, int number_of_lines);


int main() {
	FILE *file = NULL;
	int terminate = 1, number_of_lines;
	char prikaz;
	char **SPZ_array = NULL;

	do
	{
		scanf("%c", &prikaz);
		switch (prikaz) {
		case 'v': 
			file = fnc_v();
			break;
		case 'o': 
			fnc_o(file);
			break;
		case 'n':
			SPZ_array = fnc_n(file, &number_of_lines);
			break;
		case 's':
			//handling of array allocation error
			if (SPZ_array == NULL) {
				printf("Pole nie je vytvorene\n");
				break;
			}
			else {
				fnc_s(SPZ_array, number_of_lines);
				break;
			}
		case 'p':fnc_p(SPZ_array, number_of_lines);
		}

	} while (prikaz != 'k');

	return 0;
}


FILE* fnc_v(void) {
	FILE *f ;
	char s;
	int line = 1;

	//opening of file and error handling
	f = fopen("predaj.txt", "r");
	if (f == NULL) {
		printf("Neotvoreny subor\n");
		return (NULL);
	}
	rewind(f);

	//going through whole file and printing in an apropriet format
	printf("meno priezvisko: ");
	while (!(feof(f))) {
		
		s = getc(f);
		printf("%c", s);


		if (s == '\n') {
			switch (line)
			{
			case 1: {printf("SPZ: "); }
					break;
			case 2: printf("typ auta: ");
				break;
			case 3: printf("cena: ");
				break;
			case 4: printf("datum: ");
				break;
			case 5:
				line = 0;
				printf("\n");
				printf("meno priezvisko: ");
				break;
			}
			line++;
		
		}	
	}
	printf("\n");

	return(f);
}


void fnc_o(FILE *f) {
	int  right_reward = 1, date_int, pozition_to_continue = 0, act_date, New_int;
	char name[51], SPZ[10], New[4], cena[18], date[11];
	float cena_float;


	/*file check and rewind*/ {
		if (f == NULL) {
			//printf("Neotvoreny subor");
			return;
		}
		rewind(f); }

	scanf("%d", &act_date);		//act date load
	
	//going through whole file and saving data WITHOUT \n !!!!!!
	while (!(feof(f))) {
		//name
		for (int i = 0; i < 52; i++) {
			name[i] = fgetc(f);
			if (name[i] == '\n') {
				name[i] = '\0';
				break;
			}
		}
		//SPZ
		for (int i = 0; i < 10; i++) {
			SPZ[i] = fgetc(f);
			if (SPZ[i] == '\n') {
				SPZ[i] = '\0';
				break;
			}
		}
		//cena
		for (int i = 0; i < 4; i++) {
			New[i] = fgetc(f);
			if (New[i] == '\n') {
				New[i] = '\0';
				break;
			}
		}
		for (int i = 0; i < 18; i++) {
			cena[i] = fgetc(f);
			if (cena[i] == '\n') {
				cena[i] = '\0';
				break;
			}
		}
		//date
		for (int i = 0; i < 11; i++) {
			date[i] = fgetc(f);
			if (date[i] == '\n') {
				date[i] = '\0';
				break;
			}
		}

		//chceck of date and some conversion to go along with them
		sscanf(date, "%d", &date_int);
		if ((act_date - date_int) >= 10000) {
			sscanf(cena, "%f", &cena_float);
			sscanf(New, "%d", &New_int);
			if (New_int) {
				cena_float = (cena_float * 0.015);
			}
			else
			{
				cena_float = (cena_float * 0.022);
			}
			printf("%s %s %.2f\n", name,SPZ,cena_float);
		}
	}
}

char** fnc_n(FILE *f, int *number_of_lines_P) {
	int number_of_lines;
	char junck_data[53], ch;
	char** SPZ_array;

	//file and error handling
	if (f == NULL) {
		return NULL;
	}
	rewind(f);

	//counting number of lines
	for (number_of_lines = 0; number_of_lines > -1; number_of_lines++) {
		fgets(junck_data, 53, f);
		if (feof(f)) {
			break;
		}
	}

	//sending number of lines to main
	*number_of_lines_P = number_of_lines+1;

	//allocation and inicialization of array SPZ_array
	rewind(f);
	SPZ_array = (char**)malloc(number_of_lines/5*sizeof(char *));
	for (int i = 0; i <= number_of_lines/5; i++) {
		SPZ_array[i] = (char*)malloc(7 * sizeof(char));
		fgets(junck_data, 53, f);
		for (int j = 0; j < 10; j++) {
			ch = getc(f);
			if (ch == '\n') {
				SPZ_array[i][j] = '\0';
				break;
			}
			SPZ_array[i][j] = ch;
		}
		for (int j = 0; j < 3; j++) {
			fgets(junck_data, 53, f);
		}

	}
	return SPZ_array;
}
	
void	fnc_s(char **SPZarray, int number_of_lines) {
	//prints from array of SPZ izi
	for (int i = 0; i < (number_of_lines / 5); i++) {
		printf("%c%c %c%c%c %c%c", SPZarray[i][0], SPZarray[i][1], SPZarray[i][2],
			SPZarray[i][3], SPZarray[i][4], SPZarray[i][5], SPZarray[i][6], SPZarray[i][07]);
		printf("\n");
	}
}

void	fnc_p(char **SPZ_array, int number_of_lines) {
	int palindrombool = 1;
	
	//going through SPZ_array and looking for palindrom
	for (int j = 0; j < (number_of_lines / 5); j++) {
		for (int i = 0; i < 3; i++) {
			//palindrom check
			if (SPZ_array[j][i] != SPZ_array[j][6 - i]) {
				palindrombool = 0;
				break;
			}	
			else
			{
				palindrombool = 1;
			}
		}
		//print if SPZ is palindrom
		if (palindrombool == 1) {
			printf("%c%c\n", SPZ_array[j][0], SPZ_array[j][1]);
		}
	}
}