#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

#define MAX_BARANG 100
#define MAX_PEMBELIAN 100

typedef struct
{
    int tahun;
    int bulan;
    int tanggal;
} Waktu;

typedef struct
{
    char kode[10];
    char nama[30];
    int hargaJual;
    int stok;
    int hargaBeli;
    int totalTerjual;
} Barang;

typedef struct
{
    char kode[10];
    char nama[30];
    int harga;
    int jumlah;
    int totalHarga;
} Pembelian;
void barangTerlaris(Barang daftarBarang[], int jumlahBarang);
void barangTidakLaris(Barang daftarBarang[], int jumlahBarang);
// Fungsi mendapatkan tanggal hari ini
void today(Waktu *waktu, bool manual)
{
    if (manual)
    {
        printf("Masukkan tanggal (YYYY-MM-DD): ");
        scanf("%d-%d-%d", &waktu->tahun, &waktu->bulan, &waktu->tanggal);
    }
    else
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        waktu->tahun = tm.tm_year + 1900;
        waktu->bulan = tm.tm_mon + 1;
        waktu->tanggal = tm.tm_mday;
    }
}

// Fungsi memuat data barang dari file CSV
int muatDariCSV(Barang daftarBarang[], const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf(YELLOW "File tidak ditemukan. Membuat file baru...\n" RESET);
        file = fopen(filename, "w");
        fprintf(file, "Kode,Nama Barang,Harga Jual,Stok,Harga Beli,Total Terjual\n");
        fclose(file);
        return 0;
    }

    char line[256];
    int index = 0;
    fgets(line, sizeof(line), file); // Lewati header
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^,],%[^,],%d,%d,%d,%d",
               daftarBarang[index].kode,
               daftarBarang[index].nama,
               &daftarBarang[index].hargaJual,
               &daftarBarang[index].stok,
               &daftarBarang[index].hargaBeli,
               &daftarBarang[index].totalTerjual);
        index++;
    }
    fclose(file);
    return index;
}

// Fungsi menyimpan data barang ke file CSV
void simpanKeCSV(Barang daftarBarang[], int jumlahBarang, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf(RED "Gagal membuka file CSV untuk menyimpan data.\n" RESET);
        return;
    }

    fprintf(file, "Kode Barang,Nama Barang,Harga Jual,Stok,Harga Beli,Total Terjual\n");
    for (int i = 0; i < jumlahBarang; i++)
    {
        fprintf(file, "%s,%s,%d,%d,%d,%d\n",
                daftarBarang[i].kode,
                daftarBarang[i].nama,
                daftarBarang[i].hargaJual,
                daftarBarang[i].stok,
                daftarBarang[i].hargaBeli,
                daftarBarang[i].totalTerjual);
    }
    fclose(file);
    printf(GREEN "Data barang berhasil disimpan ke file %s.\n" RESET, filename);
}

// Fungsi menambah barang baru
void tambahBarang(Barang daftarBarang[], int *jumlahBarang)
{
    if (*jumlahBarang >= MAX_BARANG)
    {
        printf(RED "Kapasitas maksimum barang tercapai.\n" RESET);
        return;
    }

    Barang barangBaru;
    sprintf(barangBaru.kode, "BRG%03d", *jumlahBarang + 1);

    printf("Masukkan nama barang: ");
    scanf(" %[^\n]", barangBaru.nama);

    printf("Masukkan harga jual: ");
    scanf("%d", &barangBaru.hargaJual);

    printf("Masukkan stok: ");
    scanf("%d", &barangBaru.stok);

    printf("Masukkan harga beli: ");
    scanf("%d", &barangBaru.hargaBeli);

    barangBaru.totalTerjual = 0;
    daftarBarang[*jumlahBarang] = barangBaru;
    (*jumlahBarang)++;
}

