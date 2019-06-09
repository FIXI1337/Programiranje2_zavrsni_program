#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
int kreiranje() {
	MARKA p[100];
	FILE* fp = NULL;
	fp = fopen("FR_CHIP_TUNING.bin", "wb");
	if (fp == NULL) {
		printf("ne postoji");
		return 0;
	}
	else {
		for (int i = 0; i < 1; i++) {
			fprintf(stdout, "Unesite marku vozila:\n");
			fscanf(stdin, "%s", p[i].marka);
			fprintf(stdout, "Unesite ime artikla:\n");
			fscanf(stdin, "%s", p[i].art);
			fprintf(stdout, "Unesite ID artikla:\n");
			fscanf(stdin, "%d", &p[i].id);
			fprintf(stdout, "Unesite kolicinu artikala:\n");
			fscanf(stdin, "%d", &p[i].kolicina);
			fprintf(stdout, "Unesite cijenu:\n");
			fscanf(stdin, "%d", &p[i].cijena);

		}
		fwrite(p, sizeof(MARKA), 1, fp);
	}fclose(fp);

}
int brojaccitac() {
	int br;
	FILE* fp = NULL;
	fp = fopen("count.bin", "rb");
	if (fp == NULL) {
		return 0;
	}
	else {
		fread(&br, sizeof(int), 1, fp);

	}fclose(fp);
	return br;
}
int brojacplus(int br) {
	br++;
	FILE* fp = NULL;
	fp = fopen("count.bin", "wb+");
	if (fp == NULL) {
		return 0;
	}
	else {
		fwrite(&br, sizeof(int), 1, fp);

	}fclose(fp); return br;
}
int brojac() {
	int br = 1;
	FILE* fp = NULL;
	fp = fopen("count.bin", "wb");
	if (fp == NULL) {
		printf("error");
		return 0;
	}
	else {
		fwrite(&br, sizeof(int), 1, fp);

	}fclose(fp);
}
int brojacminus(int br) {
	br--;
	FILE* fp = NULL;
	fp = fopen("count.bin", "wb");
	if (fp == NULL) {
		return 0;
	}
	else {
		fwrite(&br, sizeof(int), 1, fp);

	}fclose(fp); return br;
}
int lista(int br) {
	MARKA p[20];
	FILE* fp = NULL;
	fp = fopen("FR_CHIP_TUNING.bin", "rb");
	if (fp == NULL) {
		perror("Otvaranje");
	}
	else {
		fprintf(stdout, "REDNI BROJ|MARKA|IME ARTIKLA|ID|KOLICINA|CIJENA|\n");
		fread(p, sizeof(MARKA), br, fp);
		for (int i = 0; i < br; i++) {
			if (i == 0) {
				fprintf(stdout, "%d|%s|%s|%d|%d|%d\n", i + 1, p[i].marka, p[i].art, p[i].id,
					p[i].kolicina, p[i].cijena);
			}
			else if (i > 0 && i < br - 1) {
				fprintf(stdout, "%d|%s|%s|%d|%d|%d\n", i + 1, p[i].marka, p[i].art, p[i].id,
					p[i].kolicina, p[i].cijena);
			}
			else {
				fprintf(stdout, "%d|%s|%s|%d|%d|%d\n", i + 1, p[i].marka, p[i].art, p[i].id,
					p[i].kolicina, p[i].cijena);
			}
		}
		fclose(fp);
	}
	return 0;
}
int unos() {
	MARKA p[100];
	FILE* fp = NULL;
	fp = fopen("FR_CHIP_TUNING.bin", "ab+");
	if (fp == NULL) {
		printf("ne postoji\n");
		return 0;
	}
	else {
		for (int i = 0; i < 1; i++) {
			fprintf(stdout, "Unesite marku vozila:\n");
			fscanf(stdin, "%s", p[i].marka);
			fprintf(stdout, "Unesite ime artikla:\n");
			fscanf(stdin, "%s", p[i].art);
			fprintf(stdout, "Unesite ID artikla:\n");
			fscanf(stdin, "%d", &p[i].id);
			fprintf(stdout, "Unesite kolicinu artikla:\n");
			fscanf(stdin, "%d", &p[i].kolicina);
			fprintf(stdout, "Unesite cijenu:\n");
			fscanf(stdin, "%d", &p[i].cijena);

		}
		fwrite(p, sizeof(MARKA), 1, fp);
	}fclose(fp);

}
int brisanje(char* searchname) {
	int ln = 0;
	MARKA psi[20];
	FILE* fp1, * fp2;
	fp1 = fopen("FR_CHIP_TUNING.bin", "rb");
	if (!fp1) {
		return 0;
	}
	fp2 = fopen("frtemp.bin", "wb");
	if (!fp2) {
		fclose(fp1);
		return 0;
	}
	while (fread(&psi, sizeof(MARKA), 1, fp1) != NULL)
	{
		if (strcmp(searchname, psi->marka) == 0) {
			printf("Izbrisano\n");
			ln = 1;
		}
		else { fwrite(&psi, sizeof(MARKA), 1, fp2); }
	}
	if (!ln) { printf("Nema takvog artikla %s\n", searchname); }
	fclose(fp1);
	fclose(fp2);
	remove("FR_CHIP_TUNING.bin");
	rename("frtemp.bin", "FR_CHIP_TUNING.bin");
	return 0;
}
int pokaz(int n) {
	char ime[20];
	int br;
	br = brojaccitac();

	switch (n) {
	case 1:
		printf("LISTA\n");
		lista(br);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
		prikaz();
		n = broj();
		pokaz(n);
		break;
	case 2:
		printf("BRISANJE\n");
		printf("Unesi marku vozila:\n");
		scanf("%s", ime);
		brisanje(ime);
		brojacminus(br);
		br = brojaccitac();
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
		prikaz();
		n = broj();
		pokaz(n);
		break;
	case 3:
		printf("UNOS\n");
		unos();
		brojacplus(br);
		br = brojaccitac();
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
		prikaz();
		n = broj();
		pokaz(n);
		break;
	case 4:
		kreiranje();
		brojac();
		br = brojaccitac();
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
		prikaz();
		n = broj();
		pokaz(n);
		break;
	case 5:
		printf("EXITING...");
		break;
	default:
		printf("Izaberite jedan od 5 navedenih izbora Lista, Brisanje, Unos, Exit.\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
		prikaz();
		n = broj();
		pokaz(n);
		break;
	}
	return 0;
}
int broj() {
	int n;
	printf("Odaberite opciju:\n");
	scanf("%d", &n);
	return n;
}
char prikaz() {
	printf("************************************************************************************************************************\n");
	printf("*------------------------------------------------*___FR_CHIP_TUNING___*------------------------------------------------*\n");
	printf("*------------------------------------------------*   1. LISTA         *------------------------------------------------*\n");
	printf("*------------------------------------------------*   2. BRISANJE      *------------------------------------------------*\n");
	printf("*------------------------------------------------*   3. UNOS          *------------------------------------------------*\n");
	printf("*------------------------------------------------*   4. OBRISI LISTU  *------------------------------------------------*\n");
	printf("*------------------------------------------------*   5. EXIT          *------------------------------------------------*\n");
	printf("************************************************************************************************************************\n");
}
