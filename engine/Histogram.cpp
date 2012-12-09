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

//Empty constructor
Histogram::Histogram() {
    totalRepetitions = 0;
}

//Default constructor
Histogram::Histogram(const string& book) {
    totalRepetitions = 1;
    reverseIndex[book] = 1;
}

//Get the movies map
tr1::unordered_map<string, int> Histogram::getReverseIndex() const {
    return reverseIndex;
}

//Get total repetitions of a word
int Histogram::getTotalRepetitions() const {
    return totalRepetitions;
}

//Add a new movie to the movies collection
void Histogram::add(const string& bookTitle) {
	totalRepetitions++;
	reverseIndex[bookTitle] += 1;
}

//Add a new movie with an actual value of repetitions
void Histogram::add(const string& bookTitle, const int& total) {
	totalRepetitions += total;
	reverseIndex[bookTitle] = total;
}

//Calculate the intersections between two words
Histogram getIntersection(tr1::unordered_map<string, int> histogram1, tr1::unordered_map<string, int> histogram2) {
    Histogram intersection;
    tr1::unordered_map<string, int>::iterator mapIndex;
    for (mapIndex = histogram1.begin(); mapIndex != histogram1.end(); mapIndex++) 
        if(histogram2.find(mapIndex->first) != histogram2.end()) 
            intersection.add(mapIndex->first, mapIndex->second + histogram2[mapIndex->first]); //If a movie is a match, then add their values
    return intersection;
}

//Build a list of the results
list<Book> Histogram::toList() {
    list<Book> books;
    for (tr1::unordered_map<string, int>::iterator mapIndex = reverseIndex.begin(); mapIndex != reverseIndex.end(); mapIndex++) 
        books.push_back(Book(mapIndex->first, mapIndex->second));
    books.sort(bookSort); //Reverse sort it.
    return books;
}

//Helper method for building the parallel engine. 
Histogram getUnion(tr1::unordered_map<string, int> histogram1, tr1::unordered_map<string, int> histogram2) {
    Histogram histogram;
    for (tr1::unordered_map<string, int>::iterator index = histogram1.begin(); index != histogram1.end(); index++)
        histogram.add(index->first, index->second);
    
    for (tr1::unordered_map<string, int>::iterator index = histogram2.begin(); index != histogram2.end(); index++)
        histogram.add(index->first, index->second);
    
    return histogram;
}