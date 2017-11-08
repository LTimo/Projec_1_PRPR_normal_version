#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


FILE* fnc_v(void);
void fnc_o(FILE *f);

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
		}

	} while (prikaz != 'k');

	return 0;
}


FILE* fnc_v(void) {
	FILE *f ;
	char s;
	int line = 1;

	f = fopen("predaj.txt", "r");
	if (f == NULL) {
		printf("Neotvoreny subor\n");
		return (NULL);
	}
	printf("meno priezvisko: ");


	// skrajsit kod !!!!!
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
	int act_date;
	char ch;
	char uselessdata[50], reward[9];
	int pozition_of_name, right_reward = 1, date;


	/*file check and rewind*/ {
		if (f == NULL) {
			printf("Neotvoreny subor");
			return;
		}
		rewind(f); }

	scanf("%d", &act_date);


	while (!(feof(f))) {

		pozition_of_name = ftell(f);

		//going through uselessdata
		for (int i = 0; i < 4; i++) {
			fgets(uselessdata, 50, f);
		}

		//get date
		fgets(uselessdata, 50, f);
		right_reward = 0;

		sscanf(uselessdata, "%d", &date);
		//printf("%d\n", date);

		//printf("%d\n", (date -act_date));
		if ((act_date - date) >= 10000) {
			fseek(f, pozition_of_name, SEEK_SET);
			fgets(uselessdata, 50, f);
			printf("%s", uselessdata);
			printf("\n");
		}
	}
}
	