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

//Default constructor
Book::Book(const string& title) {
    this->Title = title;
    repetitions = 1;
}

//Constructor with setter
Book::Book(const string& title, const int& repetitions) {
    this->Title = title;
    this->repetitions = repetitions;
}

//Increase total repetitions
void Book::increase() {
    repetitions++;
}

//Get total repetitions
int Book::getRepetitions() const {
    return repetitions;
}

//Get the movie title
string Book::getTitle() const {
    return Title;
}

//Helper method to compare relevance of movies
bool bookSort(const Book& book1, const Book& book2) {
    return book1.getRepetitions() > book2.getRepetitions();
}