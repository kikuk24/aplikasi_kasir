#include <stdio.h>
#include <string.h>

// Struktur data untuk barang
struct Barang
{
  char kode[10];
  char nama[30];
  int harga;
};

// Struktur data untuk menyimpan barang yang dibeli
struct Pembelian
{
  char nama[30];
  int harga;
  int jumlah;
};

void headerAplikasi()
{
  printf("    _    ____  _     ___ _  __   _    ____ ___   _  __   _    ____ ___ ____  \n");
  printf("   / \\  |  _ \\| |   |_ _| |/ /  / \\  / ___|_ _| | |/ /  / \\  / ___|_ _|  _ \\ \n");
  printf("  / _ \\ | |_) | |    | || ' /  / _ \\ \\___ \\| |  | ' /  / _ \\ \\___ \\| || |_) |\n");
  printf(" / ___ \\|  __/| |___ | || . \\ / ___ \\ ___) | |  | . \\ / ___ \\ ___) | ||  _ < \n");
  printf("/_/   \\_|_|   |_____|___|_|\\_/_/   \\_|____|___| |_|\\_/   \\_|____|___|_| \\_\\\n");
  printf("\n");
}

int main()
{
  // Daftar barang yang tersedia
  struct Barang daftarBarang[] = {
      {"BRG001", "Beras", 10000},
      {"BRG002", "Gula", 15000},
      {"BRG003", "Minyak", 20000},
      {"BRG004", "Telur", 25000},
      {"BRG005", "Susu", 30000},
      {"BRG006", "Rokok", 32000},
      {"BRG007", "Shampo", 12000},
      {"BRG008", "Sabun", 7000},
      {"BRG009", "Pasta Gigi", 9000},
      {"BRG010", "Sikat", 14000},
      {"BRG011", "Minuman", 30000},
      {"BRG012", "Jamu", 30000}};

  struct Pembelian daftarPembelian[100]; // Menyimpan barang yang dibeli
  int indexPembelian = 0;                // Indeks untuk daftar barang yang dibeli

  int jumlahBarang = sizeof(daftarBarang) / sizeof(daftarBarang[0]);
  char kodeInput[10];
  int totalHarga = 0;

  // Tampilkan tulisan "APLIKASI KASIR" dalam layar
  headerAplikasi();

  printf("=== Sistem Kasir Sederhana ===\n");
  while (1)
  {
    printf("\nMasukkan kode barang (atau ketik 'selesai' untuk menyelesaikan transaksi): ");
    scanf("%s", kodeInput);

    // Jika user memasukkan "selesai", program berhenti
    if (strcmp(kodeInput, "selesai") == 0)
    {
      break;
    }

    // Mencari barang berdasarkan kode
    int barangDitemukan = 0;
    for (int i = 0; i < jumlahBarang; i++)
    {
      if (strcmp(kodeInput, daftarBarang[i].kode) == 0)
      {
        printf("Barang ditemukan: %s - Harga: Rp%d\n", daftarBarang[i].nama, daftarBarang[i].harga);

        // Meminta input jumlah barang
        int jumlah;
        printf("Masukkan jumlah barang yang dibeli: ");
        scanf("%d", &jumlah);

        // Tambahkan harga total berdasarkan jumlah barang
        totalHarga += daftarBarang[i].harga * jumlah;
        barangDitemukan = 1;

        // Tambahkan barang ke daftar pembelian
        strcpy(daftarPembelian[indexPembelian].nama, daftarBarang[i].nama);
        daftarPembelian[indexPembelian].harga = daftarBarang[i].harga;
        daftarPembelian[indexPembelian].jumlah = jumlah;
        indexPembelian++;
        break;
      }
    }

    if (!barangDitemukan)
    {
      printf("Barang dengan kode %s tidak ditemukan.\n", kodeInput);
    }
  }

  // Tampilkan daftar barang yang dibeli dan total harga dalam format invoice yang rapi
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

  return 0;
}
