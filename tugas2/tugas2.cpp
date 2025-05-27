#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Pesanan {
    string namaPembeli;
    string roti;
    double harga;
};

queue<Pesanan> antrian;
vector<Pesanan> sudahDilayani;

void tambahPesanan() {
    Pesanan p;
    cout << "Nama Pembeli: ";
    cin.ignore();
    getline(cin, p.namaPembeli);
    cout << "Jenis Roti: ";
    getline(cin, p.roti);
    cout << "Harga: ";
    cin >> p.harga;

    antrian.push(p);
    cout << ">> Pesanan ditambahkan ke antrian.\n";
}

void prosesPesanan() {
    if (antrian.empty()) {
        cout << ">> Antrian kosong.\n";
        return;
    }

    Pesanan p = antrian.front();
    antrian.pop();
    sudahDilayani.push_back(p);
    cout << ">> Pesanan " << p.namaPembeli << " sudah dilayani.\n";
}

void lihatAntrian() {
    if (antrian.empty()) {
        cout << ">> Tidak ada antrian.\n";
        return;
    }

    cout << "--- Antrian Sekarang ---\n";
    queue<Pesanan> tmp = antrian;
    int no = 1;
    while (!tmp.empty()) {
        Pesanan p = tmp.front();
        cout << no << ". " << p.namaPembeli << " - " << p.roti << " - Rp" << p.harga << "\n";
        tmp.pop();
        no++;
    }
}

void batalkanPesanan() {
    if (antrian.empty()) {
        cout << ">> Tidak ada yang bisa dibatalkan.\n";
        return;
    }

    queue<Pesanan> tempQueue;
    while (antrian.size() > 1) {
        tempQueue.push(antrian.front());
        antrian.pop();
    }

    cout << ">> Pesanan atas nama " << antrian.front().namaPembeli << " dibatalkan.\n";
    antrian.pop();
    antrian = tempQueue;
}

void lihatRiwayat() {
    if (sudahDilayani.empty()) {
        cout << ">> Belum ada pesanan yang selesai.\n";
        return;
    }

    cout << "--- Riwayat Pesanan ---\n";
    for (int i = 0; i < sudahDilayani.size(); i++) {
        cout << i + 1 << ". " << sudahDilayani[i].namaPembeli << " - " << sudahDilayani[i].roti << " - Rp" << sudahDilayani[i].harga << endl;
    }
}

int main() {
    int pilih;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Layani Pesanan\n";
        cout << "3. Lihat Antrian\n";
        cout << "4. Batalkan Pesanan Terakhir\n";
        cout << "5. Lihat Riwayat\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahPesanan(); break;
            case 2: prosesPesanan(); break;
            case 3: lihatAntrian(); break;
            case 4: batalkanPesanan(); break;
            case 5: lihatRiwayat(); break;
            case 0: cout << "Program selesai.\n"; break;
            default: cout << ">> Pilihan tidak ada!\n";
        }

    } while (pilih != 0);

    return 0;
}
