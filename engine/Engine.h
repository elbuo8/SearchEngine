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

/*
The engine class extends the unordered_map class. 
Gives the code more logic and its easier to read.

It's key is a word that could be searched.
It's value is a Histogram of that word per file.
*/

class Engine: public tr1::unordered_map<string, Histogram> {

private:
    tr1::unordered_map<string, int> stopWords; // Engine must keep track of those words that are trivial
    
public:
    //Default constructor
    Engine();
    
    //Methods
    void addToEngine(const string& word, const string& file); // Word and it's containing file to be added to the engine.
    list<Book> search(const vector<string>& words); // Perform a search and obtain a list of top results.
    tr1::unordered_map<string, int> buildStopWords(); // Read the stop words list.
    
};

Engine merge(Engine& engine1, Engine& engine2); // Parallel build helper. 

#endif /* defined(____Engine__) */
