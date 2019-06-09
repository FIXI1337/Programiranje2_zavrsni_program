#pragma once
#ifndef HEADER_H
#define HEADER_H
int lista(int br);
int unos();
int brojac();
int brisanje(char* searchname);
int brojaccitac();
int brojacplus(int br);
int brojacminus(int br);
int kreiranje();
int pokaz(int n);
int broj();
char prikaz();
typedef struct marka{
	char marka[20];  
	char art[20];    
	int id;        
	int kolicina;   
	int cijena;
} MARKA;

#endif