// Fungsi menampilkan daftar barang
void tampilkanBarang(Barang daftarBarang[], int jumlahBarang)
{
    printf("\n%-10s %-20s %-10s %-10s\n", "Kode", "Nama Barang", "Harga", "Stok");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < jumlahBarang; i++)
    {
        printf("%-10s %-20s %-10d %-10d\n",
               daftarBarang[i].kode,
               daftarBarang[i].nama,
               daftarBarang[i].hargaJual,
               daftarBarang[i].stok);
    }
    printf("---------------------------------------------------\n");
}
void simpanTransaksiCSV(const char *filename, Pembelian daftarPembelian[], int jumlahPembelian, Waktu waktu)
{
    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf(RED "Gagal membuka file transaksi.\n" RESET);
        return;
    }

    for (int i = 0; i < jumlahPembelian; i++)
    {
        fprintf(file, "%d-%02d-%02d,%s,%s,%d,%d,%d\n",
                waktu.tahun, waktu.bulan, waktu.tanggal,
                daftarPembelian[i].kode,
                daftarPembelian[i].nama,
                daftarPembelian[i].harga,
                daftarPembelian[i].jumlah,
                daftarPembelian[i].totalHarga);
    }
    fclose(file);
    printf(GREEN "Transaksi berhasil disimpan ke file.\n" RESET);
}

// Fungsi untuk menu pembelian
void menuPembeli(Barang daftarBarang[], int jumlahBarang, const char *transaksiFile, const char *barangFile)
{
    Pembelian daftarPembelian[100];
    int indexPembelian = 0, totalHarga = 0;
    char kodeInput[10];
    Waktu waktu;
    today(&waktu, false);

    printf("\n=== Sistem Kasir ===\n");
    while (1)
    {
        printf("\nMasukkan kode barang (atau 'selesai' untuk menyelesaikan transaksi): ");
        scanf("%9s", kodeInput);

        if (strcmp(kodeInput, "selesai") == 0)
        {
            break;
        }

        bool barangDitemukan = false;
        for (int i = 0; i < jumlahBarang; i++)
        {
            if (strcmp(kodeInput, daftarBarang[i].kode) == 0)
            {
                printf("Barang ditemukan: %s, Harga: Rp%d\n", daftarBarang[i].nama, daftarBarang[i].hargaJual);

                int jumlah;
                printf("Masukkan jumlah barang yang dibeli: ");
                scanf("%d", &jumlah);

                if (jumlah > daftarBarang[i].stok)
                {
                    printf(RED "Stok tidak cukup.\n" RESET);
                    break;
                }

                // Kurangi stok
                daftarBarang[i].stok -= jumlah;

                // Catat pembelian
                strcpy(daftarPembelian[indexPembelian].kode, daftarBarang[i].kode);
                strcpy(daftarPembelian[indexPembelian].nama, daftarBarang[i].nama);
                daftarPembelian[indexPembelian].harga = daftarBarang[i].hargaJual;
                daftarPembelian[indexPembelian].jumlah = jumlah;
                daftarPembelian[indexPembelian].totalHarga = jumlah * daftarBarang[i].hargaJual;

                // Tambahkan ke total
                totalHarga += daftarPembelian[indexPembelian].totalHarga;
                daftarBarang[i].totalTerjual += jumlah;

                indexPembelian++;
                barangDitemukan = true;
                break;
            }
        }

        if (!barangDitemukan)
        {
            printf(YELLOW "Kode barang tidak ditemukan.\n" RESET);
        }
    }

    // Cetak invoice
    printf("\n===================================\n");
    printf("            INVOICE PEMBELIAN\n");
    printf("===================================\n");
    printf("%-3s %-20s %-10s %-10s\n", "No", "Nama Barang", "Jumlah", "Total");
    printf("-----------------------------------\n");
    for (int i = 0; i < indexPembelian; i++)
    {
        printf("%-3d %-20s %-10d Rp%-10d\n", i + 1,
               daftarPembelian[i].nama,
               daftarPembelian[i].jumlah,
               daftarPembelian[i].totalHarga);
    }
    printf("-----------------------------------\n");
    printf("%-33s Rp%-10d\n", "Total Belanja", totalHarga);
    printf("===================================\n");
    printf("Terima kasih telah berbelanja!\n");

    // Simpan transaksi ke file CSV
    if (indexPembelian > 0)
    {
        simpanTransaksiCSV(transaksiFile, daftarPembelian, indexPembelian, waktu);
        // Simpan stok terbaru ke file barang.csv
        simpanKeCSV(daftarBarang, jumlahBarang, barangFile);
    }
}

