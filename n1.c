#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 80

#include <stdio.h>
#include <Windows.h>

char s[MAX_LEN];

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	FILE* fin = fopen("text1.txt", "rt");
	if (fin == NULL) {
		printf("Входной файл не найден");
		return;
	}

	FILE* fout = fopen("out1.txt", "wt");
	if (fout == NULL) {
		printf("Выходной файл не найден");
		return;
	}

	while (!feof(fin)) {
		if (fgets(s, MAX_LEN - 1, fin) != NULL) {
			for (int i = 0; s[i] != '\0'; i++) {
				if (s[i] == '\t') {
					s[i] = '%';
				}
			}
		}
		fprintf(fout, "%s", s);
		printf(">> %s <<\n", s);
	}
	
	

	fclose(fin);
	fclose(fout);

}
