#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


FILE* fnc_v(void);
void fnc_o(FILE *f);
void fnc_n(FILE *f);


int main() {
	FILE *file = NULL;
	int terminate;
	char prikaz;

	terminate = 1;
	do
	{
		scanf("%c", &prikaz);
		switch (prikaz) {
			case 'v': file = fnc_v();
				break;
			case 'o': fnc_o(file);
				break;
			case 'n': fnc_n(file);
				break;
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
	int pozition_of_name, right_reward = 1, date_int, pozition_to_continue = 0, act_date, New_int;
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

void fnc_n(FILE *f) {
	int number_of_lines;
	char junck_data[53];

	//file and error handling
	if (f == NULL) {
		return;
	}
	rewind(f);

	//counting number of lines
	for (number_of_lines = 0; number_of_lines > -1; number_of_lines++) {
		fgets(junck_data, 53, f);
		if (feof(f)) {
			break;
		}
	}
	printf("number of lines:%d", number_of_lines);

}
	