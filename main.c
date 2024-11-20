#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

struct Waktu
{
    int tahun;
    int bulan;
    int tanggal;
};

// Struktur data untuk barang
struct Barang
{
    char kode[10];
    char nama[30];
    int hargaJual;
    int stok;
    int hargaBeli;
    int totalTerjual; // Menyimpan jumlah total barang terjual (untuk analisis)
};

// Struktur data untuk menyimpan barang yang dibeli
struct Pembelian
{
    char nama[30];
    int harga;
    int jumlah;
};

struct PenjualanHarian
{
    struct Waktu waktu;
    int totalPenjualan;
    int labaRugi;
};

// Array untuk menyimpan penjualan harian
struct PenjualanHarian penjualanHarian[365];
int indexPenjualanHarian = 0;

// Fungsi untuk menambahkan data penjualan harian
void tambahPenjualanHarian(int totalPenjualan, int labaRugi, struct Waktu waktu)
{
    printf(BLUE"\n=== Penjualan Harian ===\n"RESET);
    penjualanHarian[indexPenjualanHarian].waktu = waktu;
    penjualanHarian[indexPenjualanHarian].totalPenjualan = totalPenjualan;
    penjualanHarian[indexPenjualanHarian].labaRugi = labaRugi;
    indexPenjualanHarian++;
}

// Fungsi untuk menghitung laba/rugi harian dan menyimpannya
void hitungLabaRugiHarian(struct Barang daftarBarang[], int jumlahBarang, struct Waktu waktu)
{
    int totalPenjualan = 0;
    int totalLabaRugi = 0;

    for (int i = 0; i < jumlahBarang; i++)
    {
        totalPenjualan += daftarBarang[i].hargaJual * daftarBarang[i].totalTerjual;
        totalLabaRugi += (daftarBarang[i].hargaJual - daftarBarang[i].hargaBeli) * daftarBarang[i].totalTerjual;
    }

    printf(GREEN"\n=== Laba Rugi Harian ===\n");
    printf("Laba Rugi pada %d-%d-%d: Rp%d\n", waktu.tahun, waktu.bulan, waktu.tanggal, totalLabaRugi - (daftarBarang[0].hargaBeli * daftarBarang[0].totalTerjual));

    tambahPenjualanHarian(totalPenjualan, totalLabaRugi, waktu);
}

// Fungsi untuk analisis penjualan mingguan
void analisisPenjualanMingguan()
{
    int totalPenjualanMinggu = 0;
    int labaRugiMinggu = 0;

    printf("\n=== Analisis Penjualan Mingguan ===\n");
    for (int i = indexPenjualanHarian - 7; i < indexPenjualanHarian; i++)
    {
        if (i >= 0)
        {
            totalPenjualanMinggu += penjualanHarian[i].totalPenjualan;
            labaRugiMinggu += penjualanHarian[i].labaRugi;
        }
    }
    printf("Penjualan Mingguan: Rp%d, Laba Rugi Mingguan: Rp%d\n", totalPenjualanMinggu, labaRugiMinggu);
}

// Fungsi untuk analisis penjualan bulanan
void analisisPenjualanBulanan(struct Waktu waktu)
{
    int totalPenjualanBulan = 0;
    int labaRugiBulan = 0;

    printf(GREEN"\n=== Analisis Penjualan Bulanan ===\n" RESET);
    for (int i = 0; i < indexPenjualanHarian; i++)
    {
        if (penjualanHarian[i].waktu.bulan == waktu.bulan && penjualanHarian[i].waktu.tahun == waktu.tahun)
        {
            totalPenjualanBulan += penjualanHarian[i].totalPenjualan;
            labaRugiBulan += penjualanHarian[i].labaRugi;
        }
    }
    printf("Penjualan Bulanan untuk bulan %d: Rp%d, Laba Rugi Bulanan: Rp%d\n", waktu.bulan, totalPenjualanBulan, labaRugiBulan);
}

