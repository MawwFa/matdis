#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

// Fungsi membersihkan layar agar jalan di HP (Android/Linux) maupun Laptop (Windows)
void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H";
#endif
}

// Ubah teks ke huruf kecil semua untuk pengecekan kata "selesai"
string keHurufKecil(string teks) {
    for (int i = 0; i < (int)teks.length(); i++) {
        teks[i] = tolower(teks[i]);
    }
    return teks;
}

// Mencari posisi indeks anggota di dalam himpunan
int cariIndeks(const vector<string>& himpunan, const string& target) {
    for (int i = 0; i < (int)himpunan.size(); i++) {
        if (himpunan[i] == target) {
            return i;
        }
    }
    return -1;
}

// Menampilkan header judul & informasi himpunan yang terus ter-update
void tampilkanHeader(const string& namaHimpunan, const vector<string>& anggota, bool tampilkanAnggota) {
    cout << "==========================================\n";
    cout << "    STUDI KASUS: CEK SIFAT-SIFAT RELASI   \n";
    cout << "==========================================\n";

    if (!namaHimpunan.empty() && !tampilkanAnggota) {
        cout << "Nama Himpunan : " << namaHimpunan << "\n";
        cout << "------------------------------------------\n";
    } else if (tampilkanAnggota) {
        cout << namaHimpunan << " = { ";
        for (int i = 0; i < (int)anggota.size(); i++) {
            cout << anggota[i] << (i < (int)anggota.size() - 1 ? ", " : "");
        }
        cout << " }\n";
        cout << "------------------------------------------\n";
    }
}

void studiKasusRelasi() {
    string namaHimpunan = "";
    vector<string> anggota;

    // TAHAP 1: INPUT NAMA HIMPUNAN
    bersihkanLayar();
    tampilkanHeader("", anggota, false);
    cout << "PANDUAN:\n";
    cout << "1. Isi nama himpunan & anggotanya.\n";
    cout << "2. Ketik 'selesai' jika daftar cukup.\n";
    cout << "3. Isi relasi: anggota1 anggota2\n";
    cout << "------------------------------------------\n";
    cout << "Nama himpunan (cth: Kebun Binatang):\n> ";
    getline(cin >> ws, namaHimpunan);

    // TAHAP 2: UPDATE LAYAR -> INPUT ANGGOTA HIMPUNAN
    bersihkanLayar();
    tampilkanHeader(namaHimpunan, anggota, false);
    cout << "INPUT ANGGOTA HIMPUNAN:\n";
    cout << "Ketik satu per satu (bisa pakai spasi).\n";
    cout << "Ketik 'selesai' jika sudah (min. 2).\n\n";

    while (true) {
        string item;
        cout << "Anggota ke-" << (anggota.size() + 1) << " > ";
        getline(cin >> ws, item);

        if (keHurufKecil(item) == "selesai") {
            if (anggota.size() < 2) {
                cout << "  ! Minimal masukkan 2 anggota dulu.\n";
                continue;
            }
            break;
        }

        if (cariIndeks(anggota, item) != -1) {
            cout << "  ! '" << item << "' sudah ada.\n";
        } else {
            anggota.push_back(item);
        }
    }

    int N = anggota.size();
    vector<vector<int>> matriks(N, vector<int>(N, 0));

    // TAHAP 3: UPDATE LAYAR -> INPUT PASANGAN RELASI (PAKAI SPASI)
    bersihkanLayar();
    tampilkanHeader(namaHimpunan, anggota, true);
    cout << "INPUT PASANGAN RELASI R:\n";
    cout << "Format: " << anggota[0] << " " << anggota[1] << "\n";
    cout << "Ketik 'selesai' jika sudah cukup.\n\n";

    int nomorRelasi = 1;
    while (true) {
        string baris;
        cout << "Relasi ke-" << nomorRelasi << " > ";
        getline(cin >> ws, baris);

        if (keHurufKecil(baris) == "selesai") {
            break;
        }

        // Mencocokkan "anggota1 anggota2" yang dipisahkan spasi
        int idxAsal = -1;
        int idxTujuan = -1;

        for (int i = 0; i < N; i++) {
            string prefix = anggota[i] + " ";
            if (baris.length() > prefix.length() && baris.substr(0, prefix.length()) == prefix) {
                string sisa = baris.substr(prefix.length());
                int j = cariIndeks(anggota, sisa);
                if (j != -1) {
                    idxAsal = i;
                    idxTujuan = j;
                    break;
                }
            }
        }

        if (idxAsal == -1 || idxTujuan == -1) {
            cout << "  ! Tidak valid. Pisahkan dengan spasi\n";
            cout << "    (cth: " << anggota[0] << " " << anggota[1] << ")\n";
        } else {
            matriks[idxAsal][idxTujuan] = 1;
            nomorRelasi++;
        }
    }

    // TAHAP 4: UPDATE LAYAR -> HASIL ANALISIS AKHIR
    bersihkanLayar();
    tampilkanHeader(namaHimpunan, anggota, true);

    cout << "Relasi R = { ";
    bool pertama = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriks[i][j] == 1) {
                if (!pertama) cout << ", ";
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
    for (int j = 0; j < N; j++) cout << j + 1 << "  ";
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << "  " << i + 1 << " [";
        for (int j = 0; j < N; j++) {
            cout << matriks[i][j] << (j < N - 1 ? "  " : "");
        }
        cout << "]\n";
    }

    // Pengecekan 3 Sifat Relasi
    bool refleksif = true;
    bool setangkup = true;
    bool menghantar = true;

    for (int i = 0; i < N; i++) {
        if (matriks[i][i] != 1) refleksif = false;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriks[i][j] != matriks[j][i]) setangkup = false;
        }
    }

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
    cout << "  1. Refleksif              : " << (refleksif  ? "YA" : "TIDAK") << "\n";
    cout << "  2. Setangkup (Simetris)   : " << (setangkup  ? "YA" : "TIDAK") << "\n";
    cout << "  3. Menghantar (Transitif) : " << (menghantar ? "YA" : "TIDAK") << "\n";
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
    