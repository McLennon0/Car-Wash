#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct library {
    char nama_buku[50];
    char penulis[50];
    char kategori[30];
    int halaman;
    float harga;
};

void saveToFile(struct library library[], int count) {
    FILE *file = fopen("data_buku.txt", "w");
    if (file == NULL) {
        printf("Error membuka file untuk menyimpan data.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%s\t%d\t%.2f\n", 
                library[i].nama_buku, 
                library[i].penulis, 
                library[i].kategori,
                library[i].halaman, 
                library[i].harga);
    }
    fclose(file);
}



int loadFromFile(struct library library[]) {
    FILE *file = fopen("data_buku.txt", "r");
    if (file == NULL) {
        return 0;
    }
    int count = 0;
    while (fscanf(file, " %[^\t] %[^\t] %[^\t] %d %f", 
                  library[count].nama_buku, 
                  library[count].penulis, 
                  library[count].kategori,
                  &library[count].halaman, 
                  &library[count].harga) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}


void pauseAndClear() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar(); getchar(); 
}

void tampilkanData(struct library library[], int count) {
    if (count == 0) {
        printf("\nBelum ada data buku.\n");
        pauseAndClear();
        return;  
    } else {
        printf("========================================================================================================================\n");
        printf("%-5s %-40s %-30s %-20s %-10s %-10s\n", 
               "No", "Nama Buku", "Penulis", "Kategori", "Halaman", "Harga");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < count; i++) {
            printf("%-5d %-40s %-30s %-20s %-10d Rp%-10.2f\n", 
                   i + 1,
                   library[i].nama_buku, 
                   library[i].penulis, 
                   library[i].kategori,
                   library[i].halaman, 
                   library[i].harga);
        }
    }
}


void sortByHarga(struct library library[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (library[j].harga > library[j + 1].harga) {
                struct library temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }
}

void sortByHalaman(struct library library[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (library[j].halaman > library[j + 1].halaman) {
                struct library temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }
}

void searchHeader() {
   	printf("\n==================================================================================================================\n");
    printf("%-40s %-30s %-20s %-10s %-10s\n", 
            "Nama Buku", "Penulis", "Kategori", "Halaman", "Harga");
    printf("------------------------------------------------------------------------------------------------------------------\n");
}

void searchByPenulis(struct library library[], int count) {
    char penulis[50];
    printf("Masukkan nama penulis: ");
    scanf(" %[^\n]s", penulis);
    printf("\nHasil pencarian:\n");
    bool found = false;
    searchHeader();
    for (int i = 0; i < count; i++) {
        if (strcmp(library[i].penulis, penulis) == 0) {
            printf("%-40s %-30s %-20s %-10d Rp%-10.2f\n", 
                   library[i].nama_buku, 
                   library[i].penulis, 
                   library[i].kategori,
                   library[i].halaman, 
                   library[i].harga);
            found = true;
        }
    }
    if (!found) {
        printf("Tidak ada buku oleh penulis tersebut.\n");
    }
}

void searchByNamaBuku(struct library library[], int count) {
    char nama_buku[50];
    printf("Masukkan Judul Buku: ");
    scanf(" %[^\n]s", nama_buku);
    printf("\nHasil pencarian:\n");
    bool found = false;
    searchHeader();
    for (int i = 0; i < count; i++) {
        if (strcmp(library[i].nama_buku, nama_buku) == 0) {
            printf("%-40s %-30s %-20s %-10d Rp%-10.2f\n", 
                   library[i].nama_buku, 
                   library[i].penulis, 
                   library[i].kategori,
                   library[i].halaman, 
                   library[i].harga);
            found = true;
        }
    }
    if (!found) {
        printf("Tidak ada buku dengan judul tersebut.\n");
    }
}

void searchByKategori(struct library library[], int count) {
    char kategori[30];
    printf("Masukkan kategori: ");
    scanf(" %[^\n]s", kategori);
    printf("\nHasil pencarian:\n");
    bool found = false;
    searchHeader();
    for (int i = 0; i < count; i++) {
        if (strcmp(library[i].kategori, kategori) == 0) {
            printf("%-40s %-30s %-20s %-10d Rp%-10.2f\n", 
                   library[i].nama_buku, 
                   library[i].penulis, 
                   library[i].kategori,
                   library[i].halaman, 
                   library[i].harga);
            found = true;
        }
    }
    if (!found) {
        printf("Tidak ada buku dalam kategori tersebut.\n");
    }
}

void dataSubmenu(struct library library[], int count) {
    int choice;
    while (true) {
    	printf("\n\n==========================================");
        printf("\n1. Urutkan berdasarkan Harga\n");
        printf("2. Urutkan berdasarkan Halaman\n");
        printf("3. Cari Penulis\n");
        printf("4. Cari Judul Buku\n");
        printf("5. Cari Kategori\n");
        printf("0. Kembali ke menu utama\n");
        printf("\nMasukkan Pilihan: ");
        scanf("%d", &choice);
        printf("\n\n");

        switch (choice) {
        case 1:
            sortByHarga(library, count);
            tampilkanData(library, count);
            pauseAndClear();
            break;
        case 2:
            sortByHalaman(library, count);
            tampilkanData(library, count);
            pauseAndClear();
            break;
        case 3:
            searchByPenulis(library, count);
            pauseAndClear();
            break;
        case 4:
            searchByNamaBuku(library, count);
            pauseAndClear();
            break;
        case 5:
            searchByKategori(library, count);
            pauseAndClear();
            break;
        case 0:
            system("cls");
            return;
        default:
            printf("Input salah, coba lagi.\n");
        }
    }
}

int main() {
    struct library lib[100];
    int input, count = 0;

    count = loadFromFile(lib);

    while (true) {
    
        printf("=== Menu Utama ===\n");
        printf("1. Tambah Data\n");
        printf("2. Lihat Data\n");
        printf("0. Keluar Program\n");
        printf("\nMasukkan Pilihan: ");
        scanf("%d", &input);

        switch (input) {
        case 1:
            printf("Silahkan input data Buku dengan benar...\n");
            printf("\nNama buku: ");
            scanf(" %[^\n]s", lib[count].nama_buku);
            printf("Nama penulis: ");
            scanf(" %[^\n]s", lib[count].penulis);
            printf("Kategori: ");
            scanf(" %[^\n]s", lib[count].kategori);
            printf("Jumlah Halaman: ");
            scanf("%d", &lib[count].halaman);
            printf("Harga Buku (IDR): ");
            scanf("%f", &lib[count].harga);
            count++;
            printf("\nInformasi telah sukses ditambahkan!\n");
            saveToFile(lib, count);
            break;

        case 2:
            system("cls");
            tampilkanData(lib, count);  
            if (count > 0) {
                dataSubmenu(lib, count); 
            } else {
                system("cls");
            }
            break;

        case 0:
            printf("\nProgram selesai...\n");
            return 0;

        default:
            printf("\nInput salah! Mohon coba lagi.\n");
        }
    }
}
