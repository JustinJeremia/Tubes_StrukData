#include <iostream>

#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

using namespace std;

struct WordNode {
    char letter;
    WordNode* next;
};

struct LineNode {
    WordNode* words;
    LineNode* next;
};

struct Stack {
    char operation;
    string content;
    int lineNumber;
    int position;
    Stack* next;
};

void push(Stack*& stack, char operation, const string& content, int lineNumber, int position);
bool pop(Stack*& stack, char& operation, string& content, int& lineNumber, int& position);
void tambahBaris(LineNode*& lines);
void tambahKata(LineNode* line, const string& word, int& position);
void hapusKata(LineNode* line, int position, int length);
void hapusBaris(LineNode*& lines, int lineNumber);
void cetakTeks(LineNode* lines);
void cariKata(LineNode* lines, const string& target);
void undo(LineNode* lines, Stack*& undoStack, Stack*& redoStack);
void redo(LineNode* lines, Stack*& undoStack, Stack*& redoStack);


#endif // HEADER_H_INCLUDED
