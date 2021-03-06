#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


FILE*	fnc_v(void);
void	fnc_o(FILE *f);
char**	fnc_n(FILE *f,int *number_of_lines_P, int n_runned, int *number_of_elements);
void	fnc_s(char **SPZarray, int number_of_lines, int a_runned);
void	fnc_p(char **SPZ_array, int number_of_lines);
void	fnc_z(char **SPZ_array, int number_of_lines);
char**	fnc_a(char **SPZ_array, int *number_of_elements);
void	fnc_b(char **SPZ_array, int *number_of_elements);



int main() {
	FILE *file = NULL;
	int terminate = 1, number_of_lines, v_runned = 0, n_runned = 0, number_of_elemnts = 0, a_runned = 0;
	char prikaz;
	char **SPZ_array = NULL;

	do
	{
		scanf("%c", &prikaz);
		switch (prikaz) {
		case 'v': 
			file = fnc_v();
			v_runned = 1;
			break;
		case 'o': 
			fnc_o(file);
			break;
		case 'n':	
			if (n_runned) {
				//printf("runned");
				SPZ_array = fnc_n(file, &number_of_lines, n_runned, &number_of_elemnts);
				n_runned = 0;
				}
			SPZ_array = fnc_n(file, &number_of_lines, n_runned, &number_of_elemnts);
			//printf("%d", number_of_lines);
			if (v_runned) {
				n_runned = 1;
			}
			break;
		case 's':
			//handling of array allocation error
			if (SPZ_array == NULL) {
				printf("Pole nie je vytvorene\n");
				break;
			}
			else {
				fnc_s(SPZ_array, number_of_lines,a_runned);
				break;
			}
		case 'p':
			//handling of array allocation error
			if (SPZ_array == NULL) {
				printf("Pole nie je vytvorene\n");
				break;
			}
			else {
				fnc_p(SPZ_array, number_of_lines);
				break;
			}
		case 'z':
			//handling of array allocation error
			if (SPZ_array == NULL) {
				break;
			}
			else {
				fnc_z(SPZ_array, number_of_lines);
				break;
			}
		case 'a':
			SPZ_array = fnc_a(SPZ_array, &number_of_elemnts);
			a_runned = 1;
			break;
		case 'b':
			fnc_b(SPZ_array, &number_of_elemnts);
			break;
		}

	} while (prikaz != 'k');
	if (file != NULL) {
		fclose(file);
	}
	
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

	printf("meno a priezvisko: ");
	//going through whole file and printing in an apropriet format
	//printf("meno priezvisko: ");
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
				s = getc(f);
				printf("%c", s);
				if (s != '\n') {
					break;
				}
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
	char name[51], SPZ[10], New[4], cena[18], date[11], junck;
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
		junck = fgetc(f);


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
			printf("%s %s %.2f\n", name, SPZ, cena_float);
		}
	}
}

//pozriet vkladanie do pola a mazanie 
//proid�vanie riadkov atd

