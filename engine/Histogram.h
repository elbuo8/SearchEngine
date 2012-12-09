//
//  Histogram.h
//  
//
//  Created by Yamil Asusta on 10/29/12.
//
//

#ifndef ____Histogram__
#define ____Histogram__

#include <iostream>
#include <string>
#include <tr1/unordered_map>
#include <list>
#include "Book.h"

using namespace std;

/*
This class keeps a history of the files in which a word appears.
And there is a total of occurences per file which is also stored.
*/

class Histogram {
private:
    int totalRepetitions;
    tr1::unordered_map<string, int> reverseIndex;
    
public:
    //Empty constructor
    Histogram();
    //Default constructor
    Histogram(const string& index);
    //Methods
    void add(const string& bookTitle);
    void add(const string& bookTitle, const int& total);
    //Getters
    int getTotalRepetitions() const;
    tr1::unordered_map<string, int> getReverseIndex() const;
    list<Book> toList();
    
};

//Helper functions 
Histogram getIntersection(tr1::unordered_map<string, int> histogram1, tr1::unordered_map<string, int> histogram2);
Histogram getUnion(tr1::unordered_map<string, int> histogram1, tr1::unordered_map<string, int> histogram2);

#endif /* defined(____Histogram__) */
