//
//  Histogram.cpp
//  
//
//  Created by Yamil Asusta on 10/29/12.
//
//

#include "Histogram.h"
#include <string>
#include <tr1/unordered_map>
#include "Book.h"

using namespace std;

Histogram::Histogram() {
    totalRepetitions = 0;
}

Histogram::Histogram(const string& book) {
    totalRepetitions = 1;
    reverseIndex[book] = 1;
}

tr1::unordered_map<string, int> Histogram::getHistogram() const {
    return reverseIndex;
}

int Histogram::getTotalRepetitions() const {
    return totalRepetitions;
}

void Histogram::add(const string& bookTitle) {
	totalRepetitions++;
	reverseIndex[bookTitle] += 1;
}

list<Book> getIntersection(tr1::unordered_map<string, int> histogram1, tr1::unordered_map<string, int> histogram2) {
    list<Book> intersection;
    tr1::unordered_map<string, int>::iterator mapIndex;
    for (mapIndex = histogram1.begin(); mapIndex != histogram1.end(); mapIndex++) {
        if(histogram2.find(mapIndex->first) != histogram2.end()) {
            intersection.push_back(Book(mapIndex->first, mapIndex->second + histogram2[mapIndex->first]));
        }
    }
    return intersection;
    
}

list<Book> Histogram::toList() {
    list<Book> books;
    for (tr1::unordered_map<string, int>::iterator mapIndex = reverseIndex.begin(); mapIndex != reverseIndex.end(); mapIndex++) {
        books.push_back(Book(mapIndex->first, mapIndex->second));
    }
    return books;
}