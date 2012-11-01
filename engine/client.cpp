#include "ParsedFile.h"
#include <iostream>
#include <fstream>
#include <tr1/unordered_map>
#include "Histogram.h"
#include <vector>
#include <algorithm>
#include <locale>
#include <string>
#include <list>
#include "Book.h"

using namespace std;

/*
   Muestra como invocar la funcion getdir para obtener los nombres de los 
   archivos del directorio. Luego muestra como crear un objeto tipo
   ParsedFile para luego obtener las palabras del archivo en un vector
   de strings.
*/

int main() {
    
    //Engine requirements
    string dir = string("./moviesdb/");
    vector<string> files = vector<string>();
    getdir(dir,files); //Anade los files del directorio al vector
    tr1::unordered_map<string, Histogram> engine;
    tr1::unordered_map<string, Histogram>::iterator mapIndex;
    
    locale filter;
    
    //Stopwords requirements
    tr1::unordered_map<string, int> stopWords;//Lista esta sorted, so binary search for the win.
    ifstream stopFile("../stopwords.txt");
    
    
    cout << "Building the stopwatch list."<<endl;
    do {
        string parse;
        stopFile >> parse;
        stopWords[parse] = 1;
    } while (!stopFile.eof());

    stopFile.close();

    cout << "Done building the stopwatch list."<<endl;
    
    //Montar el engine. Contiene un hash table para index las palabras.
    //El key es la palabra, el value es un Histograma que mantiene un LL y
    //un counter total. El LL mantiene un historial de libros con su titulo y
    //apariciones de la palabra.
    cout <<endl<<"Start building the search engine."<<endl;
    for (int i = 0; i < files.size(); i++) {
        
        if (files[i].c_str()[0]!='.') { //Trampa de Arce para evitar hidden files
            
            vector<string> words = ParsedFile(dir + files[i]).readAndTokenize(); //Get all words
            
            for (int j = 0; j < words.size(); j++) {
                //cout<<words[j]<<endl;
                
                //Clean words
                
                for (int k = 0; k < words[j].length(); k++) {
                    words[j][k] = tolower(words[j][k], filter);
                    if(!isalpha(words[j][k], filter)) {
                        if(words[j][k] == '\'') words[j].erase(k);
                        else words[j].erase(k--,1);
                    }
                }
				
                //If the word is not in stopwords.txt, add it to the engine
                //!binary_search(stopWords.begin(), stopWords.end(), words[j])
                if (stopWords.find(words[j]) == stopWords.end() && !words[j].empty()) {
                    //If found, increase counter
                    
                    mapIndex = engine.find(words[j]);
                    if (mapIndex != engine.end()) {
                
                		engine[words[j]].add(files[i]);
                    }
                    //If not found, add the word
                    else {
                        engine[words[j]] = Histogram(files[i]);
                    }
                }
            }
        }
    }
    cout<<"Done building search engine."<<endl;
    
     
    //Empezar un utility file.
    //Empieza el I/O con el usuario.
    cout<<endl<<"Submit your words bro! Enter 0 when done."<<endl;
    string parse;
    getline(cin, parse);
    
    while (parse != "0") {
        vector<string> words = tokenize(parse, " "); //Recycle bro.
		if(words.size() == 0 || words.size() > 2) {
            cout<<"Invalid parameters. Just 1 or 2 words only."<<endl;            
        }
        else {
            if (words.size() == 2) {
                //Caso en que ambas palabras no son iguales y estan en el engine.
				if(engine.find(words[0]) != engine.end() && engine.find(words[1]) != engine.end() && words[0] != words[1]) {
                    list<Book> intersection = getIntersection(engine[words[0]].getHistogram(), engine[words[1]].getHistogram());
                    intersection.sort(bookSort);
                    
                    int counter = 0;
					for (list<Book>::iterator bookIndex = intersection.begin(); bookIndex != intersection.end(); bookIndex++) {
                        if(counter == 3)
                            break;
                        cout<<bookIndex->getTitle()<<endl;
                        counter++;
                    }
                    if(counter < 3)
                        cout <<"Not enough common files"<<endl;
                }
                //Caso en que son iguales o una no esta en el engine.
                else if((words[0] == words[1]) || (engine.find(words[0]) == engine.end() && engine.find(words[1]) != engine.end()) || (engine.find(words[1]) == engine.end() && engine.find(words[0]) != engine.end())) {
                    //Son iguales.
                    if(words[0] == words[1]) {
                        list<Book> matches = engine[words[0]].toList();
                        matches.sort(bookSort);
                        
                        int counter = 0;
                        for (list<Book>::iterator bookIndex = matches.begin(); bookIndex != matches.end(); bookIndex++) {
                            if(counter == 3)
                                break;
                            cout<<bookIndex->getTitle()<<endl;
                            counter++;
                        }
                        if (counter < 3) {
                            cout<<"Not enough sources"<<endl;
                        }
                    }
                    //One doesn't have it.
                    else {
                        list<Book> matches = (engine.find(words[0]) == engine.end())?engine[words[1]].toList(): engine[words[0]].toList();
                        matches.sort(bookSort);
                        
                        int counter = 0;
                        for (list<Book>::iterator bookIndex = matches.begin(); bookIndex != matches.end(); bookIndex++) {
                            if(counter == 3)
                                break;
                            cout<<bookIndex->getTitle()<<endl;
                            counter++;
                        }
                        if (counter < 3 ) {
                            cout<<"Not enough sources"<<endl;
                        }
                    }
                }
                //No esta en el engine at all.
                else {
                    cout<<"Words are not in engine"<<endl;
                }
            }
        }
        getline(cin, parse);
    }
    
    return 0;
}
