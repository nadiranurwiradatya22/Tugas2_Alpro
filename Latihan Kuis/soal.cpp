#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Film {
    string judul;
    string kode;
    float rating;
};

void tampilkanData(vector<Film> &films) {
    for (auto *film = films.data(); film < films.data() + films.size(); film++) {
        cout << "Kode: " << film->kode << " | Judul: " << film->judul << " | Rating: " << film->rating << endl;
    }
}

int sequentialSearch(vector<Film> &films, string kode) {
    for (int i = 0; i < films.size(); i++) {
        if (films[i].kode == kode) return i;
    }
    return -1;
}

int binarySearch(vector<Film> &films, string judul) {
    int left = 0, right = films.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (films[mid].judul == judul) return mid;
        else if (films[mid].judul < judul) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int partition(vector<Film> &films, int low, int high) {
    float pivot = films[high].rating;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (films[j].rating < pivot) {
            i++;
            swap(films[i], films[j]);
        }
    }
    swap(films[i + 1], films[high]);
    return i + 1;
}

void quickSort(vector<Film> &films, int low, int high) {
    if (low < high) {
        int pi = partition(films, low, high);
        quickSort(films, low, pi - 1);
        quickSort(films, pi + 1, high);
    }
}

void bubbleSort(vector<Film> &films) {
    int n = films.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (films[j].rating < films[j + 1].rating) {
                swap(films[j], films[j + 1]);
            }
        }
    }
}

int main() {
    vector<Film> films = {
        {"Interstellar", "F001", 8.6},
        {"Inception", "F002", 8.8},
        {"Avengers", "F003", 8.0},
        {"Titanic", "F004", 7.8},
        {"Joker", "F005", 8.4}
    };
    
    cout << "Data Film Sebelum Sorting:\n";
    tampilkanData(films);
    
    string kodeCari;
    cout << "\nMasukkan kode film yang ingin dicari: ";
    cin >> kodeCari;
    int idxKode = sequentialSearch(films, kodeCari);
    cout << "Film dengan Kode " << kodeCari << (idxKode != -1 ? " ditemukan!" : " tidak ditemukan!") << endl;
    
    quickSort(films, 0, films.size() - 1);
    cout << "\nData Film Setelah Quick Sort (Ascending):\n";
    tampilkanData(films);
    
    bubbleSort(films);
    cout << "\nData Film Setelah Bubble Sort (Descending):\n";
    tampilkanData(films);
    
    string judulCari;
    cout << "\nMasukkan judul film yang ingin dicari: ";
    cin.ignore();
    getline(cin, judulCari);
    
    int idxJudul = binarySearch(films, judulCari);
    cout << "Film dengan Judul '" << judulCari << "'" << (idxJudul != -1 ? " ditemukan!" : " tidak ditemukan!") << endl;
    
    return 0;
}
