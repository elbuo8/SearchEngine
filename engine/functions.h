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



#endif
