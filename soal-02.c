/** EL2208 Praktikum Pemecahan Masalah dengan C 2020/2021
*   Modul               : 4
*   Soal                : 1
*   Hari dan Tanggal    : Sabtu, 13 Maret 2021
*   Nama (NIM)          : Adeline Kartika (13218081)
*   Nama File           : M4.c
*   Deskripsi           : Program pengolahan data barang toko pakaian
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char jenis[20];
    char nama[20];
    int stok;
    int harga;
    int diskon;
} Barang;

void inputBarang(Barang *toko, int *sumBarang){
    char filename[20];
    char temp[100];
    int jumlahBarang;
    int i;

    printf("Masukkan file toko : ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    fgets(temp,sizeof(temp),fp);
    sscanf(temp, "%d", &jumlahBarang); // ambil data jumlah barang

    *sumBarang = jumlahBarang;
    
    // array dinamis
    toko = realloc(toko,(jumlahBarang)*sizeof(Barang));
    
    // masukkan data ke dalam array dinamis
    for(i=0; i<jumlahBarang; i++){
        fgets(temp,sizeof(temp),fp);
        strcpy((toko+i)->jenis,temp);
        fgets(temp,sizeof(temp),fp);
        strcpy((toko+i)->nama,temp);
        fgets(temp,sizeof(temp),fp);
        sscanf(temp,"%d", &(toko+i)->stok);
        fgets(temp,sizeof(temp),fp);
        sscanf(temp,"%d", &(toko+i)->harga);
    }

    fclose(fp);

    return;
}

void hitungDiskon(Barang *toko, int jumlahBarang){
    int i;

    // menghitung diskon sesuai ketentuan persediaan setiap barang
    for(i = 0; i < jumlahBarang; i++){
        if(strstr(toko[i].jenis,"Baju") != 0){
            if(toko[i].stok > 150){
                toko[i].diskon = 35;
            } else{
                toko[i].diskon = 0;
            }
        } else if(strstr(toko[i].jenis,"Celana") != 0){
            if(toko[i].stok > 100){
                toko[i].diskon = 50;
            } else{
                toko[i].diskon = 0;
            }
        } else if(strstr(toko[i].jenis,"Aksesoris") != 0){
            if(toko[i].stok > 50){
                toko[i].diskon = 10;
            } else{
                toko[i].diskon = 0;
            }
        } else if(strstr(toko[i].jenis,"Sepatu") != 0){
            if(toko[i].stok > 120){
                toko[i].diskon = 70;
            } else{
                toko[i].diskon = 0;
            }
        }
    }

    return;
}

void hargaDiskonTerendah(Barang *toko, int jumlahBarang, int *hargaTerendah){
    int i;
    int temp;
    int nomor;

    // menghitung harga barang sesuai diskon barang
    for(i = 0; i < jumlahBarang; i++){
        toko[i].harga = (100-toko[i].diskon)*0.01*toko[i].harga;
    }

    temp = toko[0].harga;

    // mencari harga barang termurah sebuah toko
    for(i = 1; i < jumlahBarang; i++){
        if(toko[i].harga < temp){
            temp = toko[i].harga;
            nomor = i;
        }
    }

    // mengembalikan indeks barang dengan harga termurah
    *hargaTerendah = toko[nomor].harga;

    return;
}

void cekStock(Barang *toko, int jumlahBarang){
    int i;
    int cek = 0;

    // mengecek stok barang
    for(i = 0; i < jumlahBarang; i++){
        if(strstr(toko[i].jenis,"Baju") != 0){
            if(toko[i].stok < 75){
                cek++;
                printf("\nButuh restock: %s", toko[i].nama); 
                printf("Setidaknya pesan %d barang lagi untuk mencapai batas persediaan minimal!\n", (150-toko[i].stok));
            }
        } else if(strstr(toko[i].jenis,"Celana") != 0){
            if(toko[i].stok < 50){
                cek++;
                printf("\nButuh restock: %s", toko[i].nama); 
                printf("Setidaknya pesan %d barang lagi untuk mencapai batas persediaan minimal!\n", (100-toko[i].stok));
            }
        } else if(strstr(toko[i].jenis,"Aksesoris") != 0){
            if(toko[i].stok < 25){
                cek++;
                printf("\nButuh restock: %s", toko[i].nama); 
                printf("Setidaknya pesan %d barang lagi untuk mencapai batas persediaan minimal!\n", (50-toko[i].stok));
            }
        } else if(strstr(toko[i].jenis,"Sepatu") != 0){
            if(toko[i].stok < 60){
                cek++;
                printf("\nButuh restock: %s", toko[i].nama); 
                printf("Setidaknya pesan %d barang lagi untuk mencapai batas persediaan minimal!\n", (175-toko[i].stok));
            }
        }
    }

    if (cek == 0){
        printf("Semua persediaan barang masih banyak! Tidak perlu restock!\n");
    }

    return;
}

int main(){
    Barang *toko;
    int jumlahBarang;
    int hargaTerendah;
    int i;

    toko = (Barang*)calloc(1,sizeof(Barang));

    inputBarang(toko, &jumlahBarang);


    hitungDiskon(toko, jumlahBarang);

    // menghitung harga barang termurah setelah di diskon
    hargaDiskonTerendah(toko, jumlahBarang, &hargaTerendah);

    printf("\nPengecekan Persedian...\n");
    cekStock(toko, jumlahBarang); // cek stock barang
    
    // print semua barang dengan harga termurah
    printf("\nHarga Barang Termurah: \n");
    for(i=0;i<jumlahBarang;i++){
        if(toko[i].harga == hargaTerendah){
            printf("\n");
            printf("Kategori\t: %s", toko[i].jenis);
            printf("Sub-Kategori\t: %s", toko[i].nama);
            printf("Stok Barang\t: %d\n", toko[i].stok);
            printf("Diskon Barang\t: %d\n", toko[i].diskon);
            printf("Harga Barang\t: %d\n", toko[i].harga);
        }
    }

    //free(toko);
    return 0;
}
