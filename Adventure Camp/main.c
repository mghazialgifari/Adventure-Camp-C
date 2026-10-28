#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define JUMLAH_ALAT 5
#define MAX_TRANSAKSI 100
#define MAX_NAMA 100

// Struktur untuk menyimpan data peralatan
typedef struct {
    char nama[50];
    long long harga;
} Peralatan;

// Struktur untuk menyimpan riwayat transaksi
typedef struct {
    char namaPenyewa[MAX_NAMA];
    int nomorAlat;
    int jumlahUnit;
    int lamaSewa;
    long long subtotal;
    long long diskon;
    long long totalBayar;
} Transaksi;

// Data peralatan camping
Peralatan alat[JUMLAH_ALAT] = {
    {"Tenda Kapasitas 4 Orang", 50000},
    {"Sleeping Bag", 15000},
    {"Kompor Portable", 20000},
    {"Matras Camping", 10000},
    {"Lampu Camping", 12000}
};

// Array riwayat transaksi
Transaksi riwayat[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

// Fungsi untuk membaca input bilangan bulat
int inputInteger(const char *pesan) {
    char buffer[100];
    char *akhir;
    long nilai;

    while (1) {
        printf("%s", pesan);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nInput berakhir. Program dihentikan.\n");
            exit(0);
        }

        nilai = strtol(buffer, &akhir, 10);

        while (isspace((unsigned char)*akhir)) {
            akhir++;
        }

        if (akhir == buffer || *akhir != '\0') {
            printf("Input harus berupa bilangan bulat!\n");
            continue;
        }

        if (nilai < 1 || nilai > 2147483647L) {
            printf("Masukkan angka minimal 1!\n");
            continue;
        }

        return (int)nilai;
    }
}

// Fungsi untuk menampilkan daftar peralatan
void tampilkanPeralatan() {
    printf("\n");
    printf("========================================================\n");
    printf("                 DAFTAR PERALATAN\n");
    printf("========================================================\n");
    printf("%-5s %-35s %s\n", "No.", "Nama Peralatan", "Harga/Hari");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < JUMLAH_ALAT; i++) {
        printf("%-5d %-35s Rp%lld\n",
               i + 1, alat[i].nama, alat[i].harga);
    }

    printf("========================================================\n");
}

// Fungsi untuk menentukan persentase diskon
int hitungPersentaseDiskon(int lamaSewa) {
    if (lamaSewa >= 5) {
        return 15;
    } else if (lamaSewa >= 3) {
        return 10;
    } else {
        return 0;
    }
}

// Fungsi untuk menampilkan struk penyewaan
void tampilkanStruk(Transaksi t) {
    int persenDiskon = hitungPersentaseDiskon(t.lamaSewa);

    printf("\n");
    printf("========================================\n");
    printf("             ADVENTURE CAMP\n");
    printf("             STRUK PENYEWAAN\n");
    printf("========================================\n");

    printf("Nama Penyewa   : %s\n", t.namaPenyewa);
    printf("Peralatan      : %s\n", alat[t.nomorAlat].nama);
    printf("Harga per Hari : Rp%lld\n", alat[t.nomorAlat].harga);
    printf("Jumlah Unit    : %d\n", t.jumlahUnit);
    printf("Lama Sewa      : %d hari\n", t.lamaSewa);

    printf("----------------------------------------\n");
    printf("Subtotal       : Rp%lld\n", t.subtotal);
    printf("Diskon (%d%%)   : Rp%lld\n",
           persenDiskon, t.diskon);
    printf("----------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%lld\n", t.totalBayar);
    printf("========================================\n");
    printf("Terima kasih telah menggunakan\n");
    printf("layanan Adventure Camp!\n");
}