void checkLabaRugi(struct Barang daftarBarang[], int jumlahBarang, struct Waktu waktu)
{
    int totalPenjualan = 0;
    for (int i = 0; i < jumlahBarang; i++)
    {
        totalPenjualan += daftarBarang[i].hargaJual * daftarBarang[i].totalTerjual;
    }
    int labaRugi = totalPenjualan - (daftarBarang[0].hargaBeli * daftarBarang[0].totalTerjual);
    printf("\n=== Laba Rugi Harian ===\n");
    printf("Laba Rugi dari %d-%d-%d: Rp%d\n", waktu.tahun, waktu.bulan, waktu.tanggal, labaRugi);
}

void rekapPenjualan(struct PenjualanHarian penjualanHarian[], int jumlahHari) {
    printf(BLUE"\n=== Rekapan Penjualan ===\n"RESET);
    printf("%-10s %-15s %-15s\n", "Tanggal", "Total Penjualan", "Laba/Rugi");
    printf("--------------------------------------------\n");

    for (int i = 0; i < jumlahHari; i++) {
        printf("%4d-%02d-%02d %-15d %-15d\n",
               penjualanHarian[i].waktu.tahun,
               penjualanHarian[i].waktu.bulan,
               penjualanHarian[i].waktu.tanggal,
               penjualanHarian[i].totalPenjualan,
               penjualanHarian[i].labaRugi);
    }

    printf("--------------------------------------------\n");
}

