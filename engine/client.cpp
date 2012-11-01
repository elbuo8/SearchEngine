#include "ParsedFile.h"
#include <iostream>
#include <tr1/unordered_map>
#include "Histogram.h"
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "Book.h"
#include "functions.h"
#include "Engine.h"

using namespace std;


int main() {
    
    //Engine requirements
    string dir = string("../moviesdb/");
    vector<string> files = vector<string>();
    getdir(dir,files); //Anade los files del directorio al vector
    Engine engine;
    
    cout <<endl<<"Start building the search engine."<<endl;
    for (int i = 0; i < files.size(); i++) {
        if (files[i].c_str()[0]!='.') { //Trampa de Arce para evitar hidden files
            vector<string> words = ParsedFile(dir + files[i]).readAndTokenize(); //Get all words
            for (int j = 0; j < words.size(); j++) 
                engine.addToEngine(sanitize(words[j]), files[i]);
        }
    }
    cout<<"Done building search engine."<<endl;
    files.clear();
    
    cout<<endl<<"Submit your words bro! Enter 0 when done."<<endl;
    string parse;
    getline(cin, parse);
    while (parse != "0") {
        vector<string> words = getSearchableWords(tokenize(parse, " "), engine); //Recycle bro.
        cout<<"Results for your search:"<<endl;
        int counter = 0;
        if (words.size() > 0) {
        	list<Book> topHits = engine.search(words);
            for (list<Book>::iterator index = topHits.begin(); index != topHits.end(); index++) {
                cout<<++counter << ". "<< index->getTitle()<<endl;
                if (counter > 3) break;
            }
        }
        if(counter < 3) cout<<"What a shame we don't have enough sources"<<endl;
        getline(cin, parse);
    }
    
    return 0;
}
