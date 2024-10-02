# Sistem Kasir Sederhana

Program ini adalah aplikasi kasir sederhana yang memungkinkan pengguna untuk melakukan pembelian barang dan mendapatkan invoice (nota) pembelian. Program ini ditulis menggunakan bahasa C.

## Fitur

1. Daftar barang yang tersedia dalam sistem dengan kode unik, nama, dan harga.
2. Pengguna dapat memasukkan kode barang dan jumlah yang dibeli.
3. Program akan menampilkan daftar barang yang dibeli beserta total harga dalam format invoice.
4. Jika pengguna selesai berbelanja, mereka dapat mengetik `selesai` untuk menampilkan invoice dan menyelesaikan transaksi.

## Struktur Data

- `struct Barang`: Menyimpan informasi barang, seperti kode, nama, dan harga.
- `struct Pembelian`: Menyimpan informasi barang yang dibeli, seperti nama, harga, dan jumlah yang dibeli.

## Cara Penggunaan

### Prasyarat

Pastikan kamu memiliki compiler C seperti `gcc` yang sudah terinstall pada sistem kamu.

### Langkah-langkah

1. Clone atau unduh program ini ke dalam komputer.
2. Buka terminal atau command prompt.
3. Kompilasi program menggunakan perintah berikut:

   ```bash
   gcc -o main main.c
   ```

4. Jalankan program menggunakan perintah:

   ```bash
   ./main
   ```

### Alur Penggunaan

1. Setelah menjalankan program, kamu akan melihat tampilan judul **Sistem Kasir**.
2. Masukkan **kode barang** yang ingin dibeli dari daftar barang yang tersedia. Daftar barang yang tersedia adalah sebagai berikut:
   - `BRG001` : Beras
   - `BRG002` : Gula
   - `BRG003` : Minyak
   - `BRG004` : Telur
   - `BRG005` : Susu
   - `BRG006` : Rokok
   - `BRG007` : Shampo
   - `BRG008` : Sabun
   - `BRG009` : Pasta Gigi
   - `BRG010` : Sikat
   - `BRG011` : Minuman
   - `BRG012` : Jamu

3. Setelah memasukkan kode barang, masukkan **jumlah barang** yang ingin dibeli.
4. Lanjutkan memasukkan kode barang berikutnya jika ingin membeli lebih banyak barang.
5. Jika sudah selesai berbelanja, ketik `selesai` untuk menyelesaikan transaksi.
6. Program akan menampilkan **invoice** yang berisi daftar barang yang dibeli beserta total harga.

### Contoh Penggunaan

Berikut adalah contoh penggunaan:

```
=== Sistem Kasir Sederhana ===

Masukkan kode barang (atau ketik 'selesai' untuk menyelesaikan transaksi): BRG001
Barang ditemukan: Beras - Harga: Rp10000
Masukkan jumlah barang yang dibeli: 2

Masukkan kode barang (atau ketik 'selesai' untuk menyelesaikan transaksi): BRG003
Barang ditemukan: Minyak - Harga: Rp20000
Masukkan jumlah barang yang dibeli: 1

Masukkan kode barang (atau ketik 'selesai' untuk menyelesaikan transaksi): selesai

===================================
            INVOICE PEMBELIAN
===================================
No  Nama Barang         Jumlah    Total     
-----------------------------------
1   Beras               2         Rp20000    
2   Minyak              1         Rp20000    
-----------------------------------
Total Belanja                      Rp40000    
===================================
Terima kasih telah berbelanja!
```

## Lisensi

Program ini dibuat untuk tujuan pembelajaran dan uts 