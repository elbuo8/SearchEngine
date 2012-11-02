//
//  functions.h
//  
//
//  Created by Yamil Asusta on 11/1/12.
//	Set of helper functions.
//

#ifndef _functions_h
#define _functions_h

#include <locale>
#include "Engine.h"
#include <vector>
#include <pthread.h>

using namespace std;


//Sanitize words.
string sanitize(string& word) {
    locale filter; 
    for (int k = 0; k < word.length(); k++) {
        word[k] = tolower(word[k], filter);
        if(!isalpha(word[k], filter)) {
            if(word[k] == '\'') word.erase(k);
            else word.erase(k--,1);
        }
    }
    return word;
}

vector<string> getSearchableWords(vector<string> words, const Engine& engine) {
    for (int i = 0; i < words.size(); i++) 
        if (engine.find(words[i]) == engine.end()) 
            words.erase(words.begin() + i--);
    return words;
}

struct HalfEngine {
    vector<string> files;
    string dir;
    int start;
    int finish;
    Engine engine;
};


void *halfEgineBuilder(void *values) {
    struct HalfEngine *data = (struct HalfEngine *) values;
    
    for (int i = data->start; i < data->finish; i++) {
        if (data->files[i].c_str()[0]!='.') { //Avoid hidden files.
            vector<string> words = ParsedFile(data->dir + data->files[i]).readAndTokenize(); //Get all words
            for (int j = 0; j < words.size(); j++)
                data->engine.addToEngine(sanitize(words[j]), data->files[i]); //Sanitize removes capital letters, an non alpha chars
        }
    }
    pthread_exit((void *) data);
}
/*
Engine buildEngine(string& dir, vector<string> files) {
    
}
*/


#endif
