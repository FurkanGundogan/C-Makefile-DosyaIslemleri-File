#include <stdio.h>
#include<stdlib.h>
#include "libRandevu.h"
#include <ctype.h>
#include<string.h>
/*
* @file libRandevu.c
* @description Headher dosyasındaki fonksiyonların tanımlandıgı dosya.
* @assignment BP3_Odev2
* @date 26.12.2019
* @author Furkan Gundogan - furkangundogan14@outlook.com
*/
const char* days[7] = {"Pazartesi", "Sali","Carsamba","Persembe","Cuma","Cumartesi","Pazar"};
struct kayit{
    char ad[20];
    char soyad[20];
    char tarih[3];
    char saat[3];
};
void printDates(){
    // Dosyayi gezerek kayitlari bastiracak metot.
    int dc=getDateCount();
    int i=1;
    struct kayit k;
    // k : Okunacak metinlerin tutulacagi kayit.
    FILE *f;
    f=fopen("randevular.txt","r");
    // Ad Soyad Saat 10:00 10/12/2019 Persembe
     while (!feof(f)) {
       char line[40];
       fgets(line,40,f);
       parcala(line,k.ad,k.soyad,k.tarih,k.saat);
       if (i==(dc)) {
       //Dosyanın son satırındaki son karakterin dosyadan okunmaması problemini bu şekilde çözdüm.
        char c[]=" ";
        c[0]=sonKarakteriGetir();
        strcat(k.saat,c);
           }
       printf("%d-%s %s \tSaat: %s : 00 \t%s-01-2019 %s \n",i,k.ad,k.soyad,k.saat,k.tarih,days[(atoi(k.tarih)%7)]);
       i++;
     }
    fclose(f);
}
int getDateCount(){
    // Bazi fonksiyonlarda kullanılmak üzere hazırlanmış olan dosyadaki kayit sayisini veren metot.
    int count=0;
    FILE *f;
    f=fopen("randevular.txt","r");
    while (!feof(f)) {
        char c[30];
        char c2[30];
        fscanf(f,"%s%s",c,c2);
        count++;
    }
    fclose(f);
    return count;
}
void parcala(char*line,char*kAd,char*kSoyad,char*kTarih,char*kSaat){
    // Aldigi bilgiyi bosluk ve virgüle göre ayiracak olan split metotdum.
    int i;
    int k=0;
    int v;
    char metin[25];
    for (i=0;i<=strlen(line);i++) {
        if (line[i]==' ') {
            metin[k]='\0';
            strcpy(kAd,metin);
            k=0;
        }
        else if (line[i]==','&&v==0) {
            v++;
            metin[k]='\0';
            strcpy(kSoyad,metin);
            k=0;
        }
        else if (line[i]==','&& v==1) {
            metin[k]='\0';
            strcpy(kTarih,metin);
            k=0;
        }
     else if (i==strlen(line)-1) {
          metin[k]='\0';
          strcpy(kSaat,metin);
          k=0;
   }
       else{
            metin[k]=line[i];
            k++;
        }
    }
}
void adAra(char*isim){
    // Girilen isme göre dosyadaki o isimdeki kaydı yazdıracak metot.
    FILE *f;
    int i=1;
    f=fopen("randevular.txt","r");
     while (!feof(f)) {
         char ad[30];
         char kalan[30];
         fscanf(f,"%s %s",ad,kalan);
         if (*ad==*isim) {
             struct kayit k;
             fseek(f,-(strlen(ad)+strlen(kalan)+1),SEEK_CUR);
             char line[40];
             fgets(line,40,f);
             parcala(line,k.ad,k.soyad,k.tarih,k.saat);
             if (i==(getDateCount())) {
              char c[]=" ";
              c[0]=sonKarakteriGetir();
              strcat(k.saat,c);
                 }
             printf("%d-%s %s \tSaat: %s:00 \t%s-01-2019 %s \n",i,k.ad,k.soyad,k.saat,k.tarih,days[atoi(k.tarih)%7]);
         }
          i++;
     }
     fclose(f);
}
void gunAra(char*gun){
    // Girilen sayiya göre dosyadaki o tarihteki kaydı yazdıracak metot
    FILE *f;
    int i=1;
    f=fopen("randevular.txt","r");
     while (!feof(f)) {
         struct kayit k;
         char line[40];
         fgets(line,40,f);
         parcala(line,k.ad,k.soyad,k.tarih,k.saat);
         if (i==(getDateCount())) {
          char c[]=" ";
          c[0]=sonKarakteriGetir();
          strcat(k.saat,c);
             }
         if (*k.tarih==*gun) {
             printf("%d-%s %s \tSaat: %s:00 \t%s-01-2019 %s \n",i,k.ad,k.soyad,k.saat,k.tarih,days[atoi(k.tarih)%7]);
         }
          i++;
     }
     fclose(f);
}
void randevuEkle(char* ad,char* soyad ,char* saat,char*tarih){
    // Girilecek kisi bilgilerine göre dosya sonuna yeni kaydı ekleyen metot.
    int c;
    c=eklemeKontrol(tarih,saat);
    if (c==0) {
      printf("Musait degil tekrar deneyiniz %s Ocak Saat : %s:00 \n",tarih,saat);
    } else {
        int k=0;
        int dc=getDateCount();
        FILE *f;
        FILE *f2;
        f=fopen("randevular.txt","r");
         char line[dc+1][40];
          while (!feof(f)) {
              fgets(line[k],40,f);
              k++;
        }
          strcpy(line[k],ad);
          strcat(line[k]," ");
          strcat(line[k],soyad);
          strcat(line[k],",");
          strcat(line[k],tarih);
          strcat(line[k],",");
          strcat(line[k],saat);
          fclose(f);
           f2=fopen("randevular.txt","a");
           fputs("\n",f);
           fputs(line[k],f);
          printf("\n Kayit Basarili\n");
          fclose(f2);
    }

}
char* sonKarakteriGetir(){
    // Oluşan bir problemi gidermek için yazılan,son kaydın son harfini getiren metot.
    FILE *f;
     f=fopen("randevular.txt","r");
     fseek(f,-1,SEEK_END);
     char c=fgetc(f);
     fclose(f);
     return c;
}
void randevuSil(char* aranan){
    //Girilen ad ve soyada göre dosyada o bilgileri arayıp buldugu kaydı silme fonksiyonuna gönderen metot
int silmeKontrol=0;
int silSatir;
    FILE *f;
    f=fopen("randevular.txt","r");
    int i=0;
    int k=0;
    int t;
    int boy=getDateCount();
    while (!feof(f)) {
        char okunan[30];
        char c;
        c=fgetc(f);
        if (c==',') {
            k++;
            okunan[i]='\0';
            if (!strcmp(aranan,okunan)) {
                i=0;
                silmeKontrol=1;
                silSatir=k-1;
                break;
            }else{
                char bos[50];
                fseek(f,-i,SEEK_CUR);
                fgets(bos,50,f);
                if (t==boy-1) {
                 strcat(bos,".");
                }
                i=0;
                t++;
            }
        }
        else {
            okunan[i]=c;
            i++;
        }
}
    fclose(f);
    if (silmeKontrol) {
        // silmeKontrol durumuna göre silme kodunu çağıran metot.
        indexHariciDosyayaYaz(silSatir);
        printf("\n Kayit Silme Basarili\n");
    } else {
         printf("\n silme Yapilmadi");
    }
}

