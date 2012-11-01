//
//  Book.cpp
//  
//
//  Created by Yamil Asusta on 10/29/12.
//
//

#include "Book.h"
#include <string>

using namespace std;

Book::Book(const string& title) {
    this->Title = title;
    repetitions = 1;
}

Book::Book(const string& title, const int& repetitions) {
    this->Title = title;
    this->repetitions = repetitions;
}


void Book::increase() {
    repetitions++;
}

int Book::getRepetitions() const {
    return repetitions;
}

string Book::getTitle() const {
    return Title;
}

bool bookSort(const Book& book1, const Book& book2) {
    return book1.getRepetitions() > book2.getRepetitions();
}