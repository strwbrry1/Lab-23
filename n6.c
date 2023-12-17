#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 80

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>

int getNextDelim(FILE* fp, char token[]);
int getNextWord(FILE* fp, char token[], int maxLen);
int isAlphaRu(unsigned char s);

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

	FILE* fout = fopen("out6.txt", "wt");
	if (fout == NULL) {
		printf("Выходной файл не найден");
		return;
	}

	while (!feof(fin)) {
		fgets(s, MAX_LEN - 1, fin);
		int len = strlen(s);
		int k = 0;
		char* str2 = malloc(sizeof(char) * (strlen(s) + 3));
		if (s != NULL) {
			for (int i = 0; s[i] != '\0'; i++) {
				if (s[i] == ';') {
					k++;
				}
			}
		}
		strcpy(str2, s);
		str2[len - 1] = ' ';

		fprintf(fout, "%s%d\n\0", str2, k);
		printf(">> %s %d<<\n", str2, k);
		free(str2);
	}

	fclose(fin);
	fclose(fout);

}


int isAlphaRu(unsigned char s) {
	if (isalpha(s))
		return 1;
	//ANSI
	if (s >= 192 && s <= 223)
		return 1;
	if (s >= 224 && s <= 255)
		return 1;
	return 0;
}

int getNextDelim(FILE* fp, char token[])
{
	int ch = getc(fp);
	if (ch == EOF) {
		return 0;
	}
	if (isAlphaRu((unsigned char)ch)) {
		ungetc(ch, fp);
		return 0;
	}
	token[0] = (unsigned char)ch;
	token[1] = '\0';
	return 1;
}

int getNextWord(FILE* fp, char token[], int maxLen)
{
	int i = 0;
	int ch;
	while (((ch = getc(fp)) != EOF) && (i < maxLen - 1)) {
		if (!isAlphaRu((unsigned char)(ch))) {
			break;
		}
		token[i++] = ch;
	}
	ungetc(ch, fp);
	token[i] = '\0';
	if (i == 0) return 0;
	return 1;
}

