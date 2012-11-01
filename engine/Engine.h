//
//  Engine.h
//  
//
//  Created by Yamil Asusta on 11/1/12.
//
//

#ifndef ____Engine__
#define ____Engine__

#include <iostream>
#include <tr1/unordered_map>
#include "Histogram.h"
#include <string>
#include <vector>
#include "Book.h"

class Engine: public tr1::unordered_map<string, Histogram> {
private:
    tr1::unordered_map<string, int> stopWords;
    
public:
    Engine();
    void addToEngine(const string& word, const string& file);
    list<Book> search(const vector<string>& words);
    tr1::unordered_map<string, int> buildStopWords();
    
};


#endif /* defined(____Engine__) */
