//
//  Engine.cpp
//  
//
//  Created by Yamil Asusta on 11/1/12.
//
//

#include "Histogram.h"
#include "Engine.h"
#include <tr1/unordered_map>
#include <fstream>
#include <vector>
#include "Book.h"

//Default constructor.
Engine::Engine() {
    stopWords = buildStopWords(); // Get the stopwords from the file.
}

/*
Params: word to be added, file containing the word
Return: void
*/
void Engine::addToEngine(const string& word, const string& file) {
    if (stopWords.find(word) == stopWords.end() && !word.empty()) { //If the word is not a stop word OR a "" string then add it to the engine.
        if (find(word) != end()) //If the word is in the engine, then set the new file.
            find(word)->second.add(file);
        else  //If not found, add the word to the engine with the current file
            insert(pair<string, Histogram>(word, Histogram(file)));
    }
}

/*
Params: list of words to be searched
Return: Sorted linked list of Books(movie representation) that are an intersection with the words
*/
list<Book> Engine::search(const vector<string>& words) {
    Histogram intersection = find(words[0])->second; //Add the first for 1 word searches.
	for (int i = 1; i < words.size(); i++) //If more than one word is being searched, calculate their intersections.
        intersection = getIntersection(intersection.getReverseIndex(), find(words[i])->second.getReverseIndex());
	return intersection.toList();
}


//Build stopWords map.
tr1::unordered_map<string, int> Engine::buildStopWords() {
    ifstream stopFile("../stopwords.txt"); //Literal location
    tr1::unordered_map<string, int> stopWords;
    //cout << "Building the stopwatch list."<<endl;
    do {
        string parse;
        stopFile >> parse;
        stopWords[parse] = 1; // Using a hashmap and setting the value to one is like searching in a Set. Searches will be O(1)
    } while (!stopFile.eof());
    
    stopFile.close();
    
    //cout << "Done building the stopwatch list."<<endl;
    return stopWords;
}

/*
Parallel engine builder.
Params: Two halves of the engine.
Returns: The union of the engines.

*/
Engine merge(Engine& engine1, Engine& engine2) {
    Engine engine;
    //Find the words in common and add the values of their movies.
	for (Engine::iterator index = engine1.begin(); index != engine1.end(); index++) 
        if(engine2.find(index->first) != engine2.end()) 
            engine.insert(pair<string, Histogram>(index->first, getUnion(index->second.getReverseIndex(), engine2.find(index->first)->second.getReverseIndex())));
    
    //Remove the words in common
    for(Engine::iterator index = engine.begin(); index != engine.end(); index++) {
        engine1.erase(index->first);
        engine2.erase(index->first);        
    }
    //Finish inserting the rest of the words
    engine.insert(engine1.begin(), engine1.end());
    engine.insert(engine2.begin(), engine2.end());
    
    return engine;
}