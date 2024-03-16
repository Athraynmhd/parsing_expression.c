# Konversi Notasi Ekspresi

Proyek ini menyediakan implementasi C untuk mengkonversi antar notasi ekspresi matematika: Infix, Postfix, dan Prefix. Program ini memungkinkan pengguna untuk mengkonversi ekspresi dari satu bentuk notasi ke bentuk notasi lainnya, mendukung operasi dasar matematika seperti penjumlahan (+), pengurangan (-), perkalian (*), pembagian (/), dan eksponensial (^).

## Fungsi Utama

- **Infix ke Postfix:** Mengkonversi ekspresi dalam notasi Infix menjadi notasi Postfix.
- **Infix ke Prefix:** Mengkonversi ekspresi dalam notasi Infix menjadi notasi Prefix.
- **Postfix ke Infix:** Mengkonversi ekspresi dalam notasi Postfix kembali menjadi notasi Infix.
- **Postfix ke Prefix:** Mengkonversi ekspresi dalam notasi Postfix menjadi notasi Prefix.
- **Prefix ke Infix:** Mengkonversi ekspresi dalam notasi Prefix kembali menjadi notasi Infix.
- **Prefix ke Postfix:** Mengkonversi ekspresi dalam notasi Prefix menjadi notasi Postfix.

## Cara Penggunaan

1. **Kompilasi Program:**
   Pastikan file kode sumber `parsing_expression_2208107010074.c` berada dalam direktori yang sama. Gunakan perintah kompilasi berikut pada terminal atau command prompt:
   ```
   gcc -o parsing_expression parsing_expression_2208107010074.c
   ```

2. **Menjalankan Program:**
   Setelah berhasil dikompilasi, jalankan program dengan perintah:
   ```
   ./parsing_expression
   ```
   Ikuti petunjuk pada menu untuk melakukan konversi ekspresi.

3. **Memasukkan Ekspresi:**
   Saat diminta, masukkan ekspresi matematika yang ingin dikonversi. Pastikan menggunakan format yang benar sesuai notasi asal ekspresi.

4. **Melihat Hasil Konversi:**
   Program akan menampilkan hasil konversi ekspresi ke notasi tujuan.

## Catatan

- Pastikan ekspresi yang dimasukkan valid dan sesuai dengan notasi asal yang dipilih.
- Program ini tidak mengevaluasi ekspresi matematika, hanya melakukan konversi antar notasi ekspresi.
