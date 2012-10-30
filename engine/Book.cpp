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

void Book::increase() {
    repetitions++;
}

int Book::getRepetitions() const {
    return repetitions;
}

string Book::getTitle() const {
    return Title;
}