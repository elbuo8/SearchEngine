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
#include <list>
#include "Book.h"
#include <string>

using namespace std;

class Histogram {
private:
    int totalRepetitions;
    list<Book> books;
    
public:
    Histogram(const string& book);
    Histogram();
    void addBook(const string& book);
    bool findAndAdd(const string& bookTitle);
    int getTotalRepetitions() const;
    
};

#endif /* defined(____Histogram__) */