int bacaTransaksiCSV(const char *filename, Waktu waktu[], int penjualan[], int labaRugi[])
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf(RED "File tidak ditemukan: %s\n" RESET, filename);
        return 0;
    }

    char line[256];
    int index = 0;

    fgets(line, sizeof(line), file); // Lewati header
    while (fgets(line, sizeof(line), file))
    {
        int tahun, bulan, tanggal, totalPenjualan, totalLabaRugi;
        if (sscanf(line, "%d-%d-%d,%*[^,],%*[^,],%d,%*d,%d",
                   &tahun, &bulan, &tanggal, &totalPenjualan, &totalLabaRugi) == 5)
        {
            waktu[index].tahun = tahun;
            waktu[index].bulan = bulan;
            waktu[index].tanggal = tanggal;
            penjualan[index] = totalPenjualan;
            labaRugi[index] = totalLabaRugi;
            index++;
        }
    }
    fclose(file);
    return index;
}
void analisisMingguan(Waktu waktu[], int penjualan[], int labaRugi[], int jumlahHari)
{
    int totalPenjualan = 0, totalLabaRugi = 0;

    printf("\n=== Rekapan Mingguan ===\n");
    int start = (jumlahHari >= 7) ? jumlahHari - 7 : 0;
    for (int i = start; i < jumlahHari; i++)
    {
        totalPenjualan += penjualan[i];
        totalLabaRugi += labaRugi[i];
        printf("Tanggal: %d-%02d-%02d, Penjualan: Rp%d, Laba/Rugi: Rp%d\n",
               waktu[i].tahun, waktu[i].bulan, waktu[i].tanggal, penjualan[i], labaRugi[i]);
    }
    printf("Total Penjualan Mingguan: Rp%d\n", totalPenjualan);
    printf("Total Laba/Rugi Mingguan: Rp%d\n", totalLabaRugi);
}
void analisisBulanan(Waktu waktu[], int penjualan[], int labaRugi[], int jumlahHari, int bulan, int tahun)
{
    int totalPenjualan = 0, totalLabaRugi = 0;

    printf("\n=== Rekapan Bulanan ===\n");
    for (int i = 0; i < jumlahHari; i++)
    {
        if (waktu[i].bulan == bulan && waktu[i].tahun == tahun)
        {
            totalPenjualan += penjualan[i];
            totalLabaRugi += labaRugi[i];
        }
    }
    printf("Total Penjualan Bulanan: Rp%d\n", totalPenjualan);
    printf("Total Laba/Rugi Bulanan: Rp%d\n", totalLabaRugi);
}
void analisisTahunan(Waktu waktu[], int penjualan[], int labaRugi[], int jumlahHari, int tahun)
{
    int totalPenjualan = 0, totalLabaRugi = 0;

    printf("\n=== Rekapan Tahunan ===\n");
    for (int i = 0; i < jumlahHari; i++)
    {
        if (waktu[i].tahun == tahun)
        {
            totalPenjualan += penjualan[i];
            totalLabaRugi += labaRugi[i];
        }
    }
    printf("Total Penjualan Tahunan: Rp%d\n", totalPenjualan);
    printf("Total Laba/Rugi Tahunan: Rp%d\n", totalLabaRugi);
}
void analisisStok(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf(RED "File barang tidak ditemukan.\n" RESET);
        return;
    }

    char line[256];
    int stokRendah = 10; // Batas stok rendah
    printf("\n=== Analisis Stok ===\n");
    printf("%-10s %-20s %-10s\n", "Kode", "Nama Barang", "Stok");
    printf("--------------------------------------\n");

    fgets(line, sizeof(line), file); // Lewati header
    while (fgets(line, sizeof(line), file))
    {
        char kode[10], nama[30];
        int stok;
        sscanf(line, "%[^,],%[^,],%*d,%d,%*d,%*d", kode, nama, &stok);
        printf("%-10s %-20s %-10d\n", kode, nama, stok);

        if (stok < stokRendah)
        {
            printf(YELLOW "Barang %s memiliki stok rendah: %d\n" RESET, nama, stok);
        }
    }
    fclose(file);
}
void menuAnalisis(const char *transaksiFile, const char *barangFile)
{
    int pilihan;
    Waktu waktu[365];
    int penjualan[365], labaRugi[365];
    int jumlahHari = bacaTransaksiCSV(transaksiFile, waktu, penjualan, labaRugi);

    while (1)
    {
        printf(CYAN "\n=== Menu Analisis ===\n" RESET);
        printf("1. Analisis Penjualan Mingguan\n");
        printf("2. Analisis Penjualan Bulanan\n");
        printf("3. Analisis Penjualan Tahunan\n");
        printf("4. Analisis Stok Barang\n");
        printf("0. Kembali\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            analisisMingguan(waktu, penjualan, labaRugi, jumlahHari);
            break;
        case 2:
        {
            int bulan, tahun;
            printf("Masukkan bulan (1-12): ");
            scanf("%d", &bulan);
            printf("Masukkan tahun: ");
            scanf("%d", &tahun);
            analisisBulanan(waktu, penjualan, labaRugi, jumlahHari, bulan, tahun);
            break;
        }
        case 3:
        {
            int tahun;
            printf("Masukkan tahun: ");
            scanf("%d", &tahun);
            analisisTahunan(waktu, penjualan, labaRugi, jumlahHari, tahun);
            break;
        }
        case 4:
            analisisStok(barangFile);
            break;
        case 0:
            return;
        default:
            printf(RED "Pilihan tidak valid.\n" RESET);
        }
    }
}
void menuAnalisisBarang(Barang daftarBarang[], int jumlahBarang)
{
    int pilihan;

    while (1)
    {
        printf(CYAN "\n=== Menu Analisis Barang ===\n" RESET);
        printf("1. Barang Terlaris\n");
        printf("2. Barang Tidak Laris\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            barangTerlaris(daftarBarang, jumlahBarang);
            break;
        case 2:
            barangTidakLaris(daftarBarang, jumlahBarang);
            break;
        case 0:
            return;
        default:
            printf(RED "Pilihan tidak valid.\n" RESET);
        }
    }
}
void barangTerlaris(Barang daftarBarang[], int jumlahBarang)
{
    if (jumlahBarang == 0)
    {
        printf(YELLOW "Tidak ada data barang.\n" RESET);
        return;
    }

    int indexTerlaris = 0;
    for (int i = 1; i < jumlahBarang; i++)
    {
        if (daftarBarang[i].totalTerjual > daftarBarang[indexTerlaris].totalTerjual)
        {
            indexTerlaris = i;
        }
    }

    printf(GREEN "\n=== Barang Terlaris ===\n" RESET);
    printf("Kode: %s\n", daftarBarang[indexTerlaris].kode);
    printf("Nama: %s\n", daftarBarang[indexTerlaris].nama);
    printf("Total Terjual: %d unit\n", daftarBarang[indexTerlaris].totalTerjual);
}
void barangTidakLaris(Barang daftarBarang[], int jumlahBarang)
{
    if (jumlahBarang == 0)
    {
        printf(YELLOW "Tidak ada data barang.\n" RESET);
        return;
    }

    int indexTidakLaris = 0;
    for (int i = 1; i < jumlahBarang; i++)
    {
        if (daftarBarang[i].totalTerjual < daftarBarang[indexTidakLaris].totalTerjual)
        {
            indexTidakLaris = i;
        }
    }

    printf(RED "\n=== Barang Tidak Laris ===\n" RESET);
    printf("Kode: %s\n", daftarBarang[indexTidakLaris].kode);
    printf("Nama: %s\n", daftarBarang[indexTidakLaris].nama);
    printf("Total Terjual: %d unit\n", daftarBarang[indexTidakLaris].totalTerjual);
}

