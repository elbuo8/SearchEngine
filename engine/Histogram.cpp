//
//  Histogram.cpp
//  
//
//  Created by Yamil Asusta on 10/29/12.
//
//

#include "Histogram.h"
#include <string>

using namespace std;

Histogram::Histogram() {
    totalRepetitions = 0;
}

Histogram::Histogram(const string& book) {
    totalRepetitions = 1;
    reverseIndex[book] = 1;
}

int Histogram::getTotalRepetitions() const {
    return totalRepetitions;
}

void Histogram::add(const string& bookTitle) {
	totalRepetitions++;
	reverseIndex[bookTitle] = 1;
}