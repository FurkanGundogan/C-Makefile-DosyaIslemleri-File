#include <stdio.h>
#include"libRandevu.h"
/*
* @file main.c
* @description Programın test edileceği dosya.
* @assignment BP3_Odev2
* @date 26.12.2019
* @author Furkan Gundogan - furkangundogan14@outlook.com
*/
int main()
{
    int selected=0; // menü seçeneği
      // 5 seçilene kadar uygulama çalışır.
       while (selected!=5) {
           if (selected==1) {
                printf("----Randevu Listesi----\n");
                printDates();
             }
           if (selected==2) {
               int selected2=0;
               while (selected2!=3) {
                   if (selected2==1) {
                       char aranan[30];
                       // Girilen isme göre kayit aranacak.
                       printf("Bir Isim Giriniz:");
                       getchar();
                       fgets(aranan,40,stdin);
                       printf("\nSonuclar :\n");
                       adAra(aranan);
                     }
                   if (selected2==2) {
                        // Girilen tarihe göre kayit aranacak.
                        char aranan[30];
                        printf("Bir Tarih Degeri Giriniz(Sayi):");
                        getchar();
                        fgets(aranan,40,stdin);
                        printf("\nSonuclar :\n");
                        gunAra(aranan);
                       }
                   printf("\nArama Sekli Seciniz\n");
                   printf("1.Ada Gore Ara\n");
                   printf("2.Gune Gore Ara\n");
                   printf("3.Geri Don\n");
                   printf("Bir islem seciniz : ");
                   scanf("%d",&selected2);
               }
              printf("Menuye Yonlendirildiniz...");
               }
          if (selected==3) {
                kayitOlustur();

               }
          if (selected==4) {
                kayitSil();
              }
           // Menü
           printf("\nMenu:\n");
           printf("1.Randevulari Goster\n");
           printf("2.Randevu Ara\n");
           printf("3.Randevu Ver\n");
           printf("4.Randevu Sil\n");
           printf("5.Cikis Yap\n");
           printf("Bir Islem Seciniz:");
           scanf("%d",&selected);
       }
        printf("Cikis yaptiniz.");
    return 0;
}
