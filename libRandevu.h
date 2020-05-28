#ifndef libRandevu_H
#define libRandevu_H
#include <stdio.h>
/*
* @file libRandevu.h
* @description Programın fonksiyonlarının prototiplerinin bulundugu dosya.
* @assignment BP3_Odev2
* @date 26.12.2019
* @author Furkan Gundogan - furkangundogan14@outlook.com
*/

//Prototipler
struct kayit;
void printDates();
int getDateCount();
void parcala(char*,char*,char*,char*,char*);
void adAra(char*);
void gunAra(char*);
void randevuSil(char*);
void randevuEkle(char*,char*,char*,char*);
char* sonKarakteriGetir();
extern const char* days[7];
void indexHariciDosyayaYaz(int);
int eklemeKontrol(char*,char*);
void kayitOlustur();
void kayitSil();
#endif