void menuPembeli(struct Barang daftarBarang[], int jumlahBarang)
{
    struct Pembelian daftarPembelian[100];
    int indexPembelian = 0;
    int totalHarga = 0;
    char kodeInput[10];

    printf("\n=== Sistem Kasir Sederhana ===\n");
    while (1)
    {
        printf("\nMasukkan kode barang (atau ketik 'selesai' untuk menyelesaikan transaksi): ");
        scanf("%s", kodeInput);

        if (strcmp(kodeInput, "selesai") == 0)
        {
            break;
        }

        int barangDitemukan = 0;
        for (int i = 0; i < jumlahBarang; i++)
        {
            if (strcmp(kodeInput, daftarBarang[i].kode) == 0)
            {
                printf("Barang ditemukan: %s - Harga: Rp%d\n", daftarBarang[i].nama, daftarBarang[i].hargaJual);

                int jumlah;
                printf("Masukkan jumlah barang yang dibeli: ");
                scanf("%d", &jumlah);

                totalHarga += daftarBarang[i].hargaJual * jumlah;
                barangDitemukan = 1;

                // mengurangi stok barang berdasarkan jumlah yang dibeli
                daftarBarang[i].stok -= jumlah;

                if (daftarBarang[i].stok < 0)
                {
                    printf("Stok barang tidak cukup.\n");
                    daftarBarang[i].stok += jumlah;
                    continue;
                }

                

                strcpy(daftarPembelian[indexPembelian].nama, daftarBarang[i].nama);
                daftarPembelian[indexPembelian].harga = daftarBarang[i].hargaJual;
                daftarPembelian[indexPembelian].jumlah = jumlah;
                daftarBarang[i].totalTerjual += jumlah; // Update jumlah terjual untuk analisis
                indexPembelian++;
                break;
            }
        }

        if (!barangDitemukan)
        {
            printf("Barang dengan kode %s tidak ditemukan.\n", kodeInput);
        }
    }

    printf("\n===================================\n");
    printf("            INVOICE PEMBELIAN\n");
    printf("===================================\n");
    printf("%-3s %-20s %-10s %-10s\n", "No", "Nama Barang", "Jumlah", "Total");
    printf("-----------------------------------\n");

    for (int i = 0; i < indexPembelian; i++)
    {
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

void analisisPenjualan()
{
    rekapPenjualan(penjualanHarian, indexPenjualanHarian);
}

void produkTerlaris(struct Barang daftarBarang[], int jumlahBarang)
{
    printf("\n=== Analisis Produk Terlaris ===\n");
    struct Barang *terlaris = &daftarBarang[0];
    for (int i = 1; i < jumlahBarang; i++)
    {
        if (daftarBarang[i].totalTerjual > terlaris->totalTerjual)
        {
            terlaris = &daftarBarang[i];
        }
    }
    printf("Produk Terlaris: %s dengan total terjual %d unit\n", terlaris->nama, terlaris->totalTerjual);
}

void produkPenjualanRendah(struct Barang daftarBarang[], int jumlahBarang)
{
    printf("\n=== Analisis Produk dengan Penjualan Rendah ===\n");
    struct Barang *penjualanRendah = &daftarBarang[0];
    for (int i = 1; i < jumlahBarang; i++)
    {
        if (daftarBarang[i].totalTerjual < penjualanRendah->totalTerjual)
        {
            penjualanRendah = &daftarBarang[i];
        }
    }
    printf("Produk dengan Penjualan Terendah: %s dengan total terjual %d unit\n", penjualanRendah->nama, penjualanRendah->totalTerjual);
}

void analisisStok(struct Barang daftarBarang[], int jumlahBarang)
{
    printf("\n=== Analisis Stok Produk ===\n");
    for (int i = 0; i < jumlahBarang; i++)
    {
        printf("%-20s : Stok saat ini: %d\n", daftarBarang[i].nama, daftarBarang[i].stok);
    }
}

void menuAnalisisPenjual(struct Barang daftarBarang[], int jumlahBarang, struct Waktu waktu) {
    int pilihan;
    while (1) {
        printf("\n=== Menu Analisis Penjualan ===\n");
        printf("1. Analisis Penjualan Harian\n");
        printf("2. Analisis Penjualan Mingguan\n");
        printf("3. Analisis Penjualan Bulanan\n");
        printf("4. Produk Terlaris\n");
        printf("5. Produk dengan Penjualan Rendah\n");
        printf("6. Analisis Stok Produk\n");
        printf("0. Kembali ke Menu Utama\n");

        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                hitungLabaRugiHarian(daftarBarang, jumlahBarang, waktu);
                break;
            case 2:
                analisisPenjualanMingguan();
                break;
            case 3:
                analisisPenjualanBulanan(waktu);
                break;
            case 4:
                produkTerlaris(daftarBarang, jumlahBarang);
                break;
            case 5:
                produkPenjualanRendah(daftarBarang, jumlahBarang);
                break;
            case 6:
                analisisStok(daftarBarang, jumlahBarang);
                break;
            case 0:
                return;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }
}

void today(struct Waktu *waktu)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    waktu->tahun = tm.tm_year + 1900;
    waktu->bulan = tm.tm_mon + 1;
    waktu->tanggal = tm.tm_mday;
}

int main()
{
    struct Barang daftarBarang[] = {
        {"BRG001", "Beras", 10000, 50, 8000, 0},
        {"BRG002", "Gula", 15000, 60, 12000, 0},
        {"BRG003", "Minyak", 20000, 30, 18000, 0},
        {"BRG004", "Telur", 25000, 40, 22000, 0},
        {"BRG005", "Susu", 30000, 25, 27000, 0},
        {"BRG006", "Rokok", 32000, 100, 29000, 0},
        {"BRG007", "Shampo", 12000, 50, 10000, 0},
        {"BRG008", "Sabun", 7000, 75, 6000, 0},
        {"BRG009", "Pasta Gigi", 9000, 90, 8000, 0},
        {"BRG010", "Sikat", 14000, 45, 12000, 0},
        {"BRG011", "Minuman", 30000, 70, 28000, 0},
        {"BRG012", "Jamu", 30000, 60, 28000, 0}};
    int jumlahBarang = sizeof(daftarBarang) / sizeof(daftarBarang[0]);
    int pilihan;
    struct Waktu waktu;
    today(&waktu);

    while (1)
    {
        printf("\n=== Menu Utama ===\n");
        printf("1. Sebagai Pembeli\n");
        printf("2. Sebagai Penjual\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        if (pilihan == 1)
        {
            menuPembeli(daftarBarang, jumlahBarang);
        }
        else if (pilihan == 2)
        {
            menuAnalisisPenjual(daftarBarang, jumlahBarang, waktu);
        }
        else if (pilihan == 0)
        {
            printf("Terima kasih telah menggunakan aplikasi kasir ini!\n");
            break;
        }
        else
        {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }

    return 0;
}
