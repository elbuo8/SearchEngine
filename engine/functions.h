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

using namespace std;


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
