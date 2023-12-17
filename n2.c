#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 80

#include <stdio.h>
#include <Windows.h>

char s[MAX_LEN];

int allUp(char c) {
	int res = c;
	if (c >= 'a' && c <= 'z') {
		res = 'A' + (c - 'a');
	}
	if (c >= 'а' && c <= 'п') {
		res = 'А' + (c - 'а');
	}
	if (c >= 'р' && c <= 'я') {
		res = 'Р' + (c - 'Р');
	}
	if (c == 'ё') {
		res = 'Ё';
	}
	return res;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	FILE* fin = fopen("text2.txt", "rt");
	if (fin == NULL) {
		printf("Входной файл не найден");
		return;
	}

	FILE* fout = fopen("out2.txt", "wt");
	if (fout == NULL) {
		printf("Выходной файл не найден");
		return;
	}

	while (!feof(fin)) {
		if (fgets(s, MAX_LEN - 1, fin) != NULL) {
			for (int i = 0; s[i] != '\0'; i++) {
				s[i] = allUp(s[i]);
			}
		}
		fprintf(fout, "%s", s);
		printf(">> %s <<\n", s);
	}
	
	

	fclose(fin);
	fclose(fout);

}
