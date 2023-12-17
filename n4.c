#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 80

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>

int getNextDelim(FILE* fp, char token[]);
int getNextWord(FILE* fp, char token[], int maxLen);
int isAlphaRu(unsigned char s);

char filename[] = "text3.txt";


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char s[MAX_LEN];

	FILE* fin = fopen(filename, "rt");
	if (fin == NULL) {
		printf("Входной файл не найден");
		return;
	}

	char token[MAX_LEN];
	int res;

	while (!feof(fin)) {
		while (getNextDelim(fin, token)) {
			printf("<DELIM>%s</DELIM>\n", token);
		}
		if (getNextWord(fin, token, MAX_LEN)) {
			printf("<WORD>%s</WORD>\n", token);
		}
	}

	fclose(fin);

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

