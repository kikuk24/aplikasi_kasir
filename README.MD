# Sistem Kasir dengan Analisis Penjualan

Program ini merupakan sistem kasir berbasis teks yang dapat digunakan untuk mengelola barang, mencatat transaksi, dan menganalisis data penjualan.

## Cara Penggunaan

1. **Persiapan File CSV**:
   - Pastikan Anda memiliki file `barang.csv` dengan format berikut:
     ```
     Kode,Nama Barang,Harga Jual,Stok,Harga Beli,Total Terjual
     ```
   - File ini akan dibuat secara otomatis jika tidak ditemukan.

2. **Menjalankan Program**:
   - Kompilasi program menggunakan GCC:
     ```bash
     gcc program.c -o main
     ```
   - Jalankan program:
     ./main
     ```

3. **Navigasi Menu**:
   Setelah program dijalankan, Anda akan melihat menu utama:
   ```
   === Menu Utama ===
   1. Pembeli
   2. Tambah Barang
   3. Tampilkan Barang
   4. Simpan Barang
   5. Analisis
   6. Analisis Barang
   0. Keluar
   ```
   ```
   Masukkan angka sesuai pilihan menu:
   - **1. Pembeli**: Fitur kasir untuk mencatat transaksi.
   - **2. Tambah Barang**: Tambahkan barang baru ke daftar.
   - **3. Tampilkan Barang**: Tampilkan daftar barang yang tersedia.
   - **4. Simpan Barang**: Simpan daftar barang ke file `barang.csv`.
   - **5. Analisis**: Analisis penjualan mingguan, bulanan, tahunan, dan stok barang.
   - **6. Analisis Barang**: Menampilkan barang terlaris dan tidak laris.
   - **0. Keluar**: Keluar dari program.

4. **Fitur Kasir**:
   - Pilih **1. Pembeli** dari menu utama.
   - Masukkan kode barang yang ingin dibeli.
   - Masukkan jumlah barang.
   - Ketik `selesai` untuk menyelesaikan transaksi dan mencetak invoice.

5. **Menyimpan Data**:
   - Setiap transaksi disimpan dalam file `rekap_transaksi.csv`.
   - Stok barang yang diperbarui disimpan kembali ke `barang.csv`.

## Penjelasan Fitur Utama

- **Manajemen Barang**:
  - Data barang dimuat dari file `barang.csv` saat program dijalankan.
  - Barang baru dapat ditambahkan melalui menu **Tambah Barang**.
  - Stok barang diperbarui otomatis setelah transaksi.

- **Fitur Kasir**:
  - Program mencatat setiap pembelian dan menghasilkan invoice.
  - Stok barang otomatis berkurang sesuai jumlah pembelian.

- **Analisis Penjualan**:
  - **Mingguan**: Menampilkan total penjualan dan laba/rugi dalam 7 hari terakhir.
  - **Bulanan**: Menampilkan total penjualan dan laba/rugi pada bulan tertentu.
  - **Tahunan**: Rekap penjualan dan laba/rugi tahunan.

- **Analisis Barang**:
  - **Barang Terlaris**: Barang dengan jumlah penjualan tertinggi.
  - **Barang Tidak Laris**: Barang dengan jumlah penjualan terendah.

## Contoh Output

### Menu Utama
```
=== Menu Utama ===
1. Pembeli
2. Tambah Barang
3. Tampilkan Barang
4. Simpan Barang
5. Analisis
6. Analisis Barang
0. Keluar
Masukkan pilihan: 

### Invoice Pembelian

===================================
            INVOICE PEMBELIAN
===================================
No  Nama Barang          Jumlah    Total     
-----------------------------------
1   Sabun                3         Rp15000   
2   Pasta Gigi           2         Rp20000   
-----------------------------------
Total Belanja                        Rp35000  
===================================
Terima kasih telah berbelanja!
```
## Catatan
- Program ini menggunakan format warna ANSI untuk memberikan tampilan yang lebih menarik di terminal.
- Pastikan Anda menjalankan program di terminal yang mendukung kode warna ANSI.