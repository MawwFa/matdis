#include <iostream>
#include <string>
using namespace std;

void bersihkanLayar() {
    system("CLS");
}
  
int linearSearch(string anggota[], int N, string target) {
    int posisi = -1;

    for (int i = 0; i < N; i++) {
        if (anggota[i] == target) {
            posisi = i;
            break;
        }
    }

    return posisi;
}

void tampilkanHeader(string namaHimpunan, string anggota[], int N, bool tampilkanAnggota) {
    cout << "==========================================\n";
    cout << "    STUDI KASUS: CEK SIFAT-SIFAT RELASI   \n";
    cout << "==========================================\n";

    if (namaHimpunan != "" && tampilkanAnggota == false) {
        cout << "Nama Himpunan : " << namaHimpunan << "\n";
        cout << "------------------------------------------\n";
    } else if (tampilkanAnggota == true) {
        cout << namaHimpunan << " = { ";
        for (int i = 0; i < N; i++) {
            cout << anggota[i];
            if (i < N - 1) {
                cout << ", ";
            }
        }
        cout << " }\n";
        cout << "------------------------------------------\n";
    }
}

void studiKasusRelasi() {
    string namaHimpunan = "";
    string anggota[100];
    int N = 0;

    // TAHAP 1: INPUT NAMA HIMPUNAN
    bersihkanLayar();
    tampilkanHeader("", anggota, N, false);
    cout << "PANDUAN:\n";
    cout << "1. Isi nama himpunan & anggotanya.\n";
    cout << "2. Ketik 'selesai' jika daftar cukup.\n";
    cout << "3. Isi relasi berpasangan (Anggota 1 -> Anggota 2).\n";
    cout << "------------------------------------------\n";
    cout << "Nama himpunan (cth: Kebun Binatang):\n> ";
    getline(cin >> ws, namaHimpunan);

    // TAHAP 2: INPUT ANGGOTA HIMPUNAN KE ARRAY 1D
    bersihkanLayar();
    tampilkanHeader(namaHimpunan, anggota, N, false);
    cout << "INPUT ANGGOTA HIMPUNAN:\n";
    cout << "Ketik satu per satu (boleh pakai spasi).\n";
    cout << "Ketik 'selesai' jika sudah (minimal 2 anggota).\n\n";

    while (true) {
        string item;
        cout << "Anggota ke-" << (N + 1) << " > ";
        getline(cin >> ws, item);

        if (item == "selesai" || item == "SELESAI") {
            if (N < 2) {
                cout << "  ! Minimal masukkan 2 anggota dulu.\n";
                continue;
            }
            break;
        }

        // Cek duplikat menggunakan Linear Search
        if (linearSearch(anggota, N, item) != -1) {
            cout << "  ! '" << item << "' sudah ada.\n";
        } else {
            anggota[N] = item;
            N++;
        }
    }

    // Siapkan Array 2D untuk Matriks Relasi dan isi awal dengan 0
    int matriks[100][100];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriks[i][j] = 0;
        }
    }

    // TAHAP 3: INPUT PASANGAN RELASI R
    bersihkanLayar();
    tampilkanHeader(namaHimpunan, anggota, N, true);
    cout << "INPUT PASANGAN RELASI R:\n";
    cout << "Ketik 'selesai' pada Anggota 1 jika sudah cukup.\n\n";

    int nomorRelasi = 1;
    while (true) {
        string asal, tujuan;
        cout << "Relasi ke-" << nomorRelasi << ":\n";
        cout << "  Anggota 1 : ";
        getline(cin >> ws, asal);

        if (asal == "selesai" || asal == "SELESAI") {
            break;
        }

        cout << "  Anggota 2 : ";
        getline(cin >> ws, tujuan);

        // Cari posisi indeks anggota menggunakan Linear Search
        int idxAsal = linearSearch(anggota, N, asal);
        int idxTujuan = linearSearch(anggota, N, tujuan);

        if (idxAsal == -1 || idxTujuan == -1) {
            cout << "  ! Nama anggota tidak ditemukan di himpunan.\n\n";
        } else {
            matriks[idxAsal][idxTujuan] = 1;
            nomorRelasi++;
            cout << "\n";
        }
    }

    // TAHAP 4: TAMPILKAN HASIL & ANALISIS SIFAT RELASI
    bersihkanLayar();
    tampilkanHeader(namaHimpunan, anggota, N, true);

    cout << "Relasi R = { ";
    bool pertama = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriks[i][j] == 1) {
                if (pertama == false) {
                    cout << ", ";
                }
                cout << "(" << anggota[i] << "," << anggota[j] << ")";
                pertama = false;
            }
        }
    }
    cout << " }\n\n";

    cout << "Keterangan Indeks Matriks:\n";
    for (int i = 0; i < N; i++) {
        cout << "  [" << i + 1 << "] = " << anggota[i] << "\n";
    }

    cout << "\nMatriks Relasi:\n     ";
    for (int j = 0; j < N; j++) {
        cout << j + 1 << "  ";
    }
    cout << "\n";

    for (int i = 0; i < N; i++) {
        cout << "  " << i + 1 << " [";
        for (int j = 0; j < N; j++) {
            cout << matriks[i][j];
            if (j < N - 1) {
                cout << "  ";
            }
        }
        cout << "]\n";
    }

    // Pengecekan 3 Sifat Relasi
    bool refleksif = true;
    bool setangkup = true;
    bool menghantar = true;

    // 1. Cek Refleksif (diagonal utama harus 1 semua)
    for (int i = 0; i < N; i++) {
        if (matriks[i][i] != 1) {
            refleksif = false;
        }
    }

    // 2. Cek Setangkup / Simetris (baris i kolom j harus sama dengan baris j kolom i)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriks[i][j] != matriks[j][i]) {
                setangkup = false;
            }
        }
    }

    // 3. Cek Menghantar / Transitif (jika (i,j)=1 dan (j,k)=1, maka (i,k) harus 1)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (matriks[i][j] == 1 && matriks[j][k] == 1 && matriks[i][k] != 1) {
                    menghantar = false;
                }
            }
        }
    }

    cout << "\n------------------------------------------\n";
    cout << "HASIL CEK SIFAT RELASI:\n";

    cout << "  1. Refleksif              : ";
    if (refleksif == true) {
        cout << "YA\n";
    } else {
        cout << "TIDAK\n";
    }

    cout << "  2. Setangkup (Simetris)   : ";
    if (setangkup == true) {
        cout << "YA\n";
    } else {
        cout << "TIDAK\n";
    }

    cout << "  3. Menghantar (Transitif) : ";
    if (menghantar == true) {
        cout << "YA\n";
    } else {
        cout << "TIDAK\n";
    }

    cout << "==========================================\n";
}

int main() {
    char ulangi;

    do {
        studiKasusRelasi();
        cout << "\nCek himpunan relasi lain? (y/n): ";
        cin >> ulangi;
    } while (ulangi == 'y' || ulangi == 'Y');

    return 0;
}