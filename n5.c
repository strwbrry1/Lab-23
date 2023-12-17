#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 80

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>

int getNextDelim(FILE* fp, char token[]);
int getNextWord(FILE* fp, char token[], int maxLen);
int isAlphaRu(unsigned char s);

char filename[] = "text5.txt";
char filenameHTML[] = "out5.html";


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	printf("BEGIN!!!\n");

	char s[MAX_LEN];

	FILE* fin = fopen(filename, "rt");
	if (fin == NULL) {
		printf("Входной файл не найден");
		return;
	}

	FILE* fout = fopen(filenameHTML, "wt");
	if (fout == NULL) {
		printf("Выходной файл не найден");
		return;
	}

	char token[MAX_LEN];
	

	fprintf(fout, "<!DOCTYPE html>");
	fprintf(fout, "<html>");
	fprintf(fout, "<head>");
	fprintf(fout, "<meta http - equiv = \"Content-Type\" content = 	\"text/html; charset=utf-8\" />");
	fprintf(fout, "<title>HTML Document</title>");
	fprintf(fout, "</head>");
	fprintf(fout, "<body>");


	int ch;
	while ((ch = getc(fin)) != EOF) {
		fprintf(fout, "%c", ch);

		if (ch == '\n')
			fprintf(fout, "<br>");

	}

	fprintf(fout, "</body>");
	fprintf(fout, "</html>");

	printf("END!!!");

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

