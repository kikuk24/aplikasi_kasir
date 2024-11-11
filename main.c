#include <stdio.h>
#include <string.h>

// Struktur data untuk barang
struct Barang {
    char kode[10];
    char nama[30];
    int harga;
    int totalTerjual; // Menyimpan jumlah total barang terjual (untuk analisis)
};

// Struktur data untuk menyimpan barang yang dibeli
struct Pembelian {
    char nama[30];
    int harga;
    int jumlah;
};

void menuPembeli(struct Barang daftarBarang[], int jumlahBarang) {
    struct Pembelian daftarPembelian[100];
    int indexPembelian = 0;
    int totalHarga = 0;
    char kodeInput[10];
    
    printf("\n=== Sistem Kasir Sederhana ===\n");
    while (1) {
        printf("\nMasukkan kode barang (atau ketik 'selesai' untuk menyelesaikan transaksi): ");
        scanf("%s", kodeInput);

        if (strcmp(kodeInput, "selesai") == 0) {
            break;
        }

        int barangDitemukan = 0;
        for (int i = 0; i < jumlahBarang; i++) {
            if (strcmp(kodeInput, daftarBarang[i].kode) == 0) {
                printf("Barang ditemukan: %s - Harga: Rp%d\n", daftarBarang[i].nama, daftarBarang[i].harga);

                int jumlah;
                printf("Masukkan jumlah barang yang dibeli: ");
                scanf("%d", &jumlah);

                totalHarga += daftarBarang[i].harga * jumlah;
                barangDitemukan = 1;

                strcpy(daftarPembelian[indexPembelian].nama, daftarBarang[i].nama);
                daftarPembelian[indexPembelian].harga = daftarBarang[i].harga;
                daftarPembelian[indexPembelian].jumlah = jumlah;
                daftarBarang[i].totalTerjual += jumlah; // Update jumlah terjual untuk analisis
                indexPembelian++;
                break;
            }
        }

        if (!barangDitemukan) {
            printf("Barang dengan kode %s tidak ditemukan.\n", kodeInput);
        }
    }

    printf("\n===================================\n");
    printf("            INVOICE PEMBELIAN\n");
    printf("===================================\n");
    printf("%-3s %-20s %-10s %-10s\n", "No", "Nama Barang", "Jumlah", "Total");
    printf("-----------------------------------\n");

    for (int i = 0; i < indexPembelian; i++) {
        printf("%-3d %-20s %-10d Rp%-10d\n",
               i + 1,
               daftarPembelian[i].nama,
               daftarPembelian[i].jumlah,
               daftarPembelian[i].harga * daftarPembelian[i].jumlah);
    }

    printf("-----------------------------------\n");
    printf("%-33s Rp%-10d\n", "Total Belanja", totalHarga);
    printf("===================================\n");
    printf("Terima kasih telah berbelanja!\n");
}

void analisisPenjualan(struct Barang daftarBarang[], int jumlahBarang) {
    printf("\n=== Analisis Penjualan Harian, Mingguan, dan Bulanan ===\n");
    printf("Fitur ini dapat ditambahkan untuk mencatat penjualan berdasarkan waktu.\n");
}


void produkTerlaris(struct Barang daftarBarang[], int jumlahBarang) {
    printf("\n=== Analisis Produk Terlaris ===\n");
    struct Barang *terlaris = &daftarBarang[0];
    for (int i = 1; i < jumlahBarang; i++) {
        if (daftarBarang[i].totalTerjual > terlaris->totalTerjual) {
            terlaris = &daftarBarang[i];
        }
    }
    printf("Produk Terlaris: %s dengan total terjual %d unit\n", terlaris->nama, terlaris->totalTerjual);
}

void produkPenjualanRendah(struct Barang daftarBarang[], int jumlahBarang) {
    printf("\n=== Analisis Produk dengan Penjualan Rendah ===\n");
    struct Barang *penjualanRendah = &daftarBarang[0];
    for (int i = 1; i < jumlahBarang; i++) {
        if (daftarBarang[i].totalTerjual < penjualanRendah->totalTerjual) {
            penjualanRendah = &daftarBarang[i];
        }
    }
    printf("Produk dengan Penjualan Terendah: %s dengan total terjual %d unit\n", penjualanRendah->nama, penjualanRendah->totalTerjual);
}

void analisisStok(struct Barang daftarBarang[], int jumlahBarang) {
    printf("\n=== Analisis Stok Produk ===\n");
    for (int i = 0; i < jumlahBarang; i++) {
        printf("%-20s : Total Terjual: %d\n", daftarBarang[i].nama, daftarBarang[i].totalTerjual);
    }
}

void menuAnalisisPenjual(struct Barang daftarBarang[], int jumlahBarang) {
    int pilihan;
    while (1) {
        printf("\n=== Menu Analisis Penjualan ===\n");
        printf("1. Penjualan Harian, Mingguan, dan Bulanan\n");
        printf("2. Produk Terlaris\n");
        printf("3. Produk dengan Penjualan Rendah\n");
        printf("4. Analisis Stok Produk\n");
        printf("0. Kembali ke Menu Utama\n");

        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                analisisPenjualan(daftarBarang, jumlahBarang);
                break;
            case 2:
                produkTerlaris(daftarBarang, jumlahBarang);
                break;
            case 3:
                produkPenjualanRendah(daftarBarang, jumlahBarang);
                break;
            case 4:
                analisisStok(daftarBarang, jumlahBarang);
                break;
            case 0:
                return;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }
}

int main() {
    struct Barang daftarBarang[] = {
        {"BRG001", "Beras", 10000, 0},
        {"BRG002", "Gula", 15000, 0},
        {"BRG003", "Minyak", 20000, 0},
        {"BRG004", "Telur", 25000, 0},
        {"BRG005", "Susu", 30000, 0},
        {"BRG006", "Rokok", 32000, 0},
        {"BRG007", "Shampo", 12000, 0},
        {"BRG008", "Sabun", 7000, 0},
        {"BRG009", "Pasta Gigi", 9000, 0},
        {"BRG010", "Sikat", 14000, 0},
        {"BRG011", "Minuman", 30000, 0},
        {"BRG012", "Jamu", 30000, 0}
    };
    int jumlahBarang = sizeof(daftarBarang) / sizeof(daftarBarang[0]);
    int pilihan;


    while (1) {
        printf("\n=== Menu Utama ===\n");
        printf("1. Sebagai Pembeli\n");
        printf("2. Sebagai Penjual\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            menuPembeli(daftarBarang, jumlahBarang);
        } else if (pilihan == 2) {
            menuAnalisisPenjual(daftarBarang, jumlahBarang);
        } else if (pilihan == 0) {
            printf("Terima kasih telah menggunakan aplikasi kasir ini!\n");
            break;
        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }

    return 0;
}