// Main function
int main()
{
    Barang daftarBarang[MAX_BARANG];
    int jumlahBarang = muatDariCSV(daftarBarang, "barang.csv");
    int pilihan;

    while (1)
    {
        printf(CYAN "\n=== Menu Utama ===\n" RESET);
        printf("1. Pembeli\n");
        printf("2. Tambah Barang\n");
        printf("3. Tampilkan Barang\n");
        printf("4. Simpan Barang\n");
        printf("5. Analisis\n");
        printf("6. Analisis Barang\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            menuPembeli(daftarBarang, jumlahBarang, "rekap_transaksi.csv", "barang.csv");
            break;
        case 2:
            tambahBarang(daftarBarang, &jumlahBarang);
            break;
        case 3:
            tampilkanBarang(daftarBarang, jumlahBarang);
            break;
        case 4:
            simpanKeCSV(daftarBarang, jumlahBarang, "barang.csv");
            break;
        case 5:
            menuAnalisis("rekap_transaksi.csv", "barang.csv");
            break;
        case 6:
            menuAnalisisBarang(daftarBarang, jumlahBarang);
            break;
        case 0:
            printf(GREEN "Terima kasih!\n" RESET);
            return 0;
        default:
            printf(RED "Pilihan tidak valid.\n" RESET);
        }
    }
    return 0;
}