void indexHariciDosyayaYaz(int x){
           // x Degerine gore dosyadaki kaydi silecek metot.
           int k=0;
           int dc=getDateCount();
           if(x==dc-1){
               printf("\n!! Uyari : Listedeki Son Kayit !!\n");
           }else{
           FILE *f;
           f=fopen("randevular.txt","r");
            char line[dc][40];
             while (!feof(f)) {
                 fgets(line[k],40,f);
                 k++;
           }
             k--;
             fclose(f);
             f=fopen("randevular.txt","w");
             for (int i=0;i<dc;i++) {

                 if (i==x) {
                 } else {
                     if(i==dc-1) {
                         char son[]=" ";
                         son[0]=sonKarakteriGetir();
                         strcat(line[i],son);
                     }
                    fwrite(line[i],strlen(line[i])-1,1,f);
                    if(i!=dc-1)fputs("\n",f);
                 }
             }
             fclose(f);
}
}
int eklemeKontrol(char* tarih,char* saat){
    //Gönderilen tarih ve saati kontrol eden method bool gibi çalışır.
    int kontrol=1;
    FILE *f;
    int i=1;
    f=fopen("randevular.txt","r");
    while (!feof(f)) {
        struct kayit k;
        char line[40];
        fgets(line,40,f);
        parcala(line,k.ad,k.soyad,k.tarih,k.saat);
        if (i==(getDateCount())) { // son karakter problemi çözümü
         char c[]=" ";
         c[0]=sonKarakteriGetir();
         strcat(k.saat,c);
            }
        if ((strcmp(k.tarih,tarih) || strcmp(k.saat,saat))) {
            // Aynı saat ve tarih kontrol
        }
        else{
            kontrol=0;
            break;
        }
        i++;
    }
    fclose(f);
    return kontrol;
}
void kayitOlustur(){
    // Kullanıcıdan kontrollü bilgiler alıp randevuEkle'yi çağıran metot.
    struct kayit k;
    int control=0;
    while (control!=1) {
        printf("Ad:");
        scanf("%s",k.ad);
        int i;
        for (i=0;i<strlen(k.ad);i++) {
            if(k.ad[i]==' '|| isdigit(k.ad[i]) || ispunct(k.ad[i]))
            {
                control =0; break;
            }
            else{control=1;}
        }
    }

        control=0;
        while (control!=1) {
            printf("Soyad:");
            scanf("%s",k.soyad);
            int i;
            for (i=0;i<strlen(k.soyad);i++) {
                if(k.soyad[i]==' '|| isdigit(k.soyad[i]) || ispunct(k.soyad[i]))
                {
                    control =0; break;
                }
                else{control=1;}
            }
        }


        control=0;
        while (control!=1) {
            printf("Saat:");
            scanf("%s",k.saat);
            int i;
            for (i=0;i<strlen(k.saat);i++) {
                if(k.saat[i]==' '|| isalpha(k.saat[i]) || ispunct(k.saat[i])||atoi(k.saat)>23||atoi(k.saat)<0)
                {
                    control =0; break;
                }
                else{control=1;}
            }
        }

        control=0;
        while (control!=1) {
            printf("Tarih(Sayi):");
            scanf("%s",k.tarih);
            int i;
            for (i=0;i<strlen(k.tarih);i++) {
                if(k.tarih[i]==' '|| isalpha(k.tarih[i]) || ispunct(k.tarih[i])||atoi(k.tarih)>31||atoi(k.tarih)<0)
                {
                    control =0; break;
                }
                else{control=1;}
            }
        }
     randevuEkle(k.ad,k.soyad,k.saat,k.tarih);
}
void kayitSil(){
    // Kullanıcıdan kontrollü Ad Soyad bilgisi alıp RandevuSil'i çağıran metot.
    struct kayit k;
    int control=0;
    while (control!=1) {
        printf("Silinecek Kisinin Adi:");
        scanf("%s",k.ad);
        int i;
        for (i=0;i<strlen(k.ad);i++) {
            if(k.ad[i]==' '|| isdigit(k.ad[i]) || ispunct(k.ad[i]))
            {
                control =0; break;
            }
            else{control=1;}
        }
    }
        control=0;
        while (control!=1) {
            printf("Silinecek Kisinin Soyadi:");
            scanf("%s",k.soyad);
            int i;
            for (i=0;i<strlen(k.soyad);i++) {
                if(k.soyad[i]==' '|| isdigit(k.soyad[i]) || ispunct(k.soyad[i]))
                {
                    control =0; break;
                }
                else{control=1;}
            }
        }
        char aranan[50];
        int o=0;
        int p=0;
        for (o=0;o<strlen(k.ad);o++) {
            aranan[o]=k.ad[o];
            p++;
        }
         char bosluk[1]=" ";
         strcat(aranan,bosluk);
         o++;
        int t;
        for (t=0;t<strlen(k.soyad);t++) {
            aranan[o]=k.soyad[t];
            o++;
        }
        aranan[o]='\0';
        randevuSil(aranan);
}