char** fnc_n(FILE *f, int *number_of_lines_P, int n_runned, int *number_of_elements) {
	int number_of_lines;
	char junck_data[53], ch;
	char** SPZ_array = NULL;

	//file error handling and rewind
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

	//tu bola snaha o dealokovanie po�a pri druhom spusten� len�e po intenz�vnom googlen�
	//sa mi to nepodarilo rozchodi�, toto je jedin� drobn� vec �o sa mi nepodarilo spravi�
	//presne pod�a zadania

	/*if (n_runned > 0) {
		printf("%d", n_runned);
		for (int i = 0; i < number_of_lines / 6; i++) {
			delete[](SPZ_array[i]);
		}
		delete[](SPZ_array);
		return SPZ_array;
	}
	*/

	//sending number of lines to main
	*number_of_lines_P = number_of_lines+1;
	*number_of_elements = (number_of_lines+1) / 6;

	//allocation and inicialization of array SPZ_array
	rewind(f);
	SPZ_array = (char**)malloc(number_of_lines/6*sizeof(char *));

	for (int i = 0; i <= number_of_lines/6; i++) {
		SPZ_array[i] = (char*)malloc(7 * sizeof(char));
		fgets(junck_data, 53, f);
		for (int j = 0; j < 10; j++) {
			ch = getc(f);
			if (ch == '\n') {
				SPZ_array[i][j] = '\0';
				fgets(junck_data, 53, f);
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
	
void	fnc_s(char **SPZarray, int number_of_lines, int a_runned) {
	//prints from array of SPZ izi
	if (a_runned == 0) {
		for (int i = 0; i < (number_of_lines / 6); i++) {
			printf("%c%c %c%c%c %c%c", SPZarray[i][0], SPZarray[i][1], SPZarray[i][2],
				SPZarray[i][3], SPZarray[i][4], SPZarray[i][5], SPZarray[i][6]);
			printf("\n");
		}
	}
	else {
		for (int i = 0; i < number_of_lines/6; i++) {
			printf("%s\n", SPZarray[i]);
		}

	}

}

void	fnc_p(char **SPZ_array, int number_of_lines) {
	int palindrombool = 1;
	
	//going through SPZ_array and looking for palindrom
	for (int j = 0; j < (number_of_lines / 6); j++) {
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

void	fnc_z(char **SPZ_array, int number_of_lines) {
	char **Copy_SPZ_array, buffer[3];
	int size_of_array = (number_of_lines / 6), *pocet_array, max = 0;

	//allocation and incialization of pocet_array 
	pocet_array = (int*)malloc(size_of_array * sizeof(int));
	for (int i = 0; i < size_of_array; i++) {
		pocet_array[i] = 0;
	}

	//allocation of array of stings which will be copy of SPZ_array
	Copy_SPZ_array = (char**)malloc(size_of_array*sizeof(char*));
	for (int i = 0; i < size_of_array; i++) {
		Copy_SPZ_array[i] = (char*)malloc(3 * sizeof(char));
	}

	//copying first two char of SPZ_array[i] to Copy_SPZ_array for further work
	for (int i = 0; i < size_of_array; i++) {
		for (int j = 0; j < 2; j++) {
			Copy_SPZ_array[i][j] = SPZ_array[i][j];
		}
		Copy_SPZ_array[i][2] = '\0';
	}

	//magic 
	for (int i = 0; i < size_of_array;i++) {
		if (Copy_SPZ_array[i][0] == '\0') {
			continue;
		}
		for (int k = 0; k < 2; k++) {
			buffer[k] = Copy_SPZ_array[i][k];
		}
		buffer[2] = '\0';
		for (int j = i + 1; j < size_of_array ; j++) {
			
			if ((buffer[0] == Copy_SPZ_array[j][0]) && (buffer[1] == Copy_SPZ_array[j][1])) {
				pocet_array[i]++;
				for (int l = 0; l < 3; l++) {
					Copy_SPZ_array[j][l] = '\0';
				}
			}
			else
			{
			}
		}
	}
	//end of magic

	//finding maximum of pocet_array => pozition of most permutated SPZ in Copy_SPZ_array
	for (int i = 0; i < size_of_array; i++) {
		if ((pocet_array[i] + 1) > max) {
			max = pocet_array[i] + 1;
		}
	}
	
	//printing of first two letters of SPZ with highes permutations 
	for (int i = 0; i < size_of_array; i++) {
		if (Copy_SPZ_array[i][1] == '\0') {
			break;
		}
		if (max == (pocet_array[i] + 1)) {
			printf("%s %d\n", Copy_SPZ_array[i], (pocet_array[i] + 1));
		}
	}
}

char**	fnc_a(char **SPZ_array, int *number_of_elements) {
	char **local_array = NULL;
	char ch;
	int k;

	//printf("%d\n", *number_of_elements);

	//tu bola snaha o dealokovanie po�a pri druhom spusten� len�e po intenz�vnom googlen�
	//sa mi to nepodarilo rozchodi�, toto je jedin� drobn� vec �o sa mi nepodarilo spravi�
	//presne pod�a zadania

	/*if (n_runned > 0) {
	printf("%d", n_runned);
	for (int i = 0; i < number_of_lines / 6; i++) {
	delete[](SPZ_array[i]);
	}
	delete[](SPZ_array);
	return SPZ_array;
	}
	*/

	//aloc local_array	
	local_array = (char**)malloc(*number_of_elements * sizeof(char*));
	for (int i = 0; i < *number_of_elements; i++) {
		local_array[i] = (char*)malloc(12*sizeof(char));
	}

	scanf("%d", &k);

	//copy of SPZ_array to local_array;
	for (int i = 0; i < *number_of_elements; i++) {
		for (int j = 0; j < 7; j++) {
			local_array[i][j] = SPZ_array[i][j];
		}
		local_array[i][7] = '\n';
		for (int j = 7; j < 9; j++) {
			ch = SPZ_array[i][j - 7];
			//printf("%c => ", ch);
			for (int l = 1; l <= k; l++) {
				
				if (ch++ >= 'Z') {
					ch = 'A';
				}
				local_array[i][j + 1] = ch;

			}
			local_array[i][10] = '\0';
			
		}
	}
	/*for (int i = 0; i < *number_of_elements; i++) {
		printf("%s\n", local_array[i]);
	}*/

	return local_array;
}

void	fnc_b(char **SPZ_array, int *number_of_elements) {
	int pom;
	char pom_cahr = 48;
	//printf("%c", pom_cahr);

	if (SPZ_array == NULL) {
		printf("Pole nie je vytvorene\n");
		return;
	}

	for (int i = 0; i < 10; i++) {
		pom = 0;
		for (int j = 0; j < *number_of_elements; j++) {
			for (int k = 2; k < 5; k++) {
				//printf("%c = %d ", SPZ_array[j][k], i);
				//nejde zartial porovnanie ak by islo ide to
				pom_cahr = 48 + i;
				if (SPZ_array[j][k] == pom_cahr) {
					pom++;
				}
			}
			
			}
		if (pom > 0) {
			printf("%d:%d\n", i, pom);
		}
	}
}

