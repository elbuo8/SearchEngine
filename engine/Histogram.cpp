//
//  Histogram.cpp
//  
//
//  Created by Yamil Asusta on 10/29/12.
//
//

#include "Histogram.h"
#include "Book.h"
#include <string>

using namespace std;

Histogram::Histogram() {
    totalRepetitions = 0;
}

Histogram::Histogram(const string& book) {
    totalRepetitions = 0;
    addBook(book);
}

int Histogram::getTotalRepetitions() const {
    return totalRepetitions;
}

void Histogram::addBook(const string& book) {
    Book newBook(book);
    books.push_back(newBook);
    totalRepetitions++;
}

bool Histogram::findAndAdd(const string& bookTitle) {
    list<Book>::iterator bookIndex;
    for (bookIndex = books.begin(); bookIndex != books.end(); bookIndex++) {
        if (bookIndex->getTitle() == bookTitle) {
            bookIndex->increase();
            totalRepetitions++;
            return true;
        }
    }
    return false;
}