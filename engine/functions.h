//
//  functions.h
//  
//
//  Created by Yamil Asusta on 11/1/12.
//	Set of helper functions.
//

#ifndef _functions_h
#define _functions_h

#include <tr1/unordered_map>
#include <fstream>
#include <locale>

using namespace std;

//Build stopWords map.
tr1::unordered_map<string, int> buildStopWords() {
    ifstream stopFile("../stopwords.txt");
    tr1::unordered_map<string, int> stopWords;
    cout << "Building the stopwatch list."<<endl;
    do {
        string parse;
        stopFile >> parse;
        stopWords[parse] = 1;
    } while (!stopFile.eof());
    
    stopFile.close();
    
    cout << "Done building the stopwatch list."<<endl;
    return stopWords;
}

//Sanitize words.
void sanitize(string& word) {
    locale filter;
    for (int k = 0; k < word.length(); k++) {
        word[k] = tolower(word[k], filter);
        if(!isalpha(word[k], filter)) {
            if(word[k] == '\'') word.erase(k);
            else word.erase(k--,1);
        }
    }
}



#endif
