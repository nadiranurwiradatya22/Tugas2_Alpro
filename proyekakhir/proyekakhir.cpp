
#include <iostream>
#include <cstring>
using namespace std;

struct Menu {
    char kode[10];
    char nama[50];
    int harga;
    char kategori[30];
};

struct Transaksi {
    char namaPelanggan[50];
    char kodeMenu[10];
    char namaMenu[50];
    int jumlah;
    int totalHarga;
};

void tambahMenu() {
    Menu m;
    cout << "\nTambah Menu Baru\n";
    cout << "Kode Menu     : "; cin >> m.kode;
    cin.ignore();
    cout << "Nama Menu     : "; cin.getline(m.nama, 50);
    cout << "Harga Menu    : "; cin >> m.harga;
    cin.ignore();
    cout << "Kategori      : "; cin.getline(m.kategori, 30);

    FILE* file = fopen("menu.dat", "ab");
    if (file) {
        fwrite(&m, sizeof(Menu), 1, file);
        fclose(file);
        cout << "Menu berhasil ditambahkan!\n";
    } else {
        cout << "Gagal menyimpan menu.\n";
    }
}

void tampilMenu() {
    Menu m;
    FILE* file = fopen("menu.dat", "rb");
    if (!file) {
        cout << "File menu tidak ditemukan.\n";
        return;
    }

    cout << "\nDaftar Menu\n";
    cout << "Kode\tNama\t\tHarga\tKategori\n";
    cout << "------------------------------------------\n";
    while (fread(&m, sizeof(Menu), 1, file)) {
        cout << m.kode << "\t" << m.nama << "\t\t" << m.harga << "\t" << m.kategori << endl;
    }

    fclose(file);
}

void editMenu() {
    char kode[10];
    cout << "Masukkan kode menu yang akan diedit: ";
    cin >> kode;

    FILE* file = fopen("menu.dat", "rb+");
    if (!file) {
        cout << "File menu tidak ditemukan.\n";
        return;
    }

    Menu m;
    bool found = false;

    while (fread(&m, sizeof(Menu), 1, file)) {
        if (strcmp(m.kode, kode) == 0) {
            cout << "Menu ditemukan. Masukkan data baru:\n";
            cout << "Nama Menu     : "; cin.ignore(); cin.getline(m.nama, 50);
            cout << "Harga Menu    : "; cin >> m.harga;
            cin.ignore();
            cout << "Kategori      : "; cin.getline(m.kategori, 30);

            fseek(file, -sizeof(Menu), SEEK_CUR);
            fwrite(&m, sizeof(Menu), 1, file);
            found = true;
            cout << "Menu berhasil diperbarui!\n";
            break;
        }
    }

    if (!found) {
        cout << "Menu dengan kode tersebut tidak ditemukan.\n";
    }

    fclose(file);
}

void pesanMenu() {
    char kode[10];
    int jumlah;
    char namaPelanggan[50];
    cout << "Nama Pelanggan : "; cin.ignore(); cin.getline(namaPelanggan, 50);
    cout << "Kode Menu      : "; cin >> kode;

    FILE* file = fopen("menu.dat", "rb");
    if (!file) {
        cout << "File menu tidak ditemukan.\n";
        return;
    }

    Menu m;
    bool found = false;
    while (fread(&m, sizeof(Menu), 1, file)) {
        if (strcmp(m.kode, kode) == 0) {
            found = true;
            break;
        }
    }
    fclose(file);

    if (!found) {
        cout << "Menu tidak ditemukan.\n";
        return;
    }

    cout << "Jumlah Pesanan : "; cin >> jumlah;

    Transaksi t;
    strcpy(t.namaPelanggan, namaPelanggan);
    strcpy(t.kodeMenu, m.kode);
    strcpy(t.namaMenu, m.nama);
    t.jumlah = jumlah;
    t.totalHarga = m.harga * jumlah;

    FILE* tf = fopen("transaksi.dat", "ab");
    if (tf) {
        fwrite(&t, sizeof(Transaksi), 1, tf);
        fclose(tf);
        cout << "Pesanan berhasil dicatat!\n";
        cout << "Struk Pembayaran:\n";
        cout << "Pelanggan : " << t.namaPelanggan << endl;
        cout << "Menu      : " << t.namaMenu << endl;
        cout << "Jumlah    : " << t.jumlah << endl;
        cout << "Total     : Rp " << t.totalHarga << endl;
    } else {
        cout << "Gagal menyimpan transaksi.\n";
    }
}

void tampilTransaksi() {
    FILE* file = fopen("transaksi.dat", "rb");
    if (!file) {
        cout << "File transaksi tidak ditemukan.\n";
        return;
    }

    Transaksi t;
    cout << "\nRiwayat Transaksi\n";
    while (fread(&t, sizeof(Transaksi), 1, file)) {
        cout << "Pelanggan : " << t.namaPelanggan
             << " | Menu: " << t.namaMenu
             << " | Jumlah: " << t.jumlah
             << " | Total: Rp " << t.totalHarga << endl;
    }

    fclose(file);
}

void menuUtama() {
    int pilihan;
    do {
        cout << "\nSISTEM MANAJEMEN RESTORAN\n";
        cout << "1. Tambah Menu\n";
        cout << "2. Tampilkan Menu\n";
        cout << "3. Edit Menu\n";
        cout << "4. Pesan Menu\n";
        cout << "5. Lihat Riwayat Transaksi\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahMenu(); break;
            case 2: tampilMenu(); break;
            case 3: editMenu(); break;
            case 4: pesanMenu(); break;
            case 5: tampilTransaksi(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);
}

int main() {
    menuUtama();
    return 0;
}
