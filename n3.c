#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 80

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char s[MAX_LEN];

	FILE* fin = fopen("text3.txt", "rt");
	if (fin == NULL) {
		printf("Входной файл не найден");
		return;
	}

	FILE* fout = fopen("out3.txt", "wt");
	if (fout == NULL) {
		printf("Выходной файл не найден");
		return;
	}

	while (!feof(fin)) {
		fgets(s, MAX_LEN - 1, fin);
		int c = 0;
		char* str2 = malloc(sizeof(char) * (strlen(s) + 2));
		if (s != NULL) {
			for (int i = 0; s[i] != '\0'; i++) {
				if (isalpha(s[i])) {
					c++;
					break;
				}
			}
		}
		if (c > 0 && s[strlen(s) - 1] == '\n') {
			strcpy(str2, s);
			str2[strlen(s) - 1] = '#';
			str2[strlen(s)] = '\n';
			str2[strlen(s) + 1] = '\0';

		}
		else if (c > 0 && s[strlen(s) - 1] != '\n') {
			strcpy(str2, s);
			str2[strlen(s)] = '#';
			str2[strlen(s) + 1] = '\0';
		}
		else {
			strcpy(str2, s);
		}
		fprintf(fout, "%s", str2);
		printf(">> %s <<\n", str2);
		free(str2);
	}

	fclose(fin);
	fclose(fout);

}