// Fungsi untuk melakukan penyewaan
void sewaPeralatan() {
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("\nKapasitas transaksi sudah penuh!\n");
        printf("Transaksi baru tidak dapat diproses.\n");
        return;
    }

    Transaksi t;

    printf("\n");
    printf("========================================\n");
    printf("          FORM PENYEWAAN ALAT\n");
    printf("========================================\n");

    // Input nama penyewa
    while (1) {
        printf("Nama Penyewa: ");

        if (fgets(t.namaPenyewa, sizeof(t.namaPenyewa), stdin) == NULL) {
            printf("\nInput berakhir. Program dihentikan.\n");
            exit(0);
        }

        t.namaPenyewa[strcspn(t.namaPenyewa, "\n")] = '\0';

        // Memastikan nama tidak kosong
        int kosong = 1;

        for (int i = 0; t.namaPenyewa[i] != '\0'; i++) {
            if (!isspace((unsigned char)t.namaPenyewa[i])) {
                kosong = 0;
                break;
            }
        }

        if (kosong) {
            printf("Nama penyewa tidak boleh kosong!\n");
            continue;
        }

        // Memeriksa apakah input nama terpotong
        if (strchr(t.namaPenyewa, '\0') != NULL) {
            break;
        }
    }

    tampilkanPeralatan();

    // Input nomor peralatan
    while (1) {
        t.nomorAlat = inputInteger("Pilih nomor peralatan [1-5]: ");

        if (t.nomorAlat >= 1 && t.nomorAlat <= JUMLAH_ALAT) {
            t.nomorAlat--;
            break;
        }

        printf("Nomor peralatan tidak tersedia!\n");
    }

    // Input jumlah unit
    t.jumlahUnit = inputInteger("Jumlah unit yang disewa: ");

    // Input lama penyewaan
    t.lamaSewa = inputInteger("Lama penyewaan (hari): ");

    // Menghitung biaya penyewaan
    t.subtotal = alat[t.nomorAlat].harga
                 * t.jumlahUnit
                 * t.lamaSewa;

    int persenDiskon = hitungPersentaseDiskon(t.lamaSewa);

    t.diskon = t.subtotal * persenDiskon / 100;
    t.totalBayar = t.subtotal - t.diskon;

    // Menyimpan transaksi ke dalam array
    riwayat[jumlahTransaksi] = t;
    jumlahTransaksi++;

    // Menampilkan struk
    tampilkanStruk(t);
}

// Fungsi untuk menampilkan riwayat transaksi
void tampilkanRiwayat() {
    printf("\n");
    printf("========================================================\n");
    printf("                RIWAYAT TRANSAKSI\n");
    printf("========================================================\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        printf("========================================================\n");
        return;
    }

    long long totalPendapatan = 0;

    printf("%-4s %-20s %-28s %s\n",
           "No.", "Nama", "Peralatan", "Total");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < jumlahTransaksi; i++) {
        printf("%-4d %-20.20s %-28.28s Rp%lld\n",
               i + 1,
               riwayat[i].namaPenyewa,
               alat[riwayat[i].nomorAlat].nama,
               riwayat[i].totalBayar);

        totalPendapatan += riwayat[i].totalBayar;
    }

    printf("--------------------------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%lld\n", totalPendapatan);
    printf("========================================================\n");
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    printf("\n");
    printf("========================================\n");
    printf("             ADVENTURE CAMP\n");
    printf("       SISTEM PENYEWAAN PERALATAN\n");
    printf("========================================\n");
    printf("1. Lihat Daftar Peralatan\n");
    printf("2. Sewa Peralatan\n");
    printf("3. Lihat Riwayat Transaksi\n");
    printf("4. Keluar\n");
    printf("========================================\n");
}

// Fungsi utama program
int main() {
    int pilihan;
    char konfirmasi[100];

    do {
        tampilkanMenu();

        pilihan = inputInteger("Pilih menu [1-4]: ");

        switch (pilihan) {
            case 1:
                tampilkanPeralatan();
                break;

            case 2:
                sewaPeralatan();

                // Konfirmasi setelah proses penyewaan
                if (jumlahTransaksi > 0) {
                    while (1) {
                        printf("\nKembali ke menu utama? (Y/T): ");

                        if (fgets(konfirmasi, sizeof(konfirmasi),
                                  stdin) == NULL) {
                            printf("\nInput berakhir. Program dihentikan.\n");
                            return 0;
                        }

                        konfirmasi[strcspn(konfirmasi, "\n")] = '\0';

                        if (strlen(konfirmasi) == 1 &&
                            (toupper((unsigned char)konfirmasi[0]) == 'Y' ||
                             toupper((unsigned char)konfirmasi[0]) == 'T')) {
                            break;
                        }

                        printf("Masukkan Y untuk kembali atau T untuk keluar.\n");
                    }

                    if (toupper((unsigned char)konfirmasi[0]) == 'T') {
                        printf("\nTerima kasih telah menggunakan "
                               "Adventure Camp!\n");
                        return 0;
                    }
                }
                break;

            case 3:
                tampilkanRiwayat();
                break;

            case 4:
                printf("\nTerima kasih telah menggunakan "
                       "Adventure Camp!\n");
                printf("Sampai jumpa!\n");
                break;

            default:
                printf("Menu tidak tersedia. Pilih menu 1-4!\n");
        }

    } while (pilihan != 4);

    return 0;
}
