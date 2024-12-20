#include "header.h"
#include <iostream>

using namespace std;

int main() {
    LineNode* lines = nullptr;
    Stack* undoStack = nullptr;
    Stack* redoStack = nullptr;

    int pilihan;

    do {
        cout << "\n--- Editor Teks ---" << endl;
        cout << "1. Tambah Baris" << endl;
        cout << "2. Tambah Kata" << endl;
        cout << "3. Cetak Teks" << endl;
        cout << "4. Cari Kata" << endl;
        cout << "5. Undo" << endl;
        cout << "6. Redo" << endl;
        cout << "7. Hapus Baris" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        if (pilihan == 1) {
            tambahBaris(lines);
            cout << "Baris baru ditambahkan!" << endl;
        } else if (pilihan == 2) {
            int lineNumber;
            string word;
            cout << "Masukkan nomor Baris: ";
            cin >> lineNumber;
            cout << "Masukkan kata yang akan ditambahkan: ";
            cin >> word;

            LineNode* currentLine = lines;
            for (int i = 1; i < lineNumber && currentLine; i++) {
                currentLine = currentLine->next;
            }

            if (currentLine) {
                int position;
                tambahKata(currentLine, word, position);
                push(undoStack, 'A', word, lineNumber, position);
                cout << "Kata '" << word << "' ditambahkan ke Baris " << lineNumber << "!" << endl;
            } else {
                cout << "Baris tidak ditemukan!" << endl;
            }
        } else if (pilihan == 3) {
            cetakTeks(lines);
        } else if (pilihan == 4) {
            string target;
            cout << "Masukkan kata yang ingin dicari: ";
            cin >> target;
            cariKata(lines, target);
        } else if (pilihan == 5) {
            undo(lines, undoStack, redoStack);
        } else if (pilihan == 6) {
            redo(lines, undoStack, redoStack);
        } else if (pilihan == 7) {
            int lineNumber;
            cout << "Masukkan nomor baris yang ingin dihapus: ";
            cin >> lineNumber;
            hapusBaris(lines, lineNumber);
        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);

    cout << "Terima kasih telah menggunakan editor teks." << endl;

    return 0;
}
