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

Engine::Engine() {
    stopWords = buildStopWords();
}

void Engine::addToEngine(const string& word, const string& file) {
    if (stopWords.find(word) == stopWords.end() && !word.empty()) {
        //If found, increase counter
        if (find(word) != end())
            find(word)->second.add(file);
        else  //If not found, add the word
            insert(pair<string, Histogram>(word, Histogram(file)));
    }
}


list<Book> Engine::search(const vector<string>& words) {
    Histogram intersection = find(words[0])->second;
	for (int i = 1; i < words.size(); i++)
        intersection = getIntersection(intersection.getReverseIndex(), find(words[i])->second.getReverseIndex());
	return intersection.toList();
}


//Build stopWords map.
tr1::unordered_map<string, int> Engine::buildStopWords() {
    ifstream stopFile("../stopwords.txt");
    tr1::unordered_map<string, int> stopWords;
    //cout << "Building the stopwatch list."<<endl;
    do {
        string parse;
        stopFile >> parse;
        stopWords[parse] = 1;
    } while (!stopFile.eof());
    
    stopFile.close();
    
    //cout << "Done building the stopwatch list."<<endl;
    return stopWords;
}

Engine merge(Engine& engine1, Engine& engine2) {
    Engine engine;
	for (Engine::iterator index = engine1.begin(); index != engine1.end(); index++) 
        if(engine2.find(index->first) != engine2.end()) 
            engine.insert(pair<string, Histogram>(index->first, getUnion(index->second.getReverseIndex(), engine2.find(index->first)->second.getReverseIndex())));
    
    for(Engine::iterator index = engine.begin(); index != engine.end(); index++) {
        engine1.erase(index->first);
        engine2.erase(index->first);        
    }

    engine.insert(engine1.begin(), engine1.end());
    engine.insert(engine2.begin(), engine2.end());
    
    return engine;
}