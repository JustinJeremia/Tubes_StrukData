#include "header.h"
#include <iostream>

void push(Stack*& stack, char operation, const string& content, int lineNumber, int position) {
    Stack* newNode = new Stack;
    newNode->operation = operation;
    newNode->content = content;
    newNode->lineNumber = lineNumber;
    newNode->position = position;
    newNode->next = stack;
    stack = newNode;
}

bool pop(Stack*& stack, char& operation, string& content, int& lineNumber, int& position) {
    if (stack == nullptr) return false;
    Stack* temp = stack;
    operation = stack->operation;
    content = stack->content;
    lineNumber = stack->lineNumber;
    position = stack->position;
    stack = stack->next;
    delete temp;
    return true;
}

void tambahBaris(LineNode*& lines) {
    LineNode* newLine = new LineNode;
    newLine->words = nullptr;
    newLine->next = nullptr;

    if (!lines) {
        lines = newLine;
    } else {
        LineNode* temp = lines;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newLine;
    }
}

void tambahKata(LineNode* line, const string& word, int& position) {
    if (!line) return;

    WordNode* tail = line->words;
    position = 0;
    if (tail) {
        while (tail->next) {
            tail = tail->next;
            position++;
        }
        WordNode* spaceNode = new WordNode;
        spaceNode->letter = ' ';
        spaceNode->next = nullptr;
        tail->next = spaceNode;
        tail = spaceNode;
        position++;
    }

    for (char c : word) {
        WordNode* newWord = new WordNode;
        newWord->letter = c;
        newWord->next = nullptr;
        if (!line->words) {
            line->words = newWord;
        } else {
            tail->next = newWord;
        }
        tail = newWord;
        position++;
    }
}

void hapusKata(LineNode* line, int position, int length) {
    if (!line || !line->words) return;

    WordNode* prev = nullptr;
    WordNode* current = line->words;

    for (int i = 0; i < position && current; i++) {
        prev = current;
        current = current->next;
    }

    for (int i = 0; i < length && current; i++) {
        WordNode* temp = current;
        current = current->next;
        delete temp;
    }

    if (prev) {
        prev->next = current;
    } else {
        line->words = current;
    }
}

void hapusBaris(LineNode*& lines, int lineNumber) {
    if (!lines) {
        cout << "Teks kosong, tidak ada baris untuk dihapus." << endl;
        return;
    }

    LineNode* prev = nullptr;
    LineNode* current = lines;

    for (int i = 1; i < lineNumber && current; i++) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        cout << "Baris ke-" << lineNumber << " tidak ditemukan." << endl;
        return;
    }

    if (prev) {
        prev->next = current->next;
    } else {
        lines = current->next;
    }
    WordNode* word = current->words;
    while (word) {
        WordNode* temp = word;
        word = word->next;
        delete temp;
    }

    delete current;
    cout << "Baris ke-" << lineNumber << " berhasil dihapus." << endl;
}

void cetakTeks(LineNode* lines) {
    LineNode* currentLine = lines;
    int lineNumber = 1;
    while (currentLine) {
        cout << lineNumber << ": ";
        WordNode* currentWord = currentLine->words;
        while (currentWord) {
            cout << currentWord->letter;
            currentWord = currentWord->next;
        }
        cout << endl;
        currentLine = currentLine->next;
        lineNumber++;
    }
}

void cariKata(LineNode* lines, const string& target) {
    LineNode* currentLine = lines;
    int lineNumber = 1;
    bool found = false;

    int targetLength = target.length();

    while (currentLine) {
        WordNode* currentWord = currentLine->words;
        int position = 0;
        int matchIndex = 0;

        while (currentWord) {
            if (currentWord->letter == target[matchIndex]) {
                matchIndex++;
                if (matchIndex == targetLength) {
                    cout << "Kata '" << target << "' ditemukan pada baris " << lineNumber
                         << ", posisi " << position - targetLength + 1 << "." << endl;
                    found = true;
                    matchIndex = 0;
                }
            } else {
                matchIndex = 0;
            }

            currentWord = currentWord->next;
            position++;
        }

        currentLine = currentLine->next;
        lineNumber++;
    }

    if (!found) {
        cout << "Kata '" << target << "' tidak ditemukan dalam teks." << endl;
    }
}

void undo(LineNode* lines, Stack*& undoStack, Stack*& redoStack) {
    char operation;
    string content;
    int lineNumber, position;

    if (!pop(undoStack, operation, content, lineNumber, position)) {
        cout << "Tidak ada yang bisa di-undo!" << endl;
        return;
    }

    LineNode* currentLine = lines;
    for (int i = 1; i < lineNumber && currentLine; i++) {
        currentLine = currentLine->next;
    }

    if (currentLine && operation == 'A') {
        hapusKata(currentLine, position - content.length() + 1, content.length());
        push(redoStack, 'A', content, lineNumber, position);
    } else if (currentLine && operation == 'H') {
        int newPosition;
        tambahKata(currentLine, content, newPosition);
        push(redoStack, 'H', content, lineNumber, newPosition);
    }
}

void redo(LineNode* lines, Stack*& undoStack, Stack*& redoStack) {
    char operation;
    string content;
    int lineNumber, position;

    if (!pop(redoStack, operation, content, lineNumber, position)) {
        cout << "Tidak ada yang bisa di-redo!" << endl;
        return;
    }

    LineNode* currentLine = lines;
    for (int i = 1; i < lineNumber && currentLine; i++) {
        currentLine = currentLine->next;
    }

    if (currentLine && operation == 'A') {
        int newPosition;
        tambahKata(currentLine, content, newPosition);
        push(undoStack, 'A', content, lineNumber, newPosition);
    } else if (currentLine && operation == 'H') {
        hapusKata(currentLine, position, content.length());
        push(undoStack, 'H', content, lineNumber, position);
    }
}
