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
#include <ctime>

using namespace std;

/*
 This is the runner for the Search Engine.
 Author - yamil.asusta
*/


int main() {
    
    time_t start, end;
    
    //Engine requirements initializations.
    string dir = string("../moviesdb/"); //Literal location of files.
    vector<string> files = vector<string>();
    getdir(dir,files); //Get files from directory and add them to vector.
    Engine engine; //The search engine.
        
    cout <<endl<<"Starting to build the search engine."<<endl;
    time (&start);
    
    //Uncomment this for serial build
    
    cout <<"Serial build started." <<endl;
    for (int i = 0; i < files.size(); i++) {
        if (files[i].c_str()[0]!='.') { //Avoid hidden files.
            vector<string> words = ParsedFile(dir + files[i]).readAndTokenize(); //Get all words
            for (int j = 0; j < words.size(); j++) 
                engine.addToEngine(sanitize(words[j]), files[i]); //Sanitize removes capital letters, an non alpha chars
        }
    }
    
    
    //cout << "Parallel build started." <<endl;
    //engine = buildEngine(dir, files); //Si fuera paralelo.
    
    time (&end);
    cout<<"Done building the search engine. It took: "<< difftime(end,start) << "seconds"<<endl;
    files.clear(); //Clean up memory.
    
    //I/O with the user.
    //Start asking for words to search for.
    string parse; //Input parser.
    do {
        cout<<endl<<"Submit your words bro! Enter 0 when done."<<endl;
        getline(cin, parse);
        time (&start);
        if(parse == "0") break; //Exit 
        vector<string> words = getSearchableWords(tokenize(parse, " "), engine); //Tokenize returns vector of words, then remove those that are not in engine.
        
        cout<<endl<<"Results for your search:"<<endl;
        int counter = 0;
        
        if (words.size() > 0) {
        	list<Book> topHits = engine.search(words); //Get a sorted intersection of all searchable words.
            time(&end);
            for (list<Book>::iterator index = topHits.begin(); index != topHits.end(); index++) {
                cout<<++counter << ". "<< index->getTitle() << " - " << index->getRepetitions()<<endl; // Print the title of the book and its repetitions.
                if (counter == 3) break; // Only the top 3 values should be shown.
            }
            cout<<endl;
        }
        
        cout<<"Search took: " << difftime(end,start) << "seconds."<<endl;
        if(counter < 3) cout<<"What a shame we don't have enough sources!"<<endl;
    } while (true);
    
    cout << "We are not Google but thanks for using us bro :)" <<endl;
    
    return 0;
